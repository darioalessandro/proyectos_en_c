/* ====================================================================
 
 Copyright (c) 2013 Dario Alessandro Lencina Talarico. All rights
 reserved. *
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 
 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in
 the documentation and/or other materials provided with the
 distribution.
 
 3. The end-user documentation included with the redistribution,
 if any, must include the following acknowledgment:
 
 "This product includes software developed by
 Dario Alessandro Lencina Talarico: darioalessandrolencina@gmail.com"
 
 Alternately, this acknowledgment SHOULD be included in the software itself,
 usually where such third-party acknowledgments normally appear,
 
 5. Products derived from this software may not be called "Designed by Dario Lencina",
 nor may "Designed by Dario" appear in their name, without prior written
 permission.
 
 THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL DARIO ALESSANDRO LENCINA TALARICO OR
 ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 SUCH DAMAGE.
 ==================================================================== */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#import  <libxml/HTMLparser.h>

 #define BSIZE 0x1000

//*******No trate de analizar este metodo, utiliza muchas funciones avanzadas.
static void fail (int test, const char * format, ...){
    if (test) {
    va_list args;
    va_start (args, format);
    vfprintf (stderr, format, args);
    va_end (args);
    exit (EXIT_FAILURE);
    }
}

static char * perform_http_get (int socket_ref, const char * host, const char * page){    
    char * request_message=NULL;    

    const char * request_format =
        "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.77 Safari/537.36\r\n\r\n";

    int status;

    status = asprintf (&request_message, request_format, page, host);    

    fail (status == -1 || ! request_message, "asprintf failed.\n");
    
    status = send (socket_ref, request_message, strlen (request_message), 0);

    fail (status == -1, "send failed: %s\n", strerror (errno));
    char * page_content= NULL;      
    int content_length=-1;  

    while (1) {  //Loop infinito puesto que siempre se va a cumplir esta condición.
        int numero_de_bytes_recibidos;  
        char buffer_de_datos_recibidos[BSIZE+10];
    
        numero_de_bytes_recibidos = recvfrom (socket_ref, buffer_de_datos_recibidos, BSIZE, 0, 0, 0);

        if (numero_de_bytes_recibidos == 0) {
            break;
        }
        fail (numero_de_bytes_recibidos == -1, "%s\n", strerror (errno));   
        //Es necesario poner un null al final de cada bloque para que sea un string válido
        buffer_de_datos_recibidos[numero_de_bytes_recibidos] = '\0'; 
        if(page_content==NULL){
            asprintf(&page_content, "%s", buffer_de_datos_recibidos);           
        }else{          
            asprintf(&page_content, "%s%s", page_content, buffer_de_datos_recibidos);
        }        
    }
    free (request_message);
    return page_content;
}

char * download_page(char * host, char * protocol, char * page){
    struct addrinfo hints, *res, *res0;
    int error;    
    int socket_ref;        
    memset (&hints, 0, sizeof(hints)); //Inicializando hints con 0.
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    error = getaddrinfo (host, protocol, & hints, & res0);
    fail (error, gai_strerror(error));
    socket_ref = -1;
    for (res = res0; res; res = res->ai_next) {
        socket_ref = socket (res->ai_family, res->ai_socktype, res->ai_protocol);
        fail (socket_ref < 0, "socket: %s\n", strerror (errno));
        if (connect(socket_ref, res->ai_addr, res->ai_addrlen) < 0) {
            fprintf (stderr, "connect: %s\n", strerror (errno));
            close(socket_ref);
            exit (EXIT_FAILURE);
        }
        break;
    }
    char * page_content=NULL;
    if (socket_ref != -1) {
        page_content= perform_http_get(socket_ref, host, page);          
    }
    freeaddrinfo(res0);
    return page_content;
}

int main(int argc, char **argv) {    
    printf("Number of arguments %d\n",argc);
    if((argc < 2) || (argc > 4)) {
    fprintf(stderr, "Error: wrong number of arguments.\n");    
    return(-1);
    }

    char * url_format= "numeracion.exe/info_tel?cld=%s&telefono=%s";
    char * query= malloc(sizeof(char)*strlen(url_format)+10);
    sprintf(query, url_format, argv[1],argv[2]);
    printf("Server query %s\n", query);
    char * page_content= download_page("159.16.237.60","http", query);         
    free(query);
         
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj_company, xpathObj_city; 
    
    xmlChar * xpath_Expr_company= BAD_CAST "/html/body/form/div/table/tr[8]/td[2]/p/span[1]/b/span[1]";
    xmlChar * xpath_Expr_city   = BAD_CAST "/html/body/form/div/table/tr[3]/td[2]/p/span/b/span[1]";    
        
        
    doc= htmlReadDoc(BAD_CAST page_content, NULL, "windows-1252",HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);

    if (doc == NULL) {
    fprintf(stderr, "Error: no fue posible parsear el archivo \"%s\"\n", page_content);
    return(-1);
    }

    //Crear contexto de evaluación del XPath
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        fprintf(stderr,"Error: No fue posible crear el contexto\n");
        xmlFreeDoc(doc); 
        return(-1);
    }
      
    //Evaluación de las expresiones
    xpathObj_company = xmlXPathEvalExpression(xpath_Expr_company, xpathCtx);
    xpathObj_city = xmlXPathEvalExpression(xpath_Expr_city, xpathCtx);

    if(xpathObj_company == NULL) {
        fprintf(stderr,"Error: no se pudo evaluar la expresión \"%s\"\n", xpath_Expr_company);
        xmlXPathFreeContext(xpathCtx); 
        xmlFreeDoc(doc); 
        return(-1);
    }

    if(xpathObj_city == NULL) {
        fprintf(stderr,"Error: no se pudo evaluar la expresión \"%s\"\n", xpath_Expr_city);
        xmlXPathFreeContext(xpathCtx); 
        xmlFreeDoc(doc); 
        return(-1);
    }

    //Parseo de los resultados de las expresiones.
    xmlNode *node_company = xpathObj_company->nodesetval->nodeTab[0];
    xmlNode *node_city = xpathObj_city->nodesetval->nodeTab[0];
    
    char * company= (char *) xmlNodeGetContent(node_company);
    char * city= (char *) xmlNodeGetContent(node_city);

    //Impresión de los resultados

    printf("compañía %s\n\n", company);
    printf("ciudad %s\n\n", city);    
    
    //Limpieza de los objetos reservados
    xmlXPathFreeObject(xpathObj_company);
    xmlXPathFreeObject(xpathObj_city);
    xmlXPathFreeContext(xpathCtx); 
    xmlFreeDoc(doc); 
    free(page_content);    //Liberar la memoria reservada por download_page. Esta es una función avanzada.
    return 0;
}
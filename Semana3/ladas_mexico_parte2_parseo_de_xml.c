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

int main (){    
    //Declaración de variables
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj_company, xpathObj_city; 

    //Ruta al archivo de prueba, en este caso, pagina de prueba debe de estar al mismo nivel que 
    //este archivo.

    char * filename= "pagina_de_prueba.html";

    //Consultas extraidas de Chrome para acceder a la ciudad y compañía
    xmlChar * xpath_Expr_company= BAD_CAST "/html/body/form/div/table/tr[8]/td[2]/p/span[1]/b/span[1]";
    xmlChar * xpath_Expr_city= BAD_CAST "/html/body/form/div/table/tr[3]/td[2]/p/span/b/span[1]";    
        
    //Código para cargar el archivo usando libxml
    doc = htmlReadFile(filename,"windows-1252",HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
    if (doc == NULL) {
    fprintf(stderr, "Error: no fue posible parsear el archivo \"%s\"\n", filename);
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
    
    //Impresión de los resultados
    printf("content_company %s\n\n", (char *) xmlNodeGetContent(node_company));
    printf("content_city %s\n\n", (char *) xmlNodeGetContent(node_city));    
    
    //Limpieza de los objetos reservados
    xmlXPathFreeObject(xpathObj_company);
    xmlXPathFreeObject(xpathObj_city);
    xmlXPathFreeContext(xpathCtx); 
    xmlFreeDoc(doc); 
    return 0;
}
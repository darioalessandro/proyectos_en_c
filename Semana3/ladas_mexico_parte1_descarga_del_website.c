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

#define BSIZE 0x1000

static void fail (int test, const char * format, ...){
    if (test) {
	va_list args;
	va_start (args, format);
	vfprintf (stderr, format, args);
	va_end (args);
	exit (EXIT_FAILURE);
    }
}

//No trate de analizar este metodo, utiliza muchas funciones avanzadas.
static char * get_page (int socket_ref, const char * host, const char * page){    
    char * request_message=NULL;

    /* "format" is the format of the HTTP request we send to the web
       server. */

    const char * request_format =
        "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.77 Safari/537.36\r\n\r\n";

    int status;

    status = asprintf (&request_message, request_format, page, host);

    /* Check that "asprintf" succeeded. */

    fail (status == -1 || ! request_message, "asprintf failed.\n");

    /* Send the request. */

    status = send (socket_ref, request_message, strlen (request_message), 0);

    fail (status == -1, "send failed: %s\n", strerror (errno));
    char * page_content= NULL;      
    int content_length=-1;  

    while (1) {	 //Loop infinito puesto que siempre se va a cumplir esta condición.
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

//No trate de analizar este metodo, utiliza muchas funciones avanzadas.
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
        page_content= get_page (socket_ref, host, page);          
    }
    freeaddrinfo(res0);
    return page_content;
}


int main (){    
    char * page_content= download_page("159.16.237.60","http", "numeracion.exe/info_tel?cld=462&telefono=6266452");    
    printf("page_content:\n%s\n", page_content);    
    free(page_content);    //Liberar la memoria reservada por download_page. Esta es una función avanzada.
    return 0;
}
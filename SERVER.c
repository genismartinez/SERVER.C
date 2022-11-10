/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_BUFFER 1024
 
int main(int *a){
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in serv_adr, client_adr;
    char buffer[MIDA_BUFFER];
    socklen_t mida;
    int n, i;
    
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM,0);

    /* Posem les dades del socket */
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(44444);

    /* Enllacem el socket */
    n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    if (n < 0)
    {
        printf("No s'ha pogut enllacar el socket\n");
    }
    else
    {
        i = 0;
        /* Servidor operatiu! */
        printf("Servidor operatiu!\n");

        while (1)   /* Bucle infinit */
        {
        	recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida);
        	
        	int n1, n2;
        	printf("Paquet rebut!\n");
        	printf("%s\n", buffer);
        	i++;
        	
        	sscanf(buffer, "%d %d", &n1,&n2);

		if (n1<0 || n1>99 && n2<0 || n2>99) {
        		sprintf(buffer,"Error, nombres fora de rang!");
        	}
        
        	int resultat = n1 * n2;
        	
        	
        	sprintf(buffer, "El resultat de multiplicar %d i %d és %d\n", n1, n2, resultat);
		sendto(s, buffer, MIDA_BUFFER,0,(struct sockaddr*)&client_adr,sizeof(client_adr));
		printf("El servidor ha enviat: %s", buffer);
        }
    }

    /* Tanquem el socket */
    close(s);
    return 0;
}
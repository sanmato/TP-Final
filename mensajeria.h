#ifndef MENSAJERIA_H
#define MENSAJERIA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utilidades.h"
#include "usuario.h"

typedef struct 
{
	int idUsuarioEmisor;
	int idUsuarioReceptor;
	int idContenidoEnviado;
	char mensaje[300];
	int leido; // 1:si 0:no
} stMensajeria;


int obtenerProximoIdMensajeria()
{
	FILE* arch = fopen("mensajes.dat", "rb");
	
	if ( arch==NULL )
		exit(1);
	
	fseek(arch, 0, SEEK_END);
	fseek(arch,-sizeof(stMensajeria),SEEK_CUR);
	
	stMensajeria mensajeria;
	fread(&mensajeria, sizeof(stMensajeria), 1, arch);
	
	fclose(arch);
	
	return mensajeria.idContenidoEnviado+1;
}



void crearMensajeria()
{
    FILE *arch;
    arch=fopen("mensajes.dat","wb");
    
    if (arch==NULL)
        exit(1);
            	
    stMensajeria mensajeria;
        
    mensajeria.idContenidoEnviado = 0;
    mensajeria.idUsuarioEmisor = 0;
    mensajeria.idUsuarioReceptor = 0;
    mensajeria.leido = 1;
    
    strcpy(mensajeria.mensaje, "prueba");
    
	fwrite(&mensajeria, sizeof(stMensajeria), 1, arch);
    fclose(arch);

    continuar();
}

void cargarMensajeria( int idEmisor )
{
    stMensajeria mensajeria;
    
    mensajeria.idContenidoEnviado = obtenerProximoIdMensajeria();
			
	FILE *arch = fopen("mensajes.dat","ab");
		
	if (arch==NULL)
		exit(1);
		
	mensajeria.leido = 0;
	mensajeria.idUsuarioEmisor = idEmisor;
    
    printf("Ingrese el nombre del usuario receptor:\n");
    fflush(stdin);
    char username[20];
    stUsuario usuario;
    gets(username);
    
    if ( obtenerUsuarioPorNombre(username, &usuario) )
    {
        mensajeria.idUsuarioReceptor = usuario.idUsuario;
        printf("Ingrese el contenido del mensaje: \n");
    	fflush(stdin);
    	gets(mensajeria.mensaje);
    }
	
	fwrite(&mensajeria, sizeof(stMensajeria), 1, arch);
	fclose(arch);
	
    
    continuar();
}

void listadoMensajesRecibidos( char* usernameDesde )
{
    stUsuario receptor;
    obtenerUsuarioPorNombre( usernameDesde, &receptor );



    FILE *arch;
    arch=fopen("mensajes.dat","rb");
    if (arch==NULL)
        exit(1);
    stMensajeria mensajeria;
    fread(&mensajeria, sizeof(stMensajeria), 1, arch);
    while(!feof(arch))
    {
		if ( mensajeria.idUsuarioReceptor == receptor.idUsuario )
        {
            stUsuario emisor;
            obtenerUsuarioPorId( mensajeria.idUsuarioEmisor, &emisor );
			printf("Id: %d\nDe: %s\nMensaje: %s\nLeído: %d\n\n", mensajeria.idContenidoEnviado, emisor.userName, mensajeria.mensaje, mensajeria.leido );
		};
		
        fread(&mensajeria, sizeof(stMensajeria), 1, arch);
    }
    fclose(arch);
    continuar();
}

void listadoMensajesEnviados( char* usernameDesde )
{
    stUsuario emisor;
    obtenerUsuarioPorNombre( usernameDesde, &emisor );

    FILE *arch;
    arch=fopen("mensajes.dat","rb");
    if (arch==NULL)
        exit(1);
    stMensajeria mensajeria;
    fread(&mensajeria, sizeof(stMensajeria), 1, arch);
    while(!feof(arch))
    {
        if ( mensajeria.idUsuarioEmisor == emisor.idUsuario )
        {
            stUsuario receptor;
            obtenerUsuarioPorId( mensajeria.idUsuarioReceptor, &receptor );
            printf("Id: %d\nPara: %s\nMensaje: %s\nLeído: %d\n\n", mensajeria.idContenidoEnviado, receptor.userName, mensajeria.mensaje, mensajeria.leido );
        };
        
        fread(&mensajeria, sizeof(stMensajeria), 1, arch);
    }
    fclose(arch);
    continuar();
}



#endif


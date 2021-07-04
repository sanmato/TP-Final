#ifndef AUTH
#define AUTH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "usuario.h"
#include "usuario_comun.h"
#include "admin.h"
#include "mensajeria.h"

void iniciarSesion()
{
	printf("usuario:");
	char username[20];
	fflush(stdin);
	gets(username);

	printf("password:");
	char password[20];
	fflush(stdin);
	gets(password);

	stUsuario usuario;


	if ( obtenerUsuarioPorNombre(username,&usuario) )
	{

		if ( strcmp(usuario.password, password) == 0 )
		{
			if ( usuario.rol == 1 )
			{
				menuAdministrador();
			}
			else
			{
				printf("Bienvenido %s!!\n Mensajes recibidos:\n", usuario.userName );
				//listadoMensajesRecibidos(usuario.userName);
				menuUsuarioComun(usuario);
			};

		}
		else
		{
			printf("Credenciales de acceso incorrectas\n");
		}
	}
	else
	{
		printf("Credenciales de acceso incorrectas\n");
	}

};

void registrarUsuario()
{
	cargarUsuario();
};



#endif

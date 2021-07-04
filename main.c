#include <stdio.h>


#include "usuario.h"
#include "usuario_comun.h"
#include "auth.h"

void menuPrincipal()
{
	int opcion;
    do
    {
        printf("1 - Iniciar sesion\n");
        printf("2 - Registrarse\n");
        printf("3 - Salir\n\n");

        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion)
        {
			case 1:iniciarSesion();
				break;
			case 2:registrarUsuario();
				break;
        }
    } while (opcion!=3);
}

int main()
{
    ///crearUsuario(); ///EJECUTAR EN CASO DE BORRAR EL ARCHIVO, CREA UN ARCHIVO USUARIO CON UN REGSITRO PRECARGADO.


    printf("Bienvenido a in-Social\n");
    printf("======================\n\n");

    menuPrincipal();

    return 0;
}

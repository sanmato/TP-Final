#ifndef ADMIN_H
#define ADMIN_H

#include "usuario.h"

void menuAdministrador()
{
	printf("Panel administrador\n");
	printf("-------------------\n\n");
	int opcion;
    do
    {

        printf("1 - Crear archivo binario (CREA UN ARCHIVO CON UN USUARIO)\n");
        printf("2 - Crear usuario (ALTA USR)\n");
        printf("3 - Listar usuarios\n");
        printf("4 - Buscar usuario por nombre\n");
        printf("5 - Modificar usuario\n");
        printf("6 - Eliminar usuario\n");
        printf("7 - Crear Contenido (CREA UN ARCHIVO CONTENIDO CON DATO PRECARGADO)\n");
        printf("8 - Cargar Contenido (ALTA CONTENIDO)\n");
        printf("9 - Ver Listado de Contenidos\n");
        printf("10 - Consultar Contenido por ID\n");
        printf("11 - Modificacion de Contenido\n");
        printf("12 - Eliminar Contenido\n");
        printf("13 - Salir\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion)
        {
			case 1:crearUsuario();
				break;
			case 2:cargarUsuario();
				break;
			case 3:listadoDeUsuarios();
				break;
			case 4:consultaUsuario();
				break;
			case 5:modificacionUsuario();
				break;
			case 6:eliminacionUsuario();
				break;
            case 7:crearContenido();
				break;
			case 8:cargarContenido();
				break;
			case 9:listadoContenidos();
				break;
			case 10:consultaContenido();
				break;
			case 11:modificacionContenido();
				break;
			case 12:eliminacion();
				break;
        }
    } while (opcion!=13);
};


#endif

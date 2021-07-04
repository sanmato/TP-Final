#ifndef USUARIO_COMUN_H
#define USUARIO_COMUN_H

void menuUsuarioComun(stUsuario usuarioActual)
{
	printf("Panel del usuario\n");
	printf("-------------------\n\n");
	int opcion;
    do
    {

        printf("1 - Cargar Contenido\n");
        printf("2 - Ver Listado de Contenidos\n");
        printf("3 - Consultar Contenido por ID\n");
        printf("4 - Buscar usuario por Nombre de Usuario\n");
        printf("5 - Salir\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
        switch (opcion)
        {
			case 1:cargarContenido();
				break;
			case 2:listadoContenidos();
				break;
			case 3:consultaContenido();
				break;
            case 4:consultaUsuario();
            break;
        }
    } while (opcion!=5);
};

#endif

#ifndef CONTENIDO_H
#define CONTENIDO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utilidades.h"

typedef struct
{
	int idContenido; // auto incremental
	char titulo[30];
	char descripcion[300];
	char categoria[30];
	int likes;
	int puntosPorCompartir;
	int activo; // indica 1 o 0 si el contenido está activo
} stContenido;


int obtenerProximoIdContenido()
{
	FILE* arch = fopen("contenidos.dat", "rb");

	if ( arch==NULL )
		exit(1);

	fseek(arch, 0, SEEK_END);
	fseek(arch,-sizeof(stContenido),SEEK_CUR);

	stContenido contenido;
	fread(&contenido, sizeof(stContenido), 1, arch);

	fclose(arch);

	return contenido.idContenido+1;
}


void crearContenido()
{
    FILE *arch;
    arch=fopen("contenidos.dat","wb");

    if (arch==NULL)
        exit(1);

    stContenido contenido;

    contenido.idContenido = 0;
    contenido.activo = 1;
    contenido.likes = 0;
    contenido.puntosPorCompartir = 0;

    strcpy(contenido.titulo, "default");
    strcpy(contenido.descripcion, "contenido-inicial");
    strcpy(contenido.categoria, "ninguna");


	fwrite(&contenido, sizeof(stContenido), 1, arch);


    fclose(arch);
    continuar();
}

void cargarContenido()
{
    stContenido contenido;

    contenido.idContenido = obtenerProximoIdContenido();

	FILE *arch = fopen("contenidos.dat","ab");

	if (arch==NULL)
		exit(1);

	contenido.activo = 1;
	contenido.likes = 0;
	contenido.puntosPorCompartir = 0;

    printf("Ingrese el titulo del contenido:\n");
    fflush(stdin);
    gets(contenido.titulo);

	printf("Ingrese la descripcion del contenido:\n");
	fflush(stdin);
	gets(contenido.descripcion);

	printf("Ingrese la categoria del contenido:\n");
    fflush(stdin);
    gets(contenido.categoria);


	fwrite(&contenido, sizeof(stContenido), 1, arch);
	fclose(arch);


    continuar();
}

void listadoContenidos()
{
    FILE *arch;
    arch=fopen("contenidos.dat","rb");
    if (arch==NULL)
        exit(1);
    stContenido contenido;
    fread(&contenido, sizeof(stContenido), 1, arch);
    while(!feof(arch))
    {
		if ( contenido.activo == 1 )
        {
			printf("Id: %d\nTitulo: %s\nDescripcion: %s\nCategoria: %s\nLikes: %d\nPuntos: %d\n\n", contenido.idContenido, contenido.titulo, contenido.descripcion, contenido.categoria, contenido.likes, contenido.puntosPorCompartir);
		};

        fread(&contenido, sizeof(stContenido), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consultaContenido()
{
    FILE *arch=fopen("contenidos.dat","rb");

    if (arch==NULL)
        exit(1);

    printf("Ingrese el id del contenido a consultar:");

    int id;
    scanf("%d",&id);

    stContenido contenido;
    int existe=0;
    fread(&contenido, sizeof(stContenido), 1, arch);
    while(!feof(arch) && existe != 1)
    {
        if ( id == contenido.idContenido && contenido.activo == 1)
        {
           printf("\n\nId: %d\nTitulo: %s\nDescripcion: %s\nCategoria: %s\nLikes: %d\nPuntos: %d\n\n", contenido.idContenido, contenido.titulo, contenido.descripcion, contenido.categoria, contenido.likes, contenido.puntosPorCompartir);
           existe=1;
           break;
        }
        fread(&contenido, sizeof(stContenido), 1, arch);
    }
    if (existe==0)
        printf("No existe un contenido con el titulo ingresado.\n");
    fclose(arch);
    continuar();
}

void modificacionContenido()
{
    FILE *arch;
    arch=fopen("contenidos.dat","r+b");

    if (arch==NULL)
        exit(1);

    printf("Ingrese el id del contenido a modificar:");
    int id;
    scanf("%i", &id);
    stContenido contenido;

    int existe=0;
    fread(&contenido, sizeof(stContenido), 1, arch);
    while(!feof(arch) && existe != 1 )
    {
		if (id==contenido.idContenido && contenido.activo == 1 )
		{
			printf("Id: %d\nTitulo: %s\nDescripcion: %s\nCategoria: %s\nLikes: %d\nPuntos: %d\n\n", contenido.idContenido, contenido.titulo, contenido.descripcion, contenido.categoria, contenido.likes, contenido.puntosPorCompartir);

			printf("Ingrese el titulo del contenido:\n");
			fflush(stdin);
			gets(contenido.titulo);

			printf("Ingrese la descripcion del contenido:\n");
			fflush(stdin);
			gets(contenido.descripcion);

			printf("Ingrese la categoria del contenido:\n");
			fflush(stdin);
			gets(contenido.categoria);

			int pos=ftell(arch)-sizeof(stContenido);
			fseek(arch,pos,SEEK_SET);
			fwrite(&contenido, sizeof(stContenido), 1, arch);
			printf("Se modifico el contenido.\n");
			existe=1;
			//break;
        }
        fread(&contenido, sizeof(stContenido), 1, arch);
    }
    if (existe==0)
        printf("No existe contenido para el id ingresado\n");
    fclose(arch);
    continuar();
}

void eliminacion()
{
	FILE *arch;
    arch=fopen("contenidos.dat","r+b");

    if (arch==NULL)
        exit(1);

    printf("Ingrese el id de contenido a eliminar:");
    int cod;
    scanf("%i", &cod);
    stContenido contenido;

    int existe=0;
    fread(&contenido, sizeof(stContenido), 1, arch);
    while(!feof(arch) && existe != 1 )
    {
        if (cod==contenido.idContenido && contenido.activo == 1 )
        {

           contenido.activo = 0;
           int pos=ftell(arch)-sizeof(stContenido);
           fseek(arch,pos,SEEK_SET);
           fwrite(&contenido, sizeof(stContenido), 1, arch);
           printf("Se elimino el Contenido.\n");
           existe=1;
           //break;
        }
        fread(&contenido, sizeof(stContenido), 1, arch);
    }
    if (existe==0)
        printf("No existe un Contenido asociado al ID ingresado.\n");
    fclose(arch);
    continuar();
};

#endif


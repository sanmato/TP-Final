#ifndef USUARIO_H
#define USUARIO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utilidades.h"
#include "contenido.h"

typedef struct
{
	int idUsuario; // auto incremental
	char nombre[30];
	char apellido[30];
	char userName[20];
	char password[20];
	char mail[30];
	char genero;
	int listadoIdsContenidosGuardados[50];
	int validosContenidos;
	int puntaje;
	int nivel;
	int rol;// 1: es admin - 0: es comun
	int activo;// indica 1 o 0 si el usuario está activo
	stContenido contenidosFavoritos[50]; // pensar como administrarlos
} stUsuario;


///ID AUTOINCREMENTAL
int obtenerProximoIdUsuario()
{
	FILE* arch = fopen("usuarios.dat", "rb");

	if ( arch==NULL )
		exit(1);

	fseek(arch, 0, SEEK_END);
	fseek(arch,-sizeof(stUsuario),SEEK_CUR);

	stUsuario usuario;
	fread(&usuario, sizeof(stUsuario), 1, arch);

	fclose(arch);

	return usuario.idUsuario+1;
}


///CREA UN ARCHIVO USUARIO CON UN DATO PRECARGADO
void crearUsuario()
{
    FILE *arch;
    arch=fopen("usuarios.dat","wb");

    if (arch==NULL)
        exit(1);

    stUsuario usuario;

    usuario.idUsuario = 0;
    usuario.activo = 1;

    strcpy(usuario.userName, "admin");
    strcpy(usuario.password, "987654");
    strcpy(usuario.nombre, "Administrador");
    strcpy(usuario.apellido, "admin");
    strcpy(usuario.mail, "mail@admin.com");
    usuario.genero = 'M';
    usuario.rol = 1;

	fwrite(&usuario, sizeof(stUsuario), 1, arch);


    fclose(arch);
    continuar();
}

///VALIDACION USERNAME
int existeUsername( char* username )
{
	FILE *arch;
    arch=fopen("usuarios.dat","rb");

	if (arch==NULL)
        return 0;

	stUsuario usuario;
    int existe=0;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch))
    {
		if ( strcmp(username, usuario.userName) == 0 && usuario.activo == 1 )
		{
			existe = 1;
			break;
		}
		else if ( strcmp(username, usuario.userName) == 0 && usuario.activo == 0 )
        {
			existe=0;
            break;
        }
        fread(&usuario, sizeof(stUsuario), 1, arch);
    }

    fclose(arch);

    return existe;
}

///ALTA DE USUARIO
void cargarUsuario()
{
    stUsuario usuario;

    printf("Ingrese el Nombre de Usuario:");
    fflush(stdin);
    gets(usuario.userName);

    if ( !existeUsername(usuario.userName) )
    {
		usuario.idUsuario = obtenerProximoIdUsuario();
		usuario.activo = 1;
		usuario.rol = 0;

		FILE *arch;
		arch=fopen("usuarios.dat","ab");

		if (arch==NULL)
			exit(1);

		printf("Ingrese el Password del Usuario:");
		fflush(stdin);
		gets(usuario.password);

		printf("Ingrese el Nombre Real:");
		fflush(stdin);
		gets(usuario.nombre);

		printf("Ingrese el Apellido:");
		fflush(stdin);
		gets(usuario.apellido);

		printf("Ingrese el Genero:");
		fflush(stdin);
		scanf("%c", &usuario.genero);

		printf("Ingrese el Correo Electronico:");
		fflush(stdin);
		gets(usuario.mail);

		fwrite(&usuario, sizeof(stUsuario), 1, arch);
		fclose(arch);
	}
	else
	{
		printf("El nombre de usuario ya se encuentra en uso.\n");
	};


    continuar();
}

void listadoDeUsuarios()
{
    FILE *arch;
    arch=fopen("usuarios.dat","rb");
    if (arch==NULL)
        exit(1);
    stUsuario usuario;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch))
    {
		//printf("%d %s %s %d\n", usuario.idUsuario, usuario.userName, usuario.password, usuario.activo);
        if ( usuario.activo == 1 )
        {
			printf("\n\nID: %d\nNombre:  %s\nApellido:  %s\nNombre de Usuario: %s\nPASSWORD: %s\nE-MAIL: %s\nGENERO: %c\n", usuario.idUsuario, usuario.nombre, usuario.apellido, usuario.userName, usuario.password, usuario.mail, usuario.genero);
		};

        fread(&usuario, sizeof(stUsuario), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consultaUsuario()
{
    FILE *arch=fopen("usuarios.dat","rb");

    if (arch==NULL)
        exit(1);

    printf("Ingrese el nombre del usuario a consultar:");

    char username[20];
    fflush(stdin);
    gets(username);

    stUsuario usuario;
    int existe=0;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch) && existe != 1)
    {
        if ( strcmp(username, usuario.userName) == 0 && usuario.activo == 1)
        {
           printf("\n\nID: %d\nNombre:  %s\nApellido:  %s\nNombre de Usuario: %s\nE-MAIL: %s\nGENERO: %c\n", usuario.idUsuario, usuario.nombre, usuario.apellido, usuario.userName, usuario.mail, usuario.genero);
           existe=1;
           break;
        }
        fread(&usuario, sizeof(stUsuario), 1, arch);
    }
    if (existe==0)
        printf("No existe un usuario con el nombre ingresado.\n");
    fclose(arch);
    continuar();
}

void modificacionUsuario()
{
    FILE *arch;
    arch=fopen("usuarios.dat","r+b");

    if (arch==NULL)
        exit(1);

    printf("Ingrese el idUsuario de usuario a modificar:");
    int cod;
    scanf("%i", &cod);
    stUsuario usuario;

    int existe=0;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch) && existe != 1 )
    {
        if (cod==usuario.idUsuario && usuario.activo == 1 )
        {
           printf("\n\nID: %d\nNombre:  %s\nApellido:  %s\nNombre de Usuario: %s\nPASSWORD: %s\nE-MAIL: %s\nGENERO: %c\n", usuario.idUsuario, usuario.nombre, usuario.apellido, usuario.userName, usuario.password, usuario.mail, usuario.genero);

           printf("Ingrese nuevo password:");
           fflush(stdin);
           gets(usuario.password);

           printf("Ingrese nuevo nombre:");
           fflush(stdin);
           gets(usuario.nombre);

           printf("Ingrese nuevo apellido:");
           fflush(stdin);
           gets(usuario.apellido);

           printf("Ingrese nuevo email:");
           fflush(stdin);
           gets(usuario.mail);

           printf("Ingrese nuevo genero:");
           fflush(stdin);
           scanf("%c", &usuario.genero);


           int pos=ftell(arch)-sizeof(stUsuario);
           fseek(arch,pos,SEEK_SET);
           fwrite(&usuario, sizeof(stUsuario), 1, arch);
           printf("Se modifico el password para dicho usuario.\n");
           existe=1;
           //break;
        }
        fread(&usuario, sizeof(stUsuario), 1, arch);
    }
    if (existe==0)
        printf("No existe un usuario con dicho idUsuario\n");
    fclose(arch);
    continuar();
}

void eliminacionUsuario()
{
	FILE *arch;
    arch=fopen("usuarios.dat","r+b");

    if (arch==NULL)
        exit(1);

    printf("Ingrese el idUsuario de usuario a eliminar:");
    int cod;
    scanf("%i", &cod);
    stUsuario usuario;

    int existe=0;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch) && existe != 1 )
    {
        if (cod==usuario.idUsuario && usuario.activo == 1 )
        {

           usuario.activo = 0;
           int pos=ftell(arch)-sizeof(stUsuario);
           fseek(arch,pos,SEEK_SET);
           fwrite(&usuario, sizeof(stUsuario), 1, arch);
           printf("Se elimino el usuario.\n");
           existe=1;
           //break;
        }
        fread(&usuario, sizeof(stUsuario), 1, arch);
    }
    if (existe==0)
        printf("No existe un usuario con dicho idUsuario\n");
    fclose(arch);
    continuar();
};

int obtenerUsuarioPorNombre( char* username, stUsuario* resultado )
{
    FILE *arch;
    arch=fopen("usuarios.dat","rb");

    if (arch==NULL)
        return 0;

    stUsuario usuario;
    int existe=0;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch))
    {
        if ( strcmp(username, usuario.userName) == 0 && usuario.activo == 1 )
        {
            existe = 1;
            break;
        }

        fread(&usuario, sizeof(stUsuario), 1, arch);
    }

    fclose(arch);
    *resultado = usuario;

    return existe;
}

int obtenerUsuarioPorId( int id, stUsuario* resultado )
{
    FILE *arch;
    arch=fopen("usuarios.dat","rb");

    if (arch==NULL)
        return 0;

    stUsuario usuario;
    int existe=0;
    fread(&usuario, sizeof(stUsuario), 1, arch);
    while(!feof(arch))
    {
        if ( id == usuario.idUsuario && usuario.activo == 1 )
        {
            existe = 1;
            break;
        }

        fread(&usuario, sizeof(stUsuario), 1, arch);
    }

    fclose(arch);
    *resultado = usuario;
    return existe;
}


#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include "gotoxy.h"

typedef struct
{
    int idContenido; // auto incremental
    char titulo[100];
    char descripcion[300];
    char categoria[30];
    int likes;
    int puntosPorCompartir;
    int estado; // indica 1 o 0 si el contenido está activo
} stContenido;

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
    stContenido contenidosFavoritos [100] ; // pensar como administrarlos
    //int rol;                // 1: es admin - 0: es comun
    int estado;             // indica 1 o 0 si el usuario está activo
} stUsuario;

void cargaUnUsuario (char archivo []);
int ultimoIdUsuario (char archivo []);
int validaUserName (char archivo [], char user []);
int validaPassword (char archivo [], char pass []);
int validaMail (char archivo[], char mail []);
void muestraArchivoUsuario (char archivo[]);
void muestraUnUsuario (stUsuario aux);
void cargaArchivoUsuarios (char archivo[]);
int pasaContenidoToArreglo ( char archivo [], stContenido aux [], int dim);
usuarioEligeContenido (char archivoUs [], char archivoCon []);
void ingresoUsuario ();
int buscaUsuario (char archivo [],char nomUser [], char nomPass []);
int buscaIdUsuario (char archivo [], char auxUsername []);
void ingresoPerfilUsuario (char archivoUs [], char archivoCon [], int id);
stUsuario modificarDatosUsuario (stUsuario aux);
void hacerModificacionUsuario(char archivo[]);
void cargaArchivoContenido (char archivo[]);
int ultimoIdContenido (char archivo []);
void muestraArchivoContenido (char archivo []);
void muestraUnContenido (stContenido aux);
void buscarContenidoPorCategoria ( char archivo [], char categoria[]);
void buscarContenidoPorEstado (char archivo[],int estado);
stContenido modificarContenido (stContenido aux);
void hacerModificacionContenido (char archivo[]);



int main()
{
    char fileUsuarios []= "usuarios.dat";
    char fileContenido[]= "contenidos.dat";

    srand(time(NULL));

    char opcion;
    char control='s';

    do
    {
        hidecursor(0);
        color(11);
        printf("\n\t1.carga usuario\n");
        printf("\n\t2.muestra usuario\n");
        printf("\n\t3.carga contenido\n");
        printf("\n\t4.muestra contenido\n");
        printf("\n\t5.ingreso de usuario\n");
        printf("\n\t6.registro nuevo usuario\n");
        printf("\n\t0.salir\n");
        fflush(stdin);
        opcion=getch();
        system("cls");


        switch(opcion)
        {
        case '1':
            cargaArchivoUsuarios(fileUsuarios);
            break;
        case '2':
            muestraArchivoUsuario(fileUsuarios);
            break;
        case '3':
            cargaArchivoContenido(fileContenido);
            break;
        case '4':
            muestraArchivoContenido(fileContenido);
            break;
        case '5':
            ingresoUsuario();
            break;
        case '6':
            //registro

            cargaUnUsuario(fileUsuarios);

            ingresoUsuario();


//            //elegir contenido
//            printf("\npara agregar contenido a favoritos presione 's' ");
//            fflush(stdin);
//            scanf("%c", &control);
//
//            printf("\n\tLISTA DE CONTENIDO\n");
//
//            muestraArchivoContenido(fileContenido);
//            printf("\npara guardar contenido presione 's' ");
//            fflush(stdin);
//            scanf("%c", &control);





            //
            break;
        }
    }
    while(opcion!='0');

    return 0;
}


//carga archivo usuario

void cargaUnUsuario (char archivo [])
{
    FILE*pFile= fopen(archivo,"ab");
    stUsuario aux;
    int id=ultimoIdUsuario(archivo)+1;

    if(pFile!=NULL)
    {
        aux.idUsuario=id;

        printf("\n\tNOMBRE:\t\t");
        fflush(stdin);
        gets(aux.nombre);

        while(strlen(aux.nombre)<3)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets(aux.nombre);
        }

        printf("\tAPELLIDO:\t");
        fflush(stdin);
        gets(aux.apellido);

        while(strlen(aux.apellido)<3)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets(aux.apellido);
        }

        printf("\tUSERNAME:\t");
        fflush(stdin);
        gets(aux.userName);   //validar

        while(strlen(aux.userName)<3)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets (aux.userName);
        }

        while( validaUserName(archivo,aux.userName)==1)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets(aux.userName);
        }

        printf("\tPASSWORD:\t");
        fflush(stdin);
        gets(aux.password);   //validar

        while(strlen(aux.password)<8)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets (aux.password);
        }

        while(validaPassword(archivo,aux.password)==1)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets(aux.password);
        }

        printf("\tMAIL:\t\t");
        fflush(stdin);
        gets(aux.mail);   //validar

        while(strlen(aux.mail)<8)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets(aux.password);
        }

        while(validaMail(archivo,aux.mail)==1)
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            gets(aux.mail);
        }

        printf("\tGENERO:\t\t");
        fflush(stdin);
        scanf("%c",&aux.genero); //validar

        while ( aux.genero!='f' && aux.genero!='m' && aux.genero!='o')
        {
            printf("\n\tingrese nuevamente: ");
            fflush(stdin);
            scanf("%c", &aux.genero);
        }

        aux.estado=1;

        fwrite(&aux,sizeof(stUsuario),1,pFile);

        fclose(pFile);
    }
}

int ultimoIdUsuario (char archivo [])
{
    FILE*pFile= fopen(archivo, "r+b");
    stUsuario aux;
    int ultimo=0;

    if(pFile!=NULL)
    {
        fseek(pFile,-1*sizeof(stUsuario), SEEK_END);
        if(fread(&aux,sizeof(stUsuario),1,pFile)>0)
        {
            ultimo=aux.idUsuario;
        }
        fclose(pFile);
    }
    return ultimo;
}

int validaUserName (char archivo [], char user [])
{
    FILE*pFile=fopen(archivo,"rb");
    stUsuario aux;
    int flag=0;

    if(pFile!=NULL)
    {
        while(flag==0 && fread(&aux,sizeof(stUsuario),1,pFile)>0)
        {
            if(strcmp(aux.userName,user)==0)
            {
                flag=1;
            }
        }
        fclose(pFile);
    }
    return flag;
}

int validaPassword (char archivo [], char pass [])
{
    FILE*pFile= fopen(archivo, "rb");
    stUsuario aux;
    int flag=0;

    if  (pFile!=NULL)
    {
        while (flag==0 && fread(&aux,sizeof(stUsuario),1,pFile)>0)
        {
            if(strcmp(aux.password,pass)==0)
            {
                flag=1;
            }
        }
        fclose(pFile);
    }
    return flag;
}

int validaMail (char archivo[], char mail [])
{
    FILE*pFile= fopen(archivo, "rb");
    stUsuario aux;
    int flag=0;

    if(pFile!=NULL)
    {
        while(flag==0 && fread(&aux,sizeof(stUsuario),1,pFile)>0)
        {
            if(strcmp(aux.mail,mail)==0)
            {
                flag=1;
            }
        }
    }

    return flag;
}

void muestraArchivoUsuario (char archivo[])
{
    FILE*pFile= fopen(archivo,"rb");
    stUsuario aux;

    if(pFile!=NULL)
    {
        while(fread(&aux,sizeof(stUsuario),1,pFile)>0)
        {
            muestraUnUsuario(aux);
        }
        fclose(pFile);
    }
}

void muestraUnUsuario (stUsuario aux)
{
    printf("\n*********************************");
    printf("\n\t%d",aux.idUsuario);
    printf("\n\t%s",strupr(aux.nombre));
    printf("\n\t%s",strupr(aux.apellido));
    printf("\n\t%s",aux.userName);
    printf("\n\t%s",aux.password);
    printf("\n\t%s",aux.mail);
    printf("\n\t%c",toupper(aux.genero));

    if(aux.estado==1)
    {
        printf("\n\tACTIVO\n");
    }
    else
    {
        printf("\n\tINACTIVO\n");
    }
    printf("\n*********************************\n");
}

void cargaArchivoUsuarios (char archivo[])
{
    FILE*pFile=fopen(archivo,"ab");
    char opcion;

    if(pFile!=NULL)
    {
        do
        {
            cargaUnUsuario(archivo);

            printf("\n\tESC para salir\n");
            fflush(stdin);
            opcion=getch();
            system("cls");

        }
        while(opcion!=27);

        fclose(pFile);
    }
}

//registro primera vez usuario

int pasaContenidoToArreglo ( char archivo [], stContenido aux [], int dim)
{
    FILE *pFile = fopen(archivo, "rb");
    int i=0;

    if(pFile!=NULL)
    {

        fclose(pFile);
    }
    return i;
}

usuarioEligeContenido (char archivoUs [], char archivoCon [])
{
//    char control='s';
//    int i=0;
//    stUsuario aux;
//
//    while(control=='s' && i< dim)
//    {
//        printf("\nIngrese el id del contenido de que quiera guardar: ");
//        scanf("%d", &aux.listadoIdsContenidosGuardados[i]);
//
//        i++;
//
//        printf("\npara continuar presione 's'\n");
//        fflush(stdin);
//        scanf("%c", &control);
//    }

}


//ingreso de usuario

void ingresoUsuario ()
{
    char fileUsuarios []= "usuarios.dat";
    char fileContenido[]= "contenidos.dat";

    char auxUsername [20];
    char auxPass [20];
    int idUser=0;

    //ingresa userName

    printf("\n\tUSERNAME:\t");
    fflush(stdin);
    gets(auxUsername);

    printf("\n\tPASSWORD:\t");
    fflush(stdin);
    gets(auxPass);

    //busca username en el archivo

    while(buscaUsuario(fileUsuarios,auxUsername,auxPass)==0)
    {
        system("cls");
        printf("\nerror en el ingreso, intente nuevamente\n\n");

        printf("\n\tUSERNAME:\t");
        fflush(stdin);

        gets(auxUsername);
        printf("\n\tPASSWORD:\t");
        fflush(stdin);
        gets(auxPass);
    }

    //puede ingresar a:
    //1.perfil
    //1.1 modificar sus datos-> nom, apel,username,contrasenia,darse de baja
    //1.2 agregar mas contenido a favoritos
    //2.ver contenido favorito

    idUser=buscaIdUsuario (fileUsuarios,auxUsername);

    //printf("-----------%d",idUser);

    ingresoPerfilUsuario(fileUsuarios,fileContenido,idUser);

}

int buscaUsuario (char archivo [],char nomUser [], char nomPass [])
{
    FILE*pFile=fopen(archivo,"rb");
    stUsuario aux;
    int flag=0;
    //int id;

    if(pFile!=NULL)
    {
        while(flag==0 && fread(&aux,sizeof(stUsuario),1,pFile)>0)
        {
            if(strcmp(aux.userName,nomUser)==0 && strcmp(aux.password,nomPass)==0)
            {
                flag=1;
                //id=aux.idUsuario;
            }
        }
        fclose(pFile);
    }
    return flag;
}

int buscaIdUsuario (char archivo [], char auxUsername [])
{
    FILE *pFile= fopen(archivo,"rb");
    stUsuario aux;
    int id=0;

    if(pFile!=NULL)
    {
        while(fread(&aux, sizeof(stUsuario),1,pFile)>0)
        {
            if(strcmp(aux.userName,auxUsername)==0)
            {
                id=aux.idUsuario;
            }
        }
        fclose(pFile);
    }
    return id;
}

void ingresoPerfilUsuario (char archivoUs [], char archivoCon [], int id)
{
    stUsuario aux;
    char opcion;
    char control;

    do
    {
        system("cls");
        printf("\n\t\tMI PERFIL\n");
        printf("\n\n");
        printf("\n\t1.VER MI CONTENIDO FAVORITO");
        printf("\n\t2.VER CONTENIDO FAVORITO POR CATEGORIA");
        printf("\n\t3.VER CONTENIDO RECOMENDADO");
        printf("\n\t4.AGREGAR NUEVO"); //santi
        printf("\n\t5.ELIMINAR CONTENIDO");//santi
        printf("\n\n");
        printf("\n\t6.AJUSTES DE MI PERFIL\n");
        printf("\n\t0.Salir\n");
        fflush(stdin);
        opcion=getch();
        system("cls");


        switch(opcion)
        {
        case '1':

            //muestra contenido favorito
            //verContenidoFavoritoUsuario ();

            break;
        case '2':

            //se ingresa una categoria a buscar
            //buscar por categoria
            //muestra por categoria

            break;
        case '3':

            //se puede ver contenido random

            break;
        case '4':

            //poder agregar nuevo contenido

            break;
        case '5':

            //eliminar contenido

            break;
        case '6':

            //ver mi perfil
            muestraUnUsuario(aux);
            printf("\nSi desea modificar alguno de sus datos presione 's' ");
            fflush(stdin);
            scanf("%d",&control);

            if(control=='s')
            {
                //poder modificar mis datos
                modificarDatosUsuario (aux);
                //hacerModificacionUsuario(archivoUs);

            }
            break;
        }
    }
    while(opcion!='0');
}

stUsuario modificarDatosUsuario (stUsuario aux)
{
    char opcion;


    printf("\nQue desea modificar?\n");
    printf("\n1.nombre");
    printf("\n2.apellido");
    printf("\n3.username");
    printf("\n4.password");
    printf("\n5.mail");
    printf("\n6.genero");
    fflush(stdin);
    opcion=getch();

    do
    {
        switch(opcion)
        {
        case '1':
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(aux.nombre);
            break;

        case '2':
            printf("Ingrese nuevo apellido: ");
            fflush(stdin);
            gets(aux.apellido);
            break;

        case '3':
            printf("Ingrese nuevo username: ");
            fflush(stdin);
            gets(aux.userName);
            break;

        case '4':
            printf("Ingrese nueva contrasenia: ");
            fflush(stdin);
            gets(aux.password);

            break;
        case '5':
            printf("Ingrese nuevo mail: ");
            fflush(stdin);
            gets(aux.mail);

            break;
        case '6':
            printf("Ingrese nuevo genero: ");
            fflush(stdin);
            gets(aux.genero);

            break;
        }
    }
    while(opcion!='0');

    return aux;
}
/*
void hacerModificacionUsuario(char archivo[])
{
    stUsuario nuevo;
    stUsuario aux;
    int flag=0;

    FILE *pFile= fopen(archivo, "r+b");

    if(pFile!=NULL)
    {
        while(flag==0 && fread(&aux, sizeof(stUsuario), 1, pFile)>0)
        {
            if()
            {
                flag=1;
            }
        }
        if(flag==1)
        {
            fseek(pFile, (-1)*sizeof(stUsuario),SEEK_CUR);
            aux=nuevo;
            aux=modificarDatosUsuario(aux);
            fwrite(&aux, sizeof(stUsuario), 1, pFile);
        }
        else
        {
            printf("\n no se encuentra en el archivo.\n");
        }
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
    fclose(pFile);
}*/

//carga archivo de contenido

void cargaArchivoContenido (char archivo[])
{
    FILE*pFile=fopen(archivo,"ab");
    stContenido aux;
    int id= ultimoIdContenido(archivo)+1;
    char opc;
    int nro=0;

    if(pFile!=NULL)
    {
        do
        {
            aux.idContenido=id;

            printf("\nTITULO\t\t ");
            fflush(stdin);
            gets(aux.titulo);

            printf("\nDESCRIPCION\t ");
            fflush(stdin);
            gets(aux.descripcion);

            printf("\nCATEGORIA\t");
            fflush(stdin);
            gets(aux.categoria);              //elegir categorias

            aux.likes=rand()%51;

            aux.puntosPorCompartir=rand()%11;

            aux.estado=1;//1 activo 0 inactivo

            fwrite(&aux,sizeof(stContenido),1,pFile);

            printf("\nESC para salir");
            fflush(stdin);
            opc=getch();
        }
        while(opc!=27);

        fclose(pFile);
    }
    else
    {
        printf("El archivo no pudo abrirse");
    }
}

int ultimoIdContenido (char archivo [])
{
    int ultimo=0;
    stContenido aux;

    FILE*pFile= fopen(archivo, "rb");

    if(pFile)
    {
        fseek(pFile, -1*sizeof(stContenido), SEEK_END);
        if(fread(&aux,sizeof(stContenido), 1,pFile)>0)
        {
            ultimo=aux.idContenido;
        }
        fclose(pFile);
    }
    return ultimo;
}

void muestraArchivoContenido (char archivo [])
{
    FILE*pFile=fopen(archivo,"rb");
    stContenido aux;

    if(pFile!=NULL)
    {
        while(fread(&aux,sizeof(stContenido),1,pFile)>0)
        {
            muestraUnContenido(aux);
        }
        fclose(pFile);
    }
}

void muestraUnContenido (stContenido aux)
{
    printf("\nID %d",aux.idContenido);
    printf("\nTITULO\t\t%s",strupr(aux.titulo));
    printf("\nDESCRIPCION\t%s",aux.descripcion);
    printf("\nCATEGORIA\t%s",aux.categoria);
    printf("\nLIKES\t\t%d",aux.likes);
    printf("\nPUNTOS\t\t%d",aux.puntosPorCompartir);

    if(aux.estado==1)
    {
        printf("\nACTIVO\n");
    }
    else
    {
        printf("\nINACTIVO\n");
    }

}

void buscarContenidoPorCategoria ( char archivo [], char categoria[])
{
    FILE*pFile=fopen(archivo,"rb");
    stContenido aux;

    if(pFile!=NULL)
    {
        while(fread(&aux,sizeof(stContenido),1,pFile)>0)
        {
            if(strcmp(aux.categoria,categoria)==0)
            {
                muestraArchivoContenido(archivo);
            }
        }
        fclose(pFile);
    }
}

void buscarContenidoPorEstado (char archivo[],int estado)
{
    FILE*pFile=fopen(archivo,"rb");
    stContenido aux;
    if(pFile!=NULL)
    {
        while(fread(&aux,sizeof(stContenido),1,pFile)>0)
        {
            if(aux.estado ==estado)
            {
                muestraArchivoContenido(archivo);
            }
        }
        fclose(pFile);
    }
}

stContenido modificarContenido (stContenido aux)
{
    char opc;
    do
    {
        printf("\n1. modificar titulo");
        printf("\n2. modificar descripcion");
        printf("\n3. modificar categoria");
        printf("\n4. modificar estado");
        printf("\n0. salir");
        fflush(stdin);
        opc=getch();


        switch(opc)
        {
        case '1':
            printf("\nIngrese nuevo titulo ");
            fflush(stdin);
            gets(aux.titulo);
            break;
        case '2':
            printf("\nIngrese nueva descripcion ");
            fflush(stdin);
            gets(aux.descripcion);
            break;
        case '3':
            printf("\nIngrese nueva categoria");
            fflush(stdin);
            gets(aux.categoria);
            break;
        case '4':
            printf("\nIngrese nuevo estado ");
            scanf("%d",&aux.estado);
        }
    }
    while(opc!='0');

    return aux;
}

void hacerModificacionContenido (char archivo[])
{
    FILE*pFile=fopen(archivo,"r+b");
    stContenido aux;

    if(pFile!=NULL)
    {



    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct
{
    int idTipoDonacion;
    char nombre[30];
    int categoria; /// pueden ser 1, 2, 3 o 4
} stTipoDonacion;
typedef struct
{
    int idDonante;
    char nombre[30];
    float montoDonado;
    int idTipoDonacion;
} stDonante;
int color(int num)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),num);
    return 0;
}


void cargaTipoDonacion();

//EJERCICIO 1
int carga(stDonante donante[30]);
stDonante cargaIndividual();
int validacionId(int id);
//EJERCICIO 2
void muestra(stDonante donante[30],int validos);
void muestraIndividual(stDonante donante);
//EJERCICIO 3
void pasarArchivo(stDonante donante[30],int validos);
//EJERCICIO 4
void mostrarArchivo();


//EJERCICIO 5
void promedio();
float registrosA(float t);
float registrosB(float t);
int posicionA();
int posicionB();


int main()
{
    int funcion,validos;
    stDonante donante[30];
    do
    {
        system("cls");
        printf(" NUMERO | FUNCION \n");
        printf("   1    | CARGA TIPO DONACION \n");
        printf("   2    | CARGA DONANTE \n");
        printf("   3    | MUESTRA ARREGLO DONANTES \n");
        printf("   4    | PASAR DONANTES A ARCHIVOS \n");
        printf("   5    | MOSTRAR ARCHIVOS \n");
        printf("   6    | PROMEDIO \n");
        printf("   0    | TERMINAR \n");
        scanf("%i",&funcion);
        system("cls");
        switch(funcion)
        {
            case(1):
            {
                cargaTipoDonacion();
                system("cls");
            }
            break;
            case(2):
            {
                validos=carga(donante);
                system("cls");
            }
            break;
            case(3):
            {
                muestra(donante,validos);
                system("cls");
            }
            break;
            case(4):
            {
                pasarArchivo(donante,validos);
                system("cls");
            }
            break;
            case(5):
            {
                mostrarArchivo();
                system("cls");
            }
            break;
            case(6):
            {
                promedio();
                system("cls");
            }
            break;
        }
    }
    while(funcion!=0);
    return 0;
}

void cargaTipoDonacion()
{
    stTipoDonacion tipo;
    FILE *archivo=fopen("idTipoDonacion","ab");
    if(archivo!=NULL)
    {
        printf("INGRESE EL ID DEL TIPO DE DONACION: ");
        scanf("%i",&tipo.idTipoDonacion);
        printf("INGRESE EL NOMBRE: ");
        fflush(stdin);
        gets(tipo.nombre);
        printf("INGRESE LA CATEGORIA: ");
        scanf("%i",&tipo.categoria);
        fwrite(&tipo,sizeof(stTipoDonacion),1,archivo);
        fclose(archivo);
    }
}
void muestraTipoDonacion()
{
    stTipoDonacion tipo;
    FILE *archivo=fopen("idTipoDonacion","rb");
    if(archivo!=NULL)
    {
        while(fread(&tipo,sizeof(stTipoDonacion),1,archivo)>0)
        {
            printf("ID: %i ",tipo.idTipoDonacion);
            printf("NOMBRE: %s",tipo.nombre);
            printf("CATEGORIA: %i\n",tipo.categoria);
        }
        fclose(archivo);
    }
}
//EJERCICIO 1
int carga(stDonante donante[30])
{
    int i;
    char control='s';
    for(i=0;i<30 && control=='s';i++)
    {
        donante[i]=cargaIndividual();
        printf("Desea cargar otro donante? (s|n): ");
        fflush(stdin);
        scanf("%c",&control);
    }
    return i;
}
stDonante cargaIndividual()
{
    int flag=0;
    stDonante donante;
    printf("Ingrese el id del donante: ");
    scanf("%i",&donante.idDonante);
    printf("Ingrese el nombre del donante: ");
    fflush(stdin);
    gets(donante.nombre);
    printf("Ingrese el monto donado: ");
    scanf("%f",&donante.montoDonado);
    printf("Ingrese el id del tipo de donacion: ");
    scanf("%i",&donante.idTipoDonacion);
    flag=validacionId(donante.idTipoDonacion);
    while(flag==0)
    {
        printf("Ingrese un id del tipo de donacion valido: ");
        scanf("%i",&donante.idTipoDonacion);
        flag=validacionId(donante.idTipoDonacion);
    }
    return donante;
}
int validacionId(int id)
{
    int flag=0;
    stTipoDonacion aux;
    FILE *archivo=fopen("idTipoDonacion","rb");
    if(archivo!=NULL)
    {
        while(fread(&aux,sizeof(stTipoDonacion),1,archivo)>0 && flag==0)
        {
            if(aux.idTipoDonacion==id)
            {
                flag=1;
            }
        }
        fclose(archivo);
    }
    return flag;
}
//EJERCICIO 2
void muestra(stDonante donante[30],int validos)
{
    int i;
    char continuar;
    for(i=0;i<validos;i++)
    {
        muestraIndividual(donante[i]);
    }
    printf("\nENTER para volver");
    fflush(stdin);
    scanf("%c",&continuar);
}
void muestraIndividual(stDonante donante)
{
    printf("Id donante: %-2i | ",donante.idDonante);
    printf("Donante: %-20s | ",donante.nombre);
    printf("Monto: $ %6.2f | ",donante.montoDonado);
    printf("Id tipo de donacion: %i\n",donante.idTipoDonacion);
}
//EJERCICIO 3
void pasarArchivo(stDonante donante[30],int validos)
{
    int i;
    char continuar;
    for(i=0;i<validos;i++)
    {
        if(donante[i].montoDonado>25000)
        {
            FILE *archivo=fopen("donantesA","ab");
            if(archivo!=NULL)
            {
                fwrite(&donante[i],sizeof(stDonante),1,archivo);
                fclose(archivo);
            }
        }
        else
        {
            FILE *archivo=fopen("donantesB","ab");
            if(archivo!=NULL)
            {
                fwrite(&donante[i],sizeof(stDonante),1,archivo);
                fclose(archivo);
            }
        }
    }
    printf("\nENTER para volver");
    fflush(stdin);
    scanf("%c",&continuar);
}
//EJERCICIO 4
void mostrarArchivo()
{
    char continuar,tipo;
    stDonante aux;
    do
    {
        printf("Ingrese que archivo desea mostrar (A|B): ");
        fflush(stdin);
        scanf("%c",&tipo);
    }
    while(tipo!='a' && tipo!='b');
    if(tipo=='a')
    {
        FILE *archivo=fopen("donantesA","rb");
        if(archivo!=NULL)
        {
            while(fread(&aux,sizeof(stDonante),1,archivo)>0)
            {
                printf("Id donante: %-2i | ",aux.idDonante);
                printf("Donante: %-20s | ",aux.nombre);
                printf("Monto: $ %6.2f | ",aux.montoDonado);
                printf("Id tipo de donacion: %i\n",aux.idTipoDonacion);
            }
            fclose(archivo);
        }
    }
    else
    {
        FILE *archivo=fopen("donantesB","rb");
        if(archivo!=NULL)
        {
            while(fread(&aux,sizeof(stDonante),1,archivo)>0)
            {
                printf("Id donante: %-2i | ",aux.idDonante);
                printf("Donante: %-20s | ",aux.nombre);
                printf("Monto: $ %6.2f | ",aux.montoDonado);
                printf("Id tipo de donacion: %i\n",aux.idTipoDonacion);
            }
            fclose(archivo);
        }
    }
    printf("\nENTER para volver");
    fflush(stdin);
    scanf("%c",&continuar);
}
//EJERCICIO 5
void promedio()
{
    int t=sizeof(stTipoDonacion);
    printf("tamano: %i",t);
    float promedio;
    char tipo,continuar;
    do
    {
        printf("Ingrese el archivo del cual quiere saber el promedio (A|B): ");
        fflush(stdin);
        scanf("%c",&tipo);
    }
    while(tipo!='a' && tipo!='b');

    if(tipo=='a')
    {
        promedio=registrosA(t);
    }
    else
    {
        promedio=registrosB(t);
    }
    printf("Promedio: %.2f",promedio);
    printf("\nENTER para volver");
    fflush(stdin);
    scanf("%c",&continuar);
}
float registrosA(float t)
{
    float registros;
    float posicion=posicionA();
    registros=posicion/t;
    return registros;
}
float registrosB(float t)
{
    float registros;
    float posicion=posicionA();
    registros=posicion/t;
    return registros;
}

int posicionA()
{
    int posicion;
    FILE *archivo=fopen("donantesA","rb");
    if(archivo!=NULL)
    {
        fseek(archivo,0,SEEK_END);
        posicion=ftell(archivo);
        printf("pos: %i",posicion);
        system("pause");
        fclose(archivo);
    }
    return posicion;
}
int posicionB()
{
    int posicion;
    FILE *archivo=fopen("donantesB","rb");
    if(archivo!=NULL)
    {
        fseek(archivo,0,SEEK_END);
        posicion=ftell(archivo);
        fclose(archivo);
    }
    return posicion;
}











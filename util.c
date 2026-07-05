#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

void leerCadena(char *destino, int tam)
{
    char buffer[200];

    if(fgets(buffer,sizeof(buffer),stdin)==NULL)
    {
        destino[0]='\0';
        return;
    }

    if(strchr(buffer,'\n')==NULL)
    {
        int c;
        while((c=getchar())!='\n' && c!=EOF);
    }

    buffer[strcspn(buffer,"\n")]='\0';

    strncpy(destino,buffer,tam-1);
    destino[tam-1]='\0';
}

int leerEntero()
{
    char buffer[200];
    int valor;

    while(1)
    {
        if(fgets(buffer,sizeof(buffer),stdin)==NULL) return 0;

        if(strchr(buffer,'\n')==NULL)
        {
            int c;
            while((c=getchar())!='\n' && c!=EOF);
        }

        if(sscanf(buffer,"%d",&valor)==1) return valor;

        printf("Entrada invalida, ingrese un numero entero: ");
    }
}

float leerFlotante()
{
    char buffer[200];
    float valor;

    while(1)
    {
        if(fgets(buffer,sizeof(buffer),stdin)==NULL) return 0;

        if(strchr(buffer,'\n')==NULL)
        {
            int c;
            while((c=getchar())!='\n' && c!=EOF);
        }

        if(sscanf(buffer,"%f",&valor)==1) return valor;

        printf("Entrada invalida, ingrese un numero: ");
    }
}

int fechaValida(char *fecha)
{
    int dia, mes, anio, esBisiesto;
    int diasMes[]={31,28,31,30,31,30,31,31,30,31,30,31};

    if(sscanf(fecha,"%d/%d/%d",&dia,&mes,&anio)!=3) return 0;
    if(mes<1 || mes>12) return 0;
    if(anio<1900 || anio>2100) return 0;

    esBisiesto = (anio%4==0 && anio%100!=0) || (anio%400==0);
    if(mes==2 && esBisiesto) diasMes[1]=29;

    if(dia<1 || dia>diasMes[mes-1]) return 0;

    return 1;
}

long fechaAValor(char *fecha)
{
    int dia, mes, anio;
    sscanf(fecha,"%d/%d/%d",&dia,&mes,&anio);
    return (long)anio*10000 + mes*100 + dia;
}
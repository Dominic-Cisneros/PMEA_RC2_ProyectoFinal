#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "registro.h"
#include "archivo.h"

#define NOMBRE_ARCHIVO "produccion_turnos.csv"

void cargarDatos()
{
    FILE *archivo = fopen(NOMBRE_ARCHIVO,"r");
    char linea[500];

    if(archivo==NULL) return;

    fgets(linea,sizeof(linea),archivo);

    while(fgets(linea,sizeof(linea),archivo)!=NULL && totalRegistros<MAX_REGISTROS)
    {
        Registro r;
        char *campos[8];
        int i, camposValidos=1;

        campos[0]=strtok(linea,";\n");
        for(i=1;i<8;i++)
            campos[i]=strtok(NULL,";\n");

        for(i=0;i<8;i++)
            if(campos[i]==NULL) camposValidos=0;

        if(!camposValidos) continue;

        strncpy(r.codigo_registro,campos[0],MAX_COD-1); r.codigo_registro[MAX_COD-1]='\0';
        strncpy(r.fecha,campos[1],MAX_FECHA-1); r.fecha[MAX_FECHA-1]='\0';
        strncpy(r.centro_costo,campos[2],MAX_CENTRO-1); r.centro_costo[MAX_CENTRO-1]='\0';
        r.turno=atoi(campos[3]);
        r.materia_prima_kg=(float)atof(campos[4]);
        r.desperdicio_kg=(float)atof(campos[5]);
        r.tiempo_min=atoi(campos[6]);
        r.unidades_producidas=atoi(campos[7]);

        if(r.turno<1 || r.turno>3) continue;
        if(r.materia_prima_kg<0 || r.desperdicio_kg<0 || r.desperdicio_kg>r.materia_prima_kg) continue;
        if(existeCodigo(r.codigo_registro)) continue;

        registros[totalRegistros]=r;
        totalRegistros++;
    }

    fclose(archivo);
}

void guardarDatos()
{
    FILE *archivo = fopen(NOMBRE_ARCHIVO,"w");
    int i;

    if(archivo==NULL){ printf("\nNo se pudo guardar el archivo.\n"); return; }

    fprintf(archivo,"codigo_registro,fecha,centro_costo,turno,materia_prima_kg,desperdicio_kg,tiempo_min,unidades_producidas\n");

    for(i=0;i<totalRegistros;i++)
    {
        fprintf(archivo,"%s;%s;%s;%d;%.2f;%.2f;%d;%d\n",
            registros[i].codigo_registro,
            registros[i].fecha,
            registros[i].centro_costo,
            registros[i].turno,
            registros[i].materia_prima_kg,
            registros[i].desperdicio_kg,
            registros[i].tiempo_min,
            registros[i].unidades_producidas);
    }

    fclose(archivo);
    printf("\nDatos guardados correctamente.\n");
}
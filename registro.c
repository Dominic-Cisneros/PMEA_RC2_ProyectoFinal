#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "registro.h"
#include "util.h"

Registro registros[MAX_REGISTROS];
int totalRegistros = 0;

int existeCodigo(char *codigo)
{
    int i;
    for(i=0;i<totalRegistros;i++)
        if(strcmp(registros[i].codigo_registro,codigo)==0)
            return 1;
    return 0;
}

int existeDuplicado(char *fecha, char *centro, int turno, char *codigoExcluir)
{
    int i;
    for(i=0;i<totalRegistros;i++)
    {
        if(strcmp(registros[i].codigo_registro,codigoExcluir)==0)
            continue;

        if(strcmp(registros[i].fecha,fecha)==0 &&
           strcmp(registros[i].centro_costo,centro)==0 &&
           registros[i].turno==turno)
            return 1;
    }
    return 0;
}

float calcularRendimiento(Registro *r)
{
    if(r->materia_prima_kg > 0)
        return ((r->materia_prima_kg - r->desperdicio_kg) / r->materia_prima_kg) * 100;
    return 0;
}

void registrarTurno()
{
    Registro r;

    if(totalRegistros>=MAX_REGISTROS){ printf("\nNo se pueden registrar mas turnos.\n"); return; }

    do
    {
        printf("\nIngrese el codigo de registro (1-15 caracteres, sin espacios): ");
        leerCadena(r.codigo_registro,MAX_COD);

        if(strlen(r.codigo_registro)==0 || strchr(r.codigo_registro,' ')!=NULL)
            printf("Codigo invalido, no puede estar vacio ni contener espacios.\n");
        else if(existeCodigo(r.codigo_registro))
            printf("El codigo ya existe.\n");
        else
            break;

    } while(1);

    do
    {
        printf("Ingrese la fecha (DD/MM/AAAA): ");
        leerCadena(r.fecha,MAX_FECHA);

        if(!fechaValida(r.fecha))
            printf("Fecha invalida.\n");
        else
            break;

    } while(1);

    do
    {
        printf("Ingrese el centro de costo: ");
        leerCadena(r.centro_costo,MAX_CENTRO);

        if(strlen(r.centro_costo)==0)
            printf("El centro de costo no puede estar vacio.\n");
        else
            break;

    } while(1);

    do
    {
        printf("Ingrese el turno (1, 2 o 3): ");
        r.turno = leerEntero();

        if(r.turno<1 || r.turno>3)
        {
            printf("Turno invalido.\n");
            continue;
        }

        if(existeDuplicado(r.fecha,r.centro_costo,r.turno,""))
        {
            printf("Ya existe un registro para esa fecha, centro y turno.\n");
            continue;
        }

        break;

    } while(1);

    do
    {
        printf("Ingrese la materia prima (kg): ");
        r.materia_prima_kg = leerFlotante();

        printf("Ingrese el desperdicio (kg): ");
        r.desperdicio_kg = leerFlotante();

        if(r.materia_prima_kg<0 || r.desperdicio_kg<0 || r.desperdicio_kg>r.materia_prima_kg)
            printf("Valores invalidos: deben ser positivos y el desperdicio no puede superar la materia prima.\n");
        else
            break;

    } while(1);

    do
    {
        printf("Ingrese el tiempo (min): ");
        r.tiempo_min = leerEntero();

        printf("Ingrese las unidades producidas: ");
        r.unidades_producidas = leerEntero();

        if(r.tiempo_min<0 || r.unidades_producidas<0)
            printf("Valores invalidos, deben ser mayores o iguales a 0.\n");
        else
            break;

    } while(1);

    registros[totalRegistros] = r;
    totalRegistros++;

    printf("\nTurno registrado correctamente.\n");
}

void listarRegistros()
{
    int i;

    if(totalRegistros==0){ printf("\nNo existen registros.\n"); return; }

    printf("\n========== REGISTROS ==========\n");

    for(i=0;i<totalRegistros;i++)
    {
        printf("\nCodigo: %s\n",registros[i].codigo_registro);
        printf("Fecha: %s\n",registros[i].fecha);
        printf("Centro de costo: %s\n",registros[i].centro_costo);
        printf("Turno: %d\n",registros[i].turno);
        printf("Materia prima (kg): %.2f\n",registros[i].materia_prima_kg);
        printf("Desperdicio (kg): %.2f\n",registros[i].desperdicio_kg);
        printf("Tiempo (min): %d\n",registros[i].tiempo_min);
        printf("Unidades producidas: %d\n",registros[i].unidades_producidas);
        printf("Rendimiento: %.2f%%\n",calcularRendimiento(&registros[i]));
    }
}

void buscarRegistro()
{
    int modo, i, encontrados=0;

    if(totalRegistros==0){ printf("\nNo existen registros.\n"); return; }

    printf("\nBuscar por: 1) Codigo exacto  2) Filtros (fecha/centro/turno)\n");
    printf("Seleccione una opcion: ");
    modo = leerEntero();

    if(modo==1)
    {
        char codigo[MAX_COD];

        printf("Ingrese el codigo de registro a buscar: ");
        leerCadena(codigo,MAX_COD);

        for(i=0;i<totalRegistros;i++)
        {
            if(strcmp(registros[i].codigo_registro,codigo)==0)
            {
                printf("\nCodigo: %s\n",registros[i].codigo_registro);
                printf("Fecha: %s\n",registros[i].fecha);
                printf("Centro de costo: %s\n",registros[i].centro_costo);
                printf("Turno: %d\n",registros[i].turno);
                printf("Materia prima (kg): %.2f\n",registros[i].materia_prima_kg);
                printf("Desperdicio (kg): %.2f\n",registros[i].desperdicio_kg);
                printf("Tiempo (min): %d\n",registros[i].tiempo_min);
                printf("Unidades producidas: %d\n",registros[i].unidades_producidas);
                printf("Rendimiento: %.2f%%\n",calcularRendimiento(&registros[i]));
                encontrados++;
                break;
            }
        }
    }
    else if(modo==2)
    {
        char fecha[MAX_FECHA], centro[MAX_CENTRO];
        int turno;

        printf("Fecha (DD/MM/AAAA) o Enter para omitir: ");
        leerCadena(fecha,MAX_FECHA);

        printf("Centro de costo o Enter para omitir: ");
        leerCadena(centro,MAX_CENTRO);

        printf("Turno (1,2,3) o 0 para omitir: ");
        turno = leerEntero();

        for(i=0;i<totalRegistros;i++)
        {
            if(strlen(fecha)>0 && strcmp(registros[i].fecha,fecha)!=0) continue;
            if(strlen(centro)>0 && strcmp(registros[i].centro_costo,centro)!=0) continue;
            if(turno!=0 && registros[i].turno!=turno) continue;

            printf("\nCodigo: %s\n",registros[i].codigo_registro);
            printf("Fecha: %s\n",registros[i].fecha);
            printf("Centro de costo: %s\n",registros[i].centro_costo);
            printf("Turno: %d\n",registros[i].turno);
            printf("Materia prima (kg): %.2f\n",registros[i].materia_prima_kg);
            printf("Desperdicio (kg): %.2f\n",registros[i].desperdicio_kg);
            printf("Tiempo (min): %d\n",registros[i].tiempo_min);
            printf("Unidades producidas: %d\n",registros[i].unidades_producidas);
            printf("Rendimiento: %.2f%%\n",calcularRendimiento(&registros[i]));
            encontrados++;
        }
    }
    else
    {
        printf("\nOpcion invalida.\n");
        return;
    }

    if(encontrados==0) printf("\nNo se encontraron registros.\n");
}

void actualizarRegistro()
{
    char codigo[MAX_COD];
    char entrada[50];
    int i, encontrado=0;
    Registro temp;

    if(totalRegistros==0){ printf("\nNo existen registros.\n"); return; }

    printf("\nIngrese el codigo del registro a actualizar: ");
    leerCadena(codigo,MAX_COD);

    for(i=0;i<totalRegistros;i++)
    {
        if(strcmp(registros[i].codigo_registro,codigo)==0)
        {
            encontrado=1;
            temp = registros[i];

            printf("\nDeje el campo vacio, o ingrese -1/0 segun se indique, para mantener el valor actual.\n");

            do
            {
                printf("Fecha actual [%s], nueva (DD/MM/AAAA) o Enter para mantener: ",temp.fecha);
                leerCadena(entrada,MAX_FECHA);

                if(strlen(entrada)==0) break;

                if(!fechaValida(entrada))
                {
                    printf("Fecha invalida.\n");
                    continue;
                }

                strcpy(temp.fecha,entrada);
                break;

            } while(1);

            printf("Centro de costo actual [%s], nuevo o Enter para mantener: ",temp.centro_costo);
            leerCadena(entrada,MAX_CENTRO);
            if(strlen(entrada)>0) strcpy(temp.centro_costo,entrada);

            do
            {
                int nuevoTurno;

                printf("Turno actual [%d], nuevo (1,2,3) o 0 para mantener: ",temp.turno);
                nuevoTurno = leerEntero();

                if(nuevoTurno==0) break;

                if(nuevoTurno<1 || nuevoTurno>3)
                {
                    printf("Turno invalido.\n");
                    continue;
                }

                temp.turno = nuevoTurno;
                break;

            } while(1);

            if(existeDuplicado(temp.fecha,temp.centro_costo,temp.turno,codigo))
            {
                printf("\nYa existe otro registro con esa fecha, centro y turno. No se actualizo.\n");
                return;
            }

            do
            {
                float nuevaMateria, nuevoDesperdicio, materiaFinal, desperdicioFinal;

                printf("Materia prima actual [%.2f] kg, nueva o -1 para mantener: ",temp.materia_prima_kg);
                nuevaMateria = leerFlotante();
                materiaFinal = (nuevaMateria<0) ? temp.materia_prima_kg : nuevaMateria;

                printf("Desperdicio actual [%.2f] kg, nuevo o -1 para mantener: ",temp.desperdicio_kg);
                nuevoDesperdicio = leerFlotante();
                desperdicioFinal = (nuevoDesperdicio<0) ? temp.desperdicio_kg : nuevoDesperdicio;

                if(desperdicioFinal>materiaFinal)
                {
                    printf("El desperdicio no puede superar la materia prima.\n");
                    continue;
                }

                temp.materia_prima_kg = materiaFinal;
                temp.desperdicio_kg = desperdicioFinal;
                break;

            } while(1);

            do
            {
                int nuevoTiempo, nuevasUnidades;

                printf("Tiempo actual [%d] min, nuevo o -1 para mantener: ",temp.tiempo_min);
                nuevoTiempo = leerEntero();

                printf("Unidades producidas actual [%d], nuevas o -1 para mantener: ",temp.unidades_producidas);
                nuevasUnidades = leerEntero();

                temp.tiempo_min = (nuevoTiempo<0) ? temp.tiempo_min : nuevoTiempo;
                temp.unidades_producidas = (nuevasUnidades<0) ? temp.unidades_producidas : nuevasUnidades;

                break;

            } while(1);

            registros[i] = temp;
            printf("\nRegistro actualizado correctamente.\n");
            break;
        }
    }

    if(!encontrado) printf("\nRegistro no encontrado.\n");
}

void eliminarRegistro()
{
    char codigo[MAX_COD];
    char confirmacion[10];
    int i, j, encontrado=0;

    if(totalRegistros==0){ printf("\nNo existen registros.\n"); return; }

    printf("\nIngrese el codigo del registro a eliminar: ");
    leerCadena(codigo,MAX_COD);

    for(i=0;i<totalRegistros;i++)
    {
        if(strcmp(registros[i].codigo_registro,codigo)==0)
        {
            encontrado=1;

            printf("Esta seguro que desea eliminar el registro %s? (si/no): ",codigo);
            leerCadena(confirmacion,sizeof(confirmacion));

            if(confirmacion[0]!='s' && confirmacion[0]!='S')
            {
                printf("\nEliminacion cancelada.\n");
                return;
            }

            for(j=i;j<totalRegistros-1;j++)
                registros[j] = registros[j+1];

            totalRegistros--;
            printf("\nRegistro eliminado correctamente.\n");
            break;
        }
    }

    if(!encontrado) printf("\nRegistro no encontrado.\n");
}

void reportePorCentro()
{
    char centro[MAX_CENTRO];
    char fechaInicio[MAX_FECHA], fechaFin[MAX_FECHA];
    float desperdicioTurno[3] = {0,0,0};
    long valorInicio, valorFin, valorActual;
    int i, encontrado=0, turnoMenor, turnoIdx;

    if(totalRegistros==0){ printf("\nNo existen registros.\n"); return; }

    printf("\nIngrese el centro de costo: ");
    leerCadena(centro,MAX_CENTRO);

    do
    {
        printf("Fecha inicio (DD/MM/AAAA): ");
        leerCadena(fechaInicio,MAX_FECHA);
        if(!fechaValida(fechaInicio)) printf("Fecha invalida.\n");
    } while(!fechaValida(fechaInicio));

    do
    {
        printf("Fecha fin (DD/MM/AAAA): ");
        leerCadena(fechaFin,MAX_FECHA);
        if(!fechaValida(fechaFin)) printf("Fecha invalida.\n");
    } while(!fechaValida(fechaFin));

    valorInicio = fechaAValor(fechaInicio);
    valorFin = fechaAValor(fechaFin);

    if(valorInicio>valorFin)
    {
        printf("\nLa fecha de inicio no puede ser posterior a la fecha fin.\n");
        return;
    }

    for(i=0;i<totalRegistros;i++)
    {
        turnoIdx = registros[i].turno - 1;
        if(turnoIdx<0 || turnoIdx>2) continue;

        if(strcmp(registros[i].centro_costo,centro)!=0) continue;

        valorActual = fechaAValor(registros[i].fecha);
        if(valorActual<valorInicio || valorActual>valorFin) continue;

        desperdicioTurno[turnoIdx] += registros[i].desperdicio_kg;
        encontrado=1;
    }

    if(!encontrado){ printf("\nNo hay registros para ese centro y rango de fechas.\n"); return; }

    turnoMenor=0;
    for(i=1;i<3;i++)
        if(desperdicioTurno[i]<desperdicioTurno[turnoMenor])
            turnoMenor=i;

    printf("\n===== REPORTE POR CENTRO DE COSTO =====\n");
    printf("Centro de costo: %s\n",centro);
    printf("Desperdicio turno 1: %.2f kg\n",desperdicioTurno[0]);
    printf("Desperdicio turno 2: %.2f kg\n",desperdicioTurno[1]);
    printf("Desperdicio turno 3: %.2f kg\n",desperdicioTurno[2]);
    printf("Turno con menor desperdicio: %d\n",turnoMenor+1);
}
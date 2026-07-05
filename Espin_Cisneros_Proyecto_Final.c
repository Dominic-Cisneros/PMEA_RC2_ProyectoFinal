#include <stdio.h>
#include "registro.h"
#include "archivo.h"
#include "util.h"

void menu();

int main()
{
    int opcion = -1;

    cargarDatos();

    while(opcion != 0)
    {
        menu();

        printf("\nSeleccione una opcion: ");
        opcion = leerEntero();

        switch(opcion)
        {
            case 1: registrarTurno(); break;
            case 2: listarRegistros(); break;
            case 3: buscarRegistro(); break;
            case 4: actualizarRegistro(); break;
            case 5: eliminarRegistro(); break;
            case 6: reportePorCentro(); break;
            case 7: guardarDatos(); break;
            case 0: guardarDatos(); printf("\nGracias por utilizar el sistema.\n"); break;
            default: printf("\nOpcion invalida.\n");
        }
    }
    return 0;
}

void menu()
{
    printf("\n=================================\n");
    printf("  CONTROL DE PRODUCCION POR TURNO\n");
    printf("=================================\n");
    printf("1. Registrar turno\n");
    printf("2. Listar registros\n");
    printf("3. Buscar registro\n");
    printf("4. Actualizar registro\n");
    printf("5. Eliminar registro\n");
    printf("6. Reporte por centro de costo\n");
    printf("7. Guardar cambios\n");
    printf("0. Salir\n");
}
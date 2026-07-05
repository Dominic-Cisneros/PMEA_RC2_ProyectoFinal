#include <stdio.h>

void menu();

int main()
{
    int opcion = -1;

    while (opcion != 0)
    {
        menu();

        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                printf("\nRegistrar libro.\n");
                break;

            case 2:
                printf("\nMostrar libros.\n");
                break;

            case 3:
                printf("\nBuscar libro.\n");
                break;

            case 4:
                printf("\nEditar libro.\n");
                break;

            case 5:
                printf("\nEliminar libro.\n");
                break;

            case 0:
                printf("\nGracias por utilizar el sistema.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }
    }

    return 0;
}

void menu()
{
    printf("\n=================================\n");
    printf("   SISTEMA DE BIBLIOTECA\n");
    printf("=================================\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar libros\n");
    printf("3. Buscar libro\n");
    printf("4. Editar libro\n");
    printf("5. Eliminar libro\n");
    printf("0. Salir\n");
}
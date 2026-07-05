#include <stdio.h>
#include <string.h>

void menu();
void registrarLibro();
void mostrarLibros();
void buscarLibro();
void editarLibro();
void eliminarLibro();

char titulos[50][50];
char autores[50][50];
int anios[50];

int cantidadLibros = 0;

int main()
{
    int opcion = -1;

    while(opcion != 0)
    {
        menu();

        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                registrarLibro();
                break;

            case 2:
                mostrarLibros();
                break;

            case 3:
                buscarLibro();
                break;

            case 4:
                editarLibro();
                break;

            case 5:
                eliminarLibro();
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
    printf("     SISTEMA DE BIBLIOTECA\n");
    printf("=================================\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar libros\n");
    printf("3. Buscar libro\n");
    printf("4. Editar libro\n");
    printf("5. Eliminar libro\n");
    printf("0. Salir\n");
}

void registrarLibro()
{
    if(cantidadLibros >= 50)
    {
        printf("\nNo se pueden registrar mas libros.\n");
        return;
    }

    getchar();

    printf("\nIngrese el titulo: ");
    fgets(titulos[cantidadLibros],50,stdin);
    titulos[cantidadLibros][strcspn(titulos[cantidadLibros],"\n")] = '\0';

    printf("Ingrese el autor: ");
    fgets(autores[cantidadLibros],50,stdin);
    autores[cantidadLibros][strcspn(autores[cantidadLibros],"\n")] = '\0';

    printf("Ingrese el anio: ");
    scanf("%d",&anios[cantidadLibros]);

    cantidadLibros++;

    printf("\nLibro registrado correctamente.\n");
}

void mostrarLibros()
{
    if(cantidadLibros == 0)
    {
        printf("\nNo existen libros registrados.\n");
        return;
    }

    printf("\n========== LIBROS ==========\n");

    for(int i=0;i<cantidadLibros;i++)
    {
        printf("\nLibro %d\n",i+1);
        printf("Titulo: %s\n",titulos[i]);
        printf("Autor : %s\n",autores[i]);
        printf("Anio  : %d\n",anios[i]);
    }
}

void buscarLibro()
{
    char tituloBuscar[50];
    int encontrado = 0;

    if(cantidadLibros == 0)
    {
        printf("\nNo existen libros registrados.\n");
        return;
    }

    getchar();

    printf("\nIngrese el titulo del libro: ");
    fgets(tituloBuscar,50,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")] = '\0';

    for(int i=0;i<cantidadLibros;i++)
    {
        if(strcmp(tituloBuscar,titulos[i]) == 0)
        {
            printf("\nLibro encontrado.\n");
            printf("Titulo: %s\n",titulos[i]);
            printf("Autor : %s\n",autores[i]);
            printf("Anio  : %d\n",anios[i]);
            encontrado = 1;
        }
    }

    if(encontrado == 0)
    {
        printf("\nLibro no encontrado.\n");
    }
}

void editarLibro()
{
    char tituloBuscar[50];
    int encontrado = 0;

    if(cantidadLibros == 0)
    {
        printf("\nNo existen libros registrados.\n");
        return;
    }

    getchar();

    printf("\nIngrese el titulo del libro que desea editar: ");
    fgets(tituloBuscar,50,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")] = '\0';

    for(int i=0;i<cantidadLibros;i++)
    {
        if(strcmp(tituloBuscar,titulos[i]) == 0)
        {
            printf("\nNuevo titulo: ");
            fgets(titulos[i],50,stdin);
            titulos[i][strcspn(titulos[i],"\n")] = '\0';

            printf("Nuevo autor: ");
            fgets(autores[i],50,stdin);
            autores[i][strcspn(autores[i],"\n")] = '\0';

            printf("Nuevo anio: ");
            scanf("%d",&anios[i]);

            printf("\nLibro editado correctamente.\n");
            encontrado = 1;
            break;
        }
    }

    if(encontrado == 0)
    {
        printf("\nLibro no encontrado.\n");
    }
}

void eliminarLibro()
{
    char tituloBuscar[50];
    int encontrado = 0;

    if(cantidadLibros == 0)
    {
        printf("\nNo existen libros registrados.\n");
        return;
    }

    getchar();

    printf("\nIngrese el titulo del libro que desea eliminar: ");
    fgets(tituloBuscar,50,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")] = '\0';

    for(int i=0;i<cantidadLibros;i++)
    {
        if(strcmp(tituloBuscar,titulos[i]) == 0)
        {
            for(int j=i;j<cantidadLibros-1;j++)
            {
                strcpy(titulos[j],titulos[j+1]);
                strcpy(autores[j],autores[j+1]);
                anios[j]=anios[j+1];
            }

            cantidadLibros--;

            printf("\nLibro eliminado correctamente.\n");

            encontrado = 1;
            break;
        }
    }

    if(encontrado == 0)
    {
        printf("\nLibro no encontrado.\n");
    }
}
#include <stdio.h>
#include <string.h>

void menu();
void registrarLibro();
void mostrarLibros();
void buscarLibro();
void editarLibro();
void eliminarLibro();
void estadisticas();

char titulos[50][50];
char autores[50][50];
char categorias[50][30];
int anios[50];
int cantidadLibros = 0;

int main()
{
    int opcion = -1;

    while(opcion != 0)
    {
        menu();

        printf("\nSeleccione una opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: editarLibro(); break;
            case 5: eliminarLibro(); break;
            case 6: estadisticas(); break;
            case 0: printf("\nGracias por utilizar el sistema.\n"); break;
            default: printf("\nOpcion invalida.\n");
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
    printf("6. Estadisticas\n");
    printf("0. Salir\n");
}

void registrarLibro()
{
    if(cantidadLibros>=50){ printf("\nNo se pueden registrar mas libros.\n"); return; }

    getchar();

    printf("\nIngrese el titulo: ");
    fgets(titulos[cantidadLibros],50,stdin);
    titulos[cantidadLibros][strcspn(titulos[cantidadLibros],"\n")]='\0';

    printf("Ingrese el autor: ");
    fgets(autores[cantidadLibros],50,stdin);
    autores[cantidadLibros][strcspn(autores[cantidadLibros],"\n")]='\0';

    printf("Ingrese la categoria: ");
    fgets(categorias[cantidadLibros],30,stdin);
    categorias[cantidadLibros][strcspn(categorias[cantidadLibros],"\n")]='\0';

    printf("Ingrese el anio: ");
    scanf("%d",&anios[cantidadLibros]);

    cantidadLibros++;
    printf("\nLibro registrado correctamente.\n");
}

void mostrarLibros()
{
    int i;
    if(cantidadLibros==0){ printf("\nNo existen libros registrados.\n"); return; }

    printf("\n========== LIBROS ==========\n");

    for(i=0;i<cantidadLibros;i++)
    {
        printf("\nLibro %d\n",i+1);
        printf("Titulo: %s\n",titulos[i]);
        printf("Autor: %s\n",autores[i]);
        printf("Categoria: %s\n",categorias[i]);
        printf("Anio: %d\n",anios[i]);
    }
}

void buscarLibro()
{
    char tituloBuscar[50];
    int i,encontrado=0;

    if(cantidadLibros==0){ printf("\nNo existen libros registrados.\n"); return; }

    getchar();
    printf("\nIngrese el titulo: ");
    fgets(tituloBuscar,50,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")]='\0';

    for(i=0;i<cantidadLibros;i++)
    {
        if(strcmp(tituloBuscar,titulos[i])==0)
        {
            printf("\nTitulo: %s\n",titulos[i]);
            printf("Autor: %s\n",autores[i]);
            printf("Categoria: %s\n",categorias[i]);
            printf("Anio: %d\n",anios[i]);
            encontrado=1;
        }
    }

    if(!encontrado) printf("\nLibro no encontrado.\n");
}

void editarLibro()
{
    char tituloBuscar[50];
    int i,encontrado=0;

    if(cantidadLibros==0){ printf("\nNo existen libros registrados.\n"); return; }

    getchar();
    printf("\nIngrese el titulo del libro a editar: ");
    fgets(tituloBuscar,50,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")]='\0';

    for(i=0;i<cantidadLibros;i++)
    {
        if(strcmp(tituloBuscar,titulos[i])==0)
        {
            printf("Nuevo titulo: ");
            fgets(titulos[i],50,stdin);
            titulos[i][strcspn(titulos[i],"\n")]='\0';

            printf("Nuevo autor: ");
            fgets(autores[i],50,stdin);
            autores[i][strcspn(autores[i],"\n")]='\0';

            printf("Nueva categoria: ");
            fgets(categorias[i],30,stdin);
            categorias[i][strcspn(categorias[i],"\n")]='\0';

            printf("Nuevo anio: ");
            scanf("%d",&anios[i]);

            printf("\nLibro editado correctamente.\n");
            encontrado=1;
            break;
        }
    }

    if(!encontrado) printf("\nLibro no encontrado.\n");
}

void eliminarLibro()
{
    char tituloBuscar[50];
    int i,j,encontrado=0;

    if(cantidadLibros==0){ printf("\nNo existen libros registrados.\n"); return; }

    getchar();
    printf("\nIngrese el titulo del libro a eliminar: ");
    fgets(tituloBuscar,50,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")]='\0';

    for(i=0;i<cantidadLibros;i++)
    {
        if(strcmp(tituloBuscar,titulos[i])==0)
        {
            for(j=i;j<cantidadLibros-1;j++)
            {
                strcpy(titulos[j],titulos[j+1]);
                strcpy(autores[j],autores[j+1]);
                strcpy(categorias[j],categorias[j+1]);
                anios[j]=anios[j+1];
            }
            cantidadLibros--;
            printf("\nLibro eliminado correctamente.\n");
            encontrado=1;
            break;
        }
    }

    if(!encontrado) printf("\nLibro no encontrado.\n");
}

void estadisticas()
{
    int antiguos=0,nuevos=0,i;

    if(cantidadLibros==0)
    {
        printf("\nNo existen libros registrados.\n");
        return;
    }

    for(i=0;i<cantidadLibros;i++)
    {
        if(anios[i]<2000)
            antiguos++;
        else
            nuevos++;
    }

    printf("\n===== ESTADISTICAS =====\n");
    printf("Total de libros: %d\n",cantidadLibros);
    printf("Antes del 2000: %d\n",antiguos);
    printf("Desde el 2000: %d\n",nuevos);
}
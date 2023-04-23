#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea {
    int TareaID;                    //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;                   // entre 10 – 100
} typedef Tarea;

void cargarTareas(Tarea **tareaPendiente, int num);
void pendienteToRealizada(Tarea **tareaPendiente, Tarea **tareaRealizada, int num);
void mostrarTareas(Tarea **tareaPendiente, Tarea **tareaRealizada, int num);
void BuscarTarea(Tarea **tareaPendiente, Tarea **tareaRealizada, int num);

int main()
{
    Tarea **trabajoPendiente, **trabajoRealizado;
    int num;

    printf("Cuantas tareas debe realizar?: ");
    scanf("%d", &num);
    trabajoPendiente = (Tarea **)malloc(num*sizeof(Tarea *));
    trabajoRealizado = (Tarea **)malloc(num*sizeof(Tarea *));

    cargarTareas(trabajoPendiente, num);
    pendienteToRealizada(trabajoPendiente, trabajoRealizado, num);
    mostrarTareas(trabajoPendiente, trabajoRealizado, num);
    BuscarTarea(trabajoPendiente, trabajoRealizado, num);

    free(trabajoPendiente);
    free(trabajoRealizado);

    return 0;
}

void cargarTareas(Tarea **tareaPendiente, int num)
{
    int i;
    char *Buff;

    for(i=0; i<num; i++)
    {
        tareaPendiente[i] = NULL;
    }

    for(i=0; i<num; i++)
    {
        tareaPendiente[i] = (Tarea *)malloc(sizeof(Tarea));
        fflush(stdin);
        printf("\nTarea %d", i+1);
        tareaPendiente[i]->TareaID = i+1;
        Buff = (char *)malloc(50*sizeof(char));
        printf("\nDescripcion: ");
        gets(Buff);
        tareaPendiente[i]->Descripcion = (char *)malloc((strlen(Buff)+1)*sizeof(char));
        strcpy(tareaPendiente[i]->Descripcion, Buff);
        printf("Duracion: ");
        scanf("%d", &tareaPendiente[i]->Duracion);
        printf("\n");
        free(Buff);
    }
}

void pendienteToRealizada(Tarea **tareaPendiente, Tarea **tareaRealizada, int num)
{
    int i, aux;

    for(i=0; i<num; i++)
    {
        tareaRealizada[i] = NULL;
    }

    for(i=0; i<num; i++)
    {
        aux = 0;
        printf("\nTarea %d\n", tareaPendiente[i]->TareaID);
        printf("%s\n", tareaPendiente[i]->Descripcion);
        printf("Duracion: %d\n", tareaPendiente[i]->Duracion);
        printf("Se realizo esta tarea? (1=Si, 0=No): ");
        scanf("%d", &aux);
        if(aux)
        {
            tareaRealizada[i] = (Tarea *)malloc(sizeof(Tarea));
            tareaRealizada[i]->TareaID = tareaPendiente[i]->TareaID;
            tareaRealizada[i]->Descripcion = (char *)malloc(strlen(tareaPendiente[i]->Descripcion)*sizeof(char));
            strcpy(tareaRealizada[i]->Descripcion, tareaPendiente[i]->Descripcion);
            tareaRealizada[i]->Duracion = tareaPendiente[i]->Duracion;
            free(tareaPendiente[i]);
            tareaPendiente[i] = NULL;
        }
    }
}

void mostrarTareas(Tarea **tareaPendiente, Tarea **tareaRealizada, int num)
{
    int i;

    printf("\n\n****Tareas realizadas****");
    for(i=0; i<num; i++)
    {
        if(tareaRealizada[i] != NULL)
        {
            printf("\nTarea %d\n", tareaRealizada[i]->TareaID);
            printf("%s\n", tareaRealizada[i]->Descripcion);
            printf("Duracion: %d\n\n", tareaRealizada[i]->Duracion);
        }
    }
    printf("****Tareas pendientes****");
    for(i=0; i<num; i++)
    {
        if(tareaPendiente[i] != NULL)
        {
            printf("\nTarea %d\n", tareaPendiente[i]->TareaID);
            printf("%s\n", tareaPendiente[i]->Descripcion);
            printf("Duracion: %d\n\n", tareaPendiente[i]->Duracion);
        }
    }
}

void BuscarTarea(Tarea **tareaPendiente, Tarea **tareaRealizada, int num)
{
    int i=0, j;
    char palabra[20], *aux1, *aux2;

    fflush(stdin);
    printf("Que tarea quiere ver?\nIngrese una palabra de la descripcion: ");
    gets(palabra);
    
    while(!aux1 || !aux2 || i==num)
    {
        if(tareaPendiente[i] != NULL)
        {
            aux1 = strstr(tareaPendiente[i]->Descripcion, palabra);
            j = i;
        }
        if(tareaRealizada[i] != NULL)
        {
            aux2 = strstr(tareaRealizada[i]->Descripcion, palabra);
            j = i;
        }
        i++;
    }

    if(aux1 || aux2)
    {
        if(aux1)
        {
            printf("**Tarea encontrada**\nTarea %d\n", tareaPendiente[j]->TareaID);
            printf("%s\n", tareaPendiente[j]->Descripcion);
            printf("Duracion: %d", tareaPendiente[j]->Duracion);
        }
        if(aux2)
        {
            printf("**Tarea encontrada**\nTarea %d\n", tareaRealizada[j]->TareaID);
            printf("%s\n", tareaRealizada[j]->Descripcion);
            printf("Duracion: %d", tareaRealizada[j]->Duracion);
        }
    }
    else
    {
        printf("**Tarea no encontrada**");
    }
    
}
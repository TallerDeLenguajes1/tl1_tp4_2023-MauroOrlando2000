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
void BuscarTareaPorId(Tarea **tareaPendiente, Tarea **tareaRealizada);
void BuscarTareaPorPalabra(Tarea **tareaPendiente, Tarea **tareaRealizada, int num);

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
    BuscarTareaPorId(trabajoPendiente, trabajoRealizado);
    BuscarTareaPorPalabra(trabajoPendiente, trabajoRealizado, num);

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

void BuscarTareaPorId(Tarea **tareaPendiente, Tarea **tareaRealizada)
{
    int aux, aux2=1;

    printf("Que tarea quiere ver?: ");
    scanf("%d", &aux);
    aux = aux - 1;
    if(tareaPendiente[aux] != NULL)
    {
        printf("Tarea %d\n", tareaPendiente[aux]->TareaID);
        printf("%s\n", tareaPendiente[aux]->Descripcion);
        printf("Duracion: %d\n\n", tareaPendiente[aux]->Duracion);
        aux2--;
    }
    if(tareaRealizada[aux] != NULL)
    {
        printf("Tarea %d\n", tareaRealizada[aux]->TareaID);
        printf("%s\n", tareaRealizada[aux]->Descripcion);
        printf("Duracion: %d\n\n", tareaRealizada[aux]->Duracion);
        aux2--;
    }
    if(aux2)
    {
        puts("**Tarea no encontrada**");
    }
}

void BuscarTareaPorPalabra(Tarea **tareaPendiente, Tarea **tareaRealizada, int num)
{
    int i=0, aux=1;
    char palabra[20];

    fflush(stdin);
    printf("Que tarea quiere ver?\nIngrese una palabra de la descripcion: ");
    gets(palabra);
    
    for(i=0; i<num; i++)
    {
        if(tareaPendiente[i] != NULL && strstr(tareaPendiente[i]->Descripcion, palabra))
        {
            printf("**Tarea encontrada**\nTarea %d\n", tareaPendiente[i]->TareaID);
            printf("%s\n", tareaPendiente[i]->Descripcion);
            printf("Duracion: %d", tareaPendiente[i]->Duracion);
            i=5;
            aux--;
        }
        if(tareaRealizada[i] != NULL && strstr(tareaRealizada[i]->Descripcion, palabra))
        {
            printf("**Tarea encontrada**\nTarea %d\n", tareaRealizada[i]->TareaID);
            printf("%s\n", tareaRealizada[i]->Descripcion);
            printf("Duracion: %d", tareaRealizada[i]->Duracion);
            i=5;
            aux--;
        }
    }

    if(aux)
    {
        puts("**Tarea no encontrada**");
    }
}
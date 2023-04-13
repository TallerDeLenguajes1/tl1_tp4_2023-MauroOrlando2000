#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea {
    int TareaID;                    //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;                   // entre 10 – 100
} typedef Tarea;

void mostrarTareas(Tarea **punto, int num);

int main()
{
    Tarea **punto;
    int num, i;
    char *Buff;

    printf("Cuantas tareas debe realizar?: ");
    scanf("%d", &num);
    fflush(stdin);
    punto = (Tarea **)malloc(num*sizeof(Tarea *));

    for(i=0; i<num; i++)
    {
        punto[i] = NULL;
    }

    for(i=0; i<num; i++)
    {
        Buff = (char *)malloc(50*sizeof(char));
        printf("\nTarea %d\n", i+1);
        punto[i]->TareaID = i+1;
        printf("\nDescripcion:\n");
        gets(Buff);
        punto[i]->Descripcion = (char *)malloc((strlen(Buff)+1)*sizeof(char));
        strcpy(punto[i]->Descripcion, Buff);
        printf("Duracion: ");
        scanf("%d", punto[i]->Duracion);
        fflush(stdin);
        printf("\n");
        free(Buff);
    }
    mostrarTareas(punto, num);
    free(punto);
    return 0;
}

void mostrarTareas(Tarea **punto, int num)
{
    int i;

    for(i=0; i<num; i++)
    {
        printf("\nTarea %d\n", punto[i]->TareaID);
        printf("%s\n", punto[i]->Descripcion);
        printf("Duracion: %d horas", punto[i]->Duracion);
    }
}
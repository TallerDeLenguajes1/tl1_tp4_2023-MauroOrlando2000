#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo {
    Tarea punto;
    struct Nodo *next;
}Nodo;

void cargarTareas(Nodo **pendiente, int *num);
void mostrarTareas(Nodo **pendiente, Nodo **realizada);
Nodo * listaVacia();
Nodo * crearNodo(Tarea valor);
void * insertarNodo(Nodo **Start, Tarea valor);
void realizarTarea(Nodo **pendiente, Nodo **realizada);
Tarea eliminarNodo(Nodo ** Start, int dato);
Nodo * BuscarTareaPorId(Nodo **pendiente, Nodo **realizada);
Nodo * BuscarTareaPorPalabra(Nodo **pendiente, Nodo **realizada);

int main()
{
    Nodo **tareasPendientes, **tareasRealizadas, *ID;
    int aux=1, aux2, *num = (int *)malloc(sizeof(int));
    tareasPendientes = (Nodo **)malloc(sizeof(Nodo *));
    tareasRealizadas = (Nodo **)malloc(sizeof(Nodo *));
    *num = 1;

    while(aux == 1 || aux == 2 || aux == 3 || aux == 4)
    {
        printf("\n\nQue desea hacer?:\n1: Cargar una nueva tarea\n2: Marcar tarea como realizada\n3: Mostrar tareas\n4: Buscar tarea\n5: Cerrar sesion\nIngrese aqui: ");
        scanf("%d", &aux);
        switch(aux)
        {
            case 1: cargarTareas(tareasPendientes, num);
                *num = *num + 1;
                break;
            case 2: realizarTarea(tareasPendientes, tareasRealizadas);
                break;
            case 3: mostrarTareas(tareasPendientes, tareasRealizadas);
                break;
            case 4: printf("\nComo desea buscar? (1: por ID, 2: por palabra): ");
                scanf("%d", &aux2);
                if(aux2==1)
                {
                    ID = BuscarTareaPorId(tareasPendientes, tareasRealizadas);
                }
                else
                {
                    ID = BuscarTareaPorPalabra(tareasPendientes, tareasRealizadas);
                }
                if(ID)
                {
                    printf("\nTAREA %d", ID->punto.TareaID);
                    printf("\nDescripcion: %s", ID->punto.Descripcion);
                    printf("\nDuracion: %d", ID->punto.Duracion);
                }
                else
                {
                    printf("\nTAREA NO ENCONTRADA");
                }
                break;
            default: break;
        }
    }
    return 0;
}

void cargarTareas(Nodo **pendiente, int *num)
{
    Tarea *problema;
    char *buff;
    if(*num == 1)
    {
        *pendiente = listaVacia();
    }
    fflush(stdin);
    problema = (Tarea *)malloc(sizeof(Tarea));
    buff = (char *)malloc(100*sizeof(char));
    printf("\nTarea %d", *num);
    problema->TareaID = *num;
    printf("\nDescripcion: ");
    gets(buff);
    problema->Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(problema->Descripcion, buff);
    printf("Duracion: ");
    scanf("%d", &problema->Duracion);
    insertarNodo(pendiente, *problema);
    fflush(stdin);
    free(buff);
    free(problema);
    printf("\n");
}

void realizarTarea(Nodo **pendiente, Nodo **realizada)
{
    Nodo *tmp = *pendiente;
    char aux;
    *realizada = listaVacia();

    while(tmp)
    {
        fflush(stdin);
        printf("\n\nTAREA %d",tmp->punto.TareaID);
        printf("\nDescripcion: %s", tmp->punto.Descripcion);
        printf("\nDuracion: %d", tmp->punto.Duracion);
        printf("\nEsta tarea esta realizada? ('S' = si, 'N' = no): ");
        scanf("%c", &aux);
        if(aux == 'S' || aux == 's')
        {
            insertarNodo(realizada, eliminarNodo(pendiente, tmp->punto.TareaID));
        }
        tmp = tmp->next;
    }
}

void mostrarTareas(Nodo **pendiente, Nodo **realizada)
{
    Nodo *tmp = *realizada;
    for(int i=0; i<2; i++)
    {
        if(i)
        {
            printf("\n\nTAREAS PENDIENTES");
        }
        else
        {
            printf("\n\nTAREAS REALIZADAS");
        }
        while(tmp)
        {
            printf("\n\nTAREA %d",tmp->punto.TareaID);
            printf("\nDescripcion: %s", tmp->punto.Descripcion);
            printf("\nDuracion: %d", tmp->punto.Duracion);
            tmp = tmp->next;
        }
        tmp = *pendiente;
    }
}

Nodo * BuscarTareaPorId(Nodo **pendiente, Nodo **realizada)
{
    Nodo *Aux = *pendiente;
    int ID;
    printf("\nIngrese el ID de la tarea que quiere buscar: ");
    scanf("%d", &ID);
    for(int i=0; i<2; i++)
    {
        if(i)
        {
            Aux = *realizada;
        }
        while(Aux && Aux->punto.TareaID != ID)
        {
            Aux = Aux->next;
        }
        if(Aux && Aux->punto.TareaID == ID)
        {
            i+=2;
        }
    }
    return Aux;
}


Nodo * BuscarTareaPorPalabra(Nodo **pendiente, Nodo **realizada)
{
    Nodo *tmp = *pendiente;
    char palabra[20];

    fflush(stdin);
    printf("Que tarea quiere ver?\nIngrese una palabra de la descripcion: ");
    gets(palabra);
    
    for(int i=0; i<2; i++)
    {
        if(i)
        {
            tmp = *realizada;
        }
        while(tmp && !strstr(tmp->punto.Descripcion, palabra));
        {
            tmp = tmp->next;
        }
    }
    return tmp;
}

Nodo * listaVacia()
{
    return NULL;
}

Nodo * crearNodo(Tarea valor)
{
    Nodo *NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->punto = valor;
    NNodo->next = NULL;
    return NNodo;
}

void * insertarNodo(Nodo **Start, Tarea valor)
{
    Nodo *NNodo = crearNodo(valor);
    NNodo->next = *Start;
    *Start = NNodo;
}

Tarea eliminarNodo(Nodo ** Start, int dato)
{
    Nodo *Aux = *Start;
    Nodo *AuxAnterior = *Start;
    while (Aux && (Aux->punto.TareaID != dato))
    {
        AuxAnterior = Aux;
        Aux = Aux->next;
    }
    if(Aux)
    {
        AuxAnterior->next = Aux->next;
    }
    return Aux->punto;
}

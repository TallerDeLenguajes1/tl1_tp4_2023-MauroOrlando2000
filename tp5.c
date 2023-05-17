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
void mostrarTareas(Nodo **pendiente, Nodo **realizada, Nodo **enProceso);
Nodo * listaVacia();
Nodo * crearNodo(Tarea valor);
void * insertarNodo(Nodo **Start, Tarea valor);
void moverTarea(Nodo **pendiente, Nodo **realizada, Nodo **enProceso);
Tarea moverNodo(Nodo **Start, int dato);
Nodo * BuscarTareaPorId(Nodo **pendiente, Nodo **realizada, Nodo **enProceso);
Nodo * BuscarTareaPorPalabra(Nodo **pendiente, Nodo **realizada, Nodo **enProceso);
void eliminarNodo(Nodo **pendiente, Nodo **enProceso, Nodo **realizada, int dato);
void mostrarDatos(Nodo **lista);

int main()
{
    Nodo **tareasPendientes, **tareasRealizadas, **tareasEnProceso, *ID, *tmp;
    int aux=1, aux2, *num = (int *)malloc(sizeof(int)), i;
    tareasPendientes = (Nodo **)malloc(sizeof(Nodo *));
    tareasRealizadas = (Nodo **)malloc(sizeof(Nodo *));
    tareasEnProceso = (Nodo **)malloc(sizeof(Nodo *));
    *tareasPendientes = *tareasEnProceso = *tareasRealizadas = listaVacia();
    *num = 1;

    while(aux == 1 || aux == 2 || aux == 3 || aux == 4 || aux == 5 || aux == 6)
    {
        printf("\n\nQue desea hacer?:\n1: Cargar una nueva tarea\n2: Mover tarea de lista\n3: Mostrar tareas\n4: Buscar tarea\n5: Eliminar tarea\n6: Mostrar Datos\n7: Cerrar sesion\nIngrese aqui: ");
        scanf("%d", &aux);
        switch(aux)
        {
            case 1: cargarTareas(tareasPendientes, num);
                *num = *num + 1;
                break;
            case 2: moverTarea(tareasPendientes, tareasRealizadas, tareasEnProceso);
                break;
            case 3: mostrarTareas(tareasPendientes, tareasRealizadas, tareasEnProceso);
                break;
            case 4: printf("\nComo desea buscar? (1: por ID, 2: por palabra): ");
                scanf("%d", &aux2);
                if(aux2==1)
                {
                    ID = BuscarTareaPorId(tareasPendientes, tareasRealizadas, tareasEnProceso);
                }
                else
                {
                    ID = BuscarTareaPorPalabra(tareasPendientes, tareasRealizadas, tareasEnProceso);
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
            case 5: printf("Que tarea desea eliminar? Ingrese el ID: ");
                scanf("%d", &aux2);
                for(i=0; i<3; i++)
                {
                    if(i==0)
                    {
                        tmp = *tareasPendientes;
                    }
                    else if(i==1)
                    {
                        tmp = *tareasEnProceso;
                    }
                    else
                    {
                        tmp = *tareasRealizadas;
                    }
                    while(tmp && tmp->punto.TareaID != aux)
                    {
                        tmp = tmp->next;
                    }
                    if(tmp && tmp->punto.TareaID == aux)
                    {
                        eliminarNodo(tareasPendientes, tareasEnProceso, tareasRealizadas, tmp->punto.TareaID);
                    }
                }
                break;
            case 6: printf("Que lista desea ver?: (0: pendientes, 1: en proceso, 2: realizadas): ");
                scanf("%d", &aux2);
                if(aux2 == 0)
                {
                    mostrarDatos(tareasPendientes);
                }
                else if(aux2 == 1)
                {
                    mostrarDatos(tareasEnProceso);
                }
                else
                {
                    mostrarDatos(tareasRealizadas);
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

void moverTarea(Nodo **pendiente, Nodo **realizada, Nodo **enProceso)
{
    Nodo *tmp = *pendiente;
    int aux, i;

    while(aux==10)
    {
        mostrarTareas(pendiente, realizada, enProceso);
        printf("\nSeleccione una tarea. Ingrese el ID: ");
        scanf("%d", &aux);

        for(i=0; i<3; i++)
        {
            if(i==0)
            {
                tmp = *pendiente;
            }
            else if(i==1)
            {
                tmp = *enProceso;
            }
            else
            {
                tmp = *realizada;
            }
            while(tmp && tmp->punto.TareaID != aux)
            {
                tmp = tmp->next;
            }
            if(tmp && tmp->punto.TareaID == aux)
            {
                if(i==0)
                {
                    i=4;
                }
                else if(i==1)
                {
                    i=5;
                }
                else
                {
                    i=6;
                }
            }
        }
        if(tmp)
        {
            printf("\n\nTAREA %d",tmp->punto.TareaID);
            printf("\nDescripcion: %s", tmp->punto.Descripcion);
            printf("\nDuracion: %d", tmp->punto.Duracion);
            printf("Que desea hacer? (0: Mover tarea, 1: eliminar tarea, 2: no hacer nada): ");
            scanf("%d", &aux);
            if(aux==0)
            {
                if(i==5)
                {
                    printf("\nEsta tarea esta en proceso o realizada? (0: en proceso, 1: realizada): ");
                    scanf("%d", &aux);
                    if(aux)
                    {
                        insertarNodo(realizada, moverNodo(pendiente, tmp->punto.TareaID));
                        printf("\nTarea colocada en realizadas correctamente");
                    }
                    else
                    {
                        insertarNodo(enProceso, moverNodo(pendiente, tmp->punto.TareaID));
                        printf("\nTarea colocada en proceso correctamente");
                    }
                }
                else if(i==6)
                {
                    printf("\nEsta tarea esta pendiente o realizada? (0: pendiente, 1: realizada): ");
                    scanf("%d", &aux);
                    if(aux)
                    {
                        insertarNodo(realizada, moverNodo(enProceso, tmp->punto.TareaID));
                        printf("\nTarea colocada en realizadas correctamente");
                    }
                    else
                    {
                        insertarNodo(pendiente, moverNodo(enProceso, tmp->punto.TareaID));
                        printf("\nTarea colocada en proceso correctamente");
                    }
                }
                else
                {
                    printf("\nEsta tarea esta pendiente o en proceso? (0: pendiente, 1: en proceso): ");
                    scanf("%d", &aux);
                    if(aux)
                    {
                        insertarNodo(enProceso, moverNodo(realizada, tmp->punto.TareaID));
                        printf("\nTarea colocada en realizadas correctamente");
                    }
                    else
                    {
                        insertarNodo(pendiente, moverNodo(realizada, tmp->punto.TareaID));
                        printf("\nTarea colocada en proceso correctamente");
                    }
                }
            }   
            else if(aux==1)
            {
                eliminarNodo(pendiente, enProceso, realizada, tmp->punto.TareaID);
            }
        }
        else
        {
            printf("\nTAREA NO ENCONTRADA");
        }
        printf("\n\nDesea modificar alguna otra tarea?: (0: no, 1: si): ");
        scanf("%d", &aux);
        if(aux)
        {
            aux = 10;
        }
        else
        {
            mostrarDatos(pendiente);
            mostrarDatos(enProceso);
            mostrarDatos(realizada);
        }
    }
}

void mostrarTareas(Nodo **pendiente, Nodo **realizada, Nodo **enProceso)
{
    Nodo *tmp;
    for(int i=0; i<3; i++)
    {
        if(i==0)
        {
            printf("\n\nTAREAS REALIZADAS");
            tmp = *realizada;
        }
        else if(i==1)
        {
            printf("\n\nTAREAS EN PROCESO");
            tmp = *enProceso;
        }
        else
        {
            printf("\n\nTAREAS PENDIENTES");
            tmp = *pendiente;
        }
        while(tmp)
        {
            printf("\n\nTAREA %d",tmp->punto.TareaID);
            printf("\nDescripcion: %s", tmp->punto.Descripcion);
            printf("\nDuracion: %d", tmp->punto.Duracion);
            tmp = tmp->next;
        }
    }
}

Nodo * BuscarTareaPorId(Nodo **pendiente, Nodo **realizada, Nodo **enProceso)
{
    Nodo *Aux;
    int ID;
    printf("\nIngrese el ID de la tarea que quiere buscar: ");
    scanf("%d", &ID);
    for(int i=0; i<3; i++)
    {
        if(i==0)
        {
            Aux = *pendiente;
        }
        else if(i==1)
        {
            Aux = *realizada;
        }
        else
        {
            Aux = *enProceso;
        }
        while(Aux && Aux->punto.TareaID != ID)
        {
            Aux = Aux->next;
        }
        if(Aux && Aux->punto.TareaID == ID)
        {
            i=3;
        }
    }
    return Aux;
}


Nodo * BuscarTareaPorPalabra(Nodo **pendiente, Nodo **realizada, Nodo **enProceso)
{
    Nodo *tmp;
    char palabra[20];

    fflush(stdin);
    printf("Que tarea quiere ver?\nIngrese una palabra de la descripcion: ");
    gets(palabra);
    
    for(int i=0; i<3; i++)
    {
        if(i==0)
        {
            tmp = *pendiente;
        }
        else if(i==1)
        {
            tmp = *realizada;
        }
        else
        {
            tmp = *enProceso;
        }
        while(tmp && !strstr(tmp->punto.Descripcion, palabra));
        {
            tmp = tmp->next;
        }
        if(tmp && strstr(tmp->punto.Descripcion, palabra))
        {
            i=3;
        }
    }
    return tmp;
}

void mostrarDatos(Nodo **lista)
{
    Nodo *tmp = *lista;
    int duracion=0;
    while(tmp)
    {
        printf("\n");
        printf("TAREA %D\n", tmp->punto.TareaID);
        printf("Descripcion: %s\n", tmp->punto.Descripcion);
        duracion += tmp->punto.Duracion;
        tmp = tmp->next;
    }
    printf("\nDuracion total: %d", duracion);
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

Tarea moverNodo(Nodo **Start, int dato)
{
    Nodo *Aux = *Start;
    Nodo *AuxAnterior = NULL;
    while (Aux && (Aux->punto.TareaID != dato))
    {
        AuxAnterior = Aux;
        Aux = Aux->next;
    }
    if(Aux)
    {
        if(!AuxAnterior)
        {
            *Start = Aux->next;
        }
        else
        {
            AuxAnterior->next = Aux->next;
        }
    }
    return Aux->punto;
}

void eliminarNodo(Nodo **pendiente, Nodo **enProceso, Nodo **realizada, int dato)
{
    Nodo *Aux = *pendiente;
    Nodo *AuxAnterior = NULL;
    int i;
    for(i=0; i<3; i++)
    {
        if(i==1)
        {
            Aux = *enProceso;
            AuxAnterior = NULL;
        }
        if(i==2)
        {
            Aux = *realizada;
            AuxAnterior = NULL;
        }
        while (Aux && (Aux->punto.TareaID != dato))
        {
            AuxAnterior = Aux;
            Aux = Aux->next;
        }
        if(Aux)
        {
            if(i==0)
            {
                i=2;
            }
            else if(i==1)
            {
                i=3;
            }
            else
            {
                i=4;
            }
        }
    }
    if(Aux)
    {
        if(!AuxAnterior)
        {
            if(i==3)
            {
                *pendiente = Aux->next;
            }
            else if(i==4)
            {
                *enProceso = Aux->next;
            }
            else
            {
                *realizada = Aux->next;
            }
        }
        else
        {
            AuxAnterior->next = Aux->next;
        }
        free(Aux);
        printf("\nTarea eliminada");
    }
    else
    {
        printf("\nTarea no encontrada");
    }
}
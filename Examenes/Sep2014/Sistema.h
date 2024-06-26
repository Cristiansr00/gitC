#ifndef __SISTEMA__
#define __SISTEMA__

// Definición del tipo LSistema
typedef struct Nodo* LSistema; 
typedef struct Hebra* LHebra;

struct Nodo{
    unsigned pid;
    LSistema sig;
    LHebra h;
};

struct Hebra{
    unsigned prio;
    char * idhebra;
    LHebra sig;
};

//Crea una lista vacia
void Crear(LSistema *l);
//Inserta un proceso por orden de llegada.
void InsertarProceso ( LSistema *ls, int numproc);
//Inserta una hebra en el proceso numproc teniendo en cuenta el orden de prioridad (mayor a menor)
void InsertarHebra (LSistema *ls, int numproc, char *idhebra, int priohebra);
//Muestra el contenido del sistema
void Mostrar (LSistema ls);
//Elimina del sistema el proceso con número numproc liberando la memoria de éste y de sus hebras.
void EliminarProc (LSistema *ls, int numproc);
//Destruye toda la estructura liberando su memoria
void Destruir (LSistema *ls); 



#endif

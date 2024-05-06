/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ6***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    /*Este programa intencionalmente genera un memory leak*/

    //Se define un apuntador y se le asigna una direccion de memoria
    void *ptr = malloc(10);

    //SOLUCION
    /*-------Para solucionarlo, unicamente se debe liberar la memoria antes
      -------de la reasignacion*/ free(ptr);

    /*Se reasigna el apuntador, perdiendo al referencia al primer bloque de
    memoria que se le habia asignado, generando asi un memory leak*/
    ptr = malloc(10); 

    //Se libera uno de los bloques de memoria, el de ultima asignacion
    free(ptr);

    /*Con ayuda del comando valgrind --leak-check=full --track-origins=yes ./run
    se detecta la memoria no liberada*/

    return 0;
}
/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Tarea 9/EJ3 Neville********/
/***********Metodos Numericos**********/
/**************22/10/2023**************/
/**************************************/
/**************************************/

#include "tarea9.c"

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Se obtienen los puntos y sus evaluaciones
    int sz;
    double **pairs = r_pairs(argv[1], &sz);

    //Se obtiene la solucion
    solInterpol *sol = eval_neville(pairs[0], pairs[1], 1.0, sz);
    printf("La evaluacion de la interpolacion de neville de grado %d, en el punto 1.0 es: %lf\n", sz-1, sol->sol);

    //Liberando memoria
    free(pairs[0]); //Memoria contigua
    free(pairs);
    free_interpol(sol);

    return 0;
}
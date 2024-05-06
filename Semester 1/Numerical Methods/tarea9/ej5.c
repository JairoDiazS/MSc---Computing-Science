/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*********Tarea 9/EJ5 Comparacion******/
/***********Metodos Numericos**********/
/**************22/10/2023**************/
/**************************************/
/**************************************/

#include "tarea9.c"

int main(int argc, char **argv){
    if (argc < 3) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Se obtienen los puntos y sus evaluaciones
    int sz;
    double **pairs = r_pairs(argv[1], &sz);

    int p;
    //Se obtienen los puntos a probar
    double *test = r_points(argv[2], &p);

    //Soluciones
    double lagr, sol, e_lagr, e_nevi, e_dd;
    solInterpol *nevi, *DD;

    //Se imprime la tabla
    printf("z\t\tf(z)=exp(z)\tLagrange\te_Lagrang\t\tNeville\t\te_Neville\t\tDD\t\te_DD\t\t\n");
    for(int i=0; i<p; i++){
        sol = exp(test[i]);
        lagr = eval_lagrange(pairs[0], pairs[1], test[i], sz-1);
        nevi = eval_neville(pairs[0], pairs[1], test[i], sz);
        DD = eval_newtonDD(pairs[0], pairs[1], test[i], sz);
        e_lagr = fabs(lagr - sol);
        e_nevi = fabs(nevi->sol - sol);
        e_dd = fabs(DD->sol - sol);
        printf("%g\t\t%g\t\t%g\t\t%g\t\t%g\t\t%g\t\t%g\t\t%g\n",\
         test[i], sol, lagr, e_lagr, nevi->sol, e_nevi, DD->sol, e_dd);
        free_interpol(nevi);
        free_interpol(DD);
    }
    
    free(pairs[0]); //Memoria contigua
    free(pairs);

    return 0;
}
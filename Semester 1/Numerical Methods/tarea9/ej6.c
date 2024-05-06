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
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Se obtienen los puntos y sus evaluaciones
    int sz;
    double **pairs = r_pairs(argv[1], &sz);

    //Se obtiene la solucion para los puntos que se solicita
    double x1 = 0.0075;
    double x2 = 0.0125;
    double x3 = 0.0175;
    solInterpol *sol1 = eval_newtonDD(pairs[0], pairs[1], x1, sz);
    solInterpol *sol2 = eval_newtonDD(pairs[0], pairs[1], x2, sz);
    solInterpol *sol3 = eval_newtonDD(pairs[0], pairs[1], x3, sz);

    //Creamos una matriz para almacenarlos todos
    double **mat = genMatriz(sz+3, 2);
    double **pred = genMatriz(3,2);

    //Se rellena
    int i;
    for(i=0; i<sz; i++){
        mat[i][0] = pairs[0][i];
        mat[i][1] = pairs[1][i];
    }
    print_mat(mat, "in.txt", sz, 2);
    mat[i][0] = pred[0][0] = x1;
    mat[i][1] = pred[0][1] = sol1->sol;
    i++;
    mat[i][0] = pred[1][0] = x2;
    mat[i][1] = pred[1][1] = sol2->sol;
    i++;
    mat[i][0] = pred[2][0] = x3;
    mat[i][1] = pred[2][1] = sol3->sol;





    //Se ordenan los datos
    sortPairs(mat, sz+3);
    //Se imrpime la matriz en un archivo
    print_mat(mat, "graf.txt", sz+3, 2);
    print_mat(pred, "pred.txt", 3, 2);



    //Liberando memoria
    free(pairs[0]); //Memoria contigua
    free(pairs);
    free_interpol(sol1);
    free_interpol(sol2);
    free_interpol(sol3);

    free(mat[0]); //Memoria contigua
    free(mat);
    free(pred[0]); //Memoria contigua
    free(pred);

    return 0;
}
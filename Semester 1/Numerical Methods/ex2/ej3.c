/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Examen 2 Ejercicio 3********/
/***********Metodos Numericos**********/
/**************04/12/2023**************/
/**************************************/
/**************************************/

#include "tarea9.c"
#include "tarea11.c"

double rbf(double x, int n){
    return exp(-n*x*3);
}

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }
    
    //Se obtienen los puntos y sus evaluaciones
    int sz;
    double **pairs = r_pairs(argv[1], &sz);
    
    //Se obtiene la solucion
    double p = 4.0;
    double sol = eval_lagrange(pairs[0], pairs[1], p, sz-1);
    printf("La evaluacion del polinomio de lagrange de grado %d, en el punto %lf es: %lf\n", sz-1, p, sol);

    double *inv = (double *)calloc(sz, sizeof(double));
    for(int i=0; i< sz; i++){
        inv[i] = 1.0 / pairs[1][i];
    }


    double l1 = 0;
    double l2 = 1e-5;
    double l3 = 1e-7;
    int n = 2;

    double *cp1 = least_sqr(pairs[0], inv, l1, sz, -1, n, rbf);
    double *cp2 = least_sqr(pairs[0], inv, l2, sz, -1, n, rbf);
    double *cp3 = least_sqr(pairs[0], inv, l3, sz, -1, n, rbf);

    double pol1 = 1.0 / eval_serie(cp1, p, n, rbf);
    double pol2 = 1.0 / eval_serie(cp2, p, n, rbf);
    double pol3 = 1.0 / eval_serie(cp3, p, n, rbf);

    printf("Lambda = %lf, eval = %lf\n", l1, pol1);
    for(int i=0; i<n; i++){
        printf("Coeficiente %d: %lf\n", i, cp1[i]);
    }
    printf("Lambda = %lf, eval = %lf\n", l2, pol1);
    for(int i=0; i<n; i++){
        printf("Coeficiente %d: %lf\n", i, cp2[i]);
    }
    printf("Lambda = %lf, eval = %lf\n", l3, pol1);
    for(int i=0; i<n; i++){
        printf("Coeficiente %d: %lf\n", i, cp3[i]);
    }

    //Creamos la matriz para guardar el intervalo
    int pts = 120;
    double **ppts1 = genMatriz(pts, 2);
    double **ppts2 = genMatriz(pts, 2);
    double **ppts3 = genMatriz(pts, 2);
    double **ppts4 = genMatriz(pts, 2);

    for(int i=0; i<pts; i++){
        //polinomial
        ppts1[i][0] = i / 10.0;
        ppts1[i][1] = 1.0 / eval_serie(cp1, ppts1[i][0], n, rbf);
        ppts2[i][0] = i / 10.0;
        ppts2[i][1] = 1.0 / eval_serie(cp2, ppts2[i][0], n, rbf);
        ppts3[i][0] = i / 10.0;
        ppts3[i][1] = 1.0 / eval_serie(cp3, ppts3[i][0], n, rbf);
        ppts4[i][0] = i / 10.0;
        ppts4[i][1] = eval_lagrange(pairs[0], pairs[1], ppts4[i][0], sz-1);
    }

    //Se escriben los valores en archivos de texto
    print_mat(ppts1, "ppts1.txt", pts, 2);
    print_mat(ppts2, "ppts2.txt", pts, 2);
    print_mat(ppts3, "ppts3.txt", pts, 2);
    print_mat(ppts4, "ppts4.txt", pts, 2);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "plot 'ppts1.txt' using 1:2 w l title 'lambda = 0'\n");
    fprintf(gnuplotPipe, "replot 'ppts2.txt' using 1:2 w l title 'lambda = 1e-5'\n");
    fprintf(gnuplotPipe, "replot 'ppts3.txt' using 1:2 w l title 'lambda = 1e-7'\n");
    fprintf(gnuplotPipe, "replot 'ppts4.txt' using 1:2 w l title 'Lagrange'\n");
    fclose(gnuplotPipe);

    //Liberando memoria
    free(pairs[0]); //Memoria contigua
    free(pairs);
    free(cp1);
    free(cp2);
    free(cp3);

    return 0;
}
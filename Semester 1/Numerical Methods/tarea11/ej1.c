/********************************************/
/********************************************/
/*************Jairo Saul Diaz Soto***********/
/*********Tarea 11 - Minimos Cuadrados*******/
/**************Metodos Numericos*************/
/*****************05/11/2023*****************/
/********************************************/
/********************************************/

#include "tarea11.c"

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }
    //Se leen los puntos de entrada
    int sz1;
    double *x1 = r_points(argv[1], &sz1);

    //Se solicita memoria para guardar las evaluaciones
    double *y1 = (double *)calloc(sz1, sizeof(double));

    //Se definen las ctes
    double m0 = 1.919e-2;
    double t0 = 273.0;
    double su = 139.0;
    int n = atoi(argv[2]);

    //Se evaalua la funcion
    for(int i=0; i<sz1; i++){
        y1[i] = sutherland(x1[i], m0, su, t0);
    }

    //Aplicamos para t = 1.2
    double t = 1.2;
    double l1 = 0;
    double l2 = 1e-5;
    double l3 = 1e-7;

    //Obtenemos su evaluacion real
    double treal = sutherland(t, m0, su, t0);
    //Polinomial
    double *cp1 = least_sqr(x1, y1, l1, sz1, -1, n, polinomial);
    double *cp2 = least_sqr(x1, y1, l2, sz1, -1, n, polinomial);
    double *cp3 = least_sqr(x1, y1, l3, sz1, -1, n, polinomial);
    //Trigonometrica
    double *ct1 = least_sqr(x1, y1, l1, sz1, -1, n, trigonometrica);
    double *ct2 = least_sqr(x1, y1, l2, sz1, -1, n, trigonometrica);
    double *ct3 = least_sqr(x1, y1, l3, sz1, -1, n, trigonometrica);
    //RBF
    double *ce1 = least_sqr(x1, y1, l1, sz1, 1, n, exponencial);
    double *ce2 = least_sqr(x1, y1, l2, sz1, 1, n, exponencial);
    double *ce3 = least_sqr(x1, y1, l3, sz1, 1, n, exponencial);

    //Creamos las evaluaciones
    double pol1 = eval_serie(cp1, t, n, polinomial);
    double pol2 = eval_serie(cp2, t, n, polinomial);
    double pol3 = eval_serie(cp3, t, n, polinomial);
    double tri1 = eval_serie(ct1, t, n, trigonometrica);
    double tri2 = eval_serie(ct2, t, n, trigonometrica);
    double tri3 = eval_serie(ct3, t, n, trigonometrica);
    double exp1 = eval_exp(ce1, x1, t, n);
    double exp2 = eval_exp(ce2, x1, t, n);
    double exp3 = eval_exp(ce3, x1, t, n);

    //Se imprimen los valores
    printf("Evaluacion del punto t=%lf es suth(t)=%lf\n",t, treal);
    printf("funcion\t\tlambda\t\tprediccion\terror abs\n");
    printf("polinomial\t%.7lf\t%lf\t%lf\n", l1, pol1, fabs(pol1-treal));
    printf("polinomial\t%.7lf\t%lf\t%lf\n", l2, pol2, fabs(pol2-treal));
    printf("polinomial\t%.7lf\t%lf\t%lf\n", l3, pol3, fabs(pol3-treal));
    printf("trigonometrica\t%.7lf\t%lf\t%lf\n", l1, tri1, fabs(tri1-treal));
    printf("trigonometrica\t%.7lf\t%lf\t%lf\n", l2, tri2, fabs(tri2-treal));
    printf("trigonometrica\t%.7lf\t%lf\t%lf\n", l3, tri3, fabs(tri3-treal));
    printf("exponencial\t%.7lf\t%lf\t%lf\n", l1, exp1, fabs(exp1-treal));
    printf("exponencial\t%.7lf\t%lf\t%lf\n", l2, exp2, fabs(exp2-treal));
    printf("exponencial\t%.7lf\t%lf\t%lf\n", l3, exp3, fabs(exp3-treal));

    //Creamos la matriz para guardar el intervalo
    double **ppts1 = genMatriz(25, 2);
    double **ppts2 = genMatriz(25, 2);
    double **ppts3 = genMatriz(25, 2);
    double **tpts1 = genMatriz(25, 2);
    double **tpts2 = genMatriz(25, 2);
    double **tpts3 = genMatriz(25, 2);
    double **epts1 = genMatriz(25, 2);
    double **epts2 = genMatriz(25, 2);
    double **epts3 = genMatriz(25, 2);

    //Se rellenan la matriz
    double temp = 0.273;
    for(int i=0; i<25; i++){
        //polinomial
        ppts1[i][0] = temp;
        ppts1[i][1] = eval_serie(cp1, ppts1[i][0], n, polinomial);
        ppts2[i][0] = temp;
        ppts2[i][1] = eval_serie(cp2, ppts2[i][0], n, polinomial);
        ppts3[i][0] = temp;
        ppts3[i][1] = eval_serie(cp3, ppts3[i][0], n, polinomial);
        //trigonometrica
        tpts1[i][0] = temp;
        tpts1[i][1] = eval_serie(ct1, tpts1[i][0], n, trigonometrica);
        tpts2[i][0] = temp;
        tpts2[i][1] = eval_serie(ct2, tpts2[i][0], n, trigonometrica);
        tpts3[i][0] = temp;
        tpts3[i][1] = eval_serie(ct3, tpts3[i][0], n, trigonometrica);
        //RBF
        epts1[i][0] = temp;
        epts1[i][1] = eval_exp(ce1, x1, epts1[i][0], n);
        epts2[i][0] = temp;
        epts2[i][1] = eval_exp(ce2, x1, epts2[i][0], n);
        epts3[i][0] = temp;
        epts3[i][1] = eval_exp(ce3, x1, epts3[i][0], n);
        temp += 0.05;
    }

    //Se escriben los valores en archivos de texto
    print_mat(ppts1, "ppts1.txt", 25, 2);
    print_mat(ppts2, "ppts2.txt", 25, 2);
    print_mat(ppts3, "ppts3.txt", 25, 2);
    print_mat(tpts1, "tpts1.txt", 25, 2);
    print_mat(tpts2, "tpts2.txt", 25, 2);
    print_mat(tpts3, "tpts3.txt", 25, 2);
    print_mat(epts1, "epts1.txt", 25, 2);
    print_mat(epts2, "epts2.txt", 25, 2);
    print_mat(epts3, "epts3.txt", 25, 2);

    //Se libera la memoria
    free(ppts1[0]); //Memoria contigua
    free(ppts1);
    free(ppts2[0]); //Memoria contigua
    free(ppts2);
    free(ppts3[0]); //Memoria contigua
    free(ppts3);
    free(tpts1[0]); //Memoria contigua
    free(tpts1);
    free(tpts2[0]); //Memoria contigua
    free(tpts2);
    free(tpts3[0]); //Memoria contigua
    free(tpts3);
    free(epts1[0]); //Memoria contigua
    free(epts1);
    free(epts2[0]); //Memoria contigua
    free(epts2);
    free(epts3[0]); //Memoria contigua
    free(epts3);
    free(cp1);
    free(cp2);
    free(cp3);
    free(ct1);
    free(ct2);
    free(ct3);
    free(ce1);
    free(ce2);
    free(ce3);

    return 0;
}
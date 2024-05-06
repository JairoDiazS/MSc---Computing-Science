/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*****Tarea 12 Sistemas no lineales****/
/***********Metodos Numericos**********/
/**************12/11/2023**************/
/**************************************/
/**************************************/

#include "tarea12.c"

#define TOL 1e-8
#define nMax 1000

double *R1(double *x){
    double *sol = (double *)calloc(3, sizeof(double));
    sol[0] = ((1.0/3.0) * cos(x[1]*x[2])) + (1.0/6.0);
    sol[1] = ((1.0/9.0) * sqrt((x[0]*x[0]) + sin(x[2]) + 1.06)) - 0.1;
    sol[2] = ((-1.0/20.0) * exp(-x[0]*x[1])) - (((10*M_PI)-3.0)/60.0);
    return sol;
}

double *R2(double *x){
    double *sol = (double *)calloc(2, sizeof(double));
    sol[0] = 3-x[1];
    sol[1] = sqrt(9 - (x[0]*x[0]));
    return sol;
}

double f1(double *x){
    return ((3.0*x[0]) - cos(x[1]*x[2]) - (1.0/2.0));
}

double f2(double *x){
    return ( (x[0]*x[0]) - (81.0*(x[1]+0.1)*(x[1]+0.1)) + sin(x[2]) + 1.06 );
}

double f3(double *x){
    return ( exp(-x[0]*x[1]) + (20.0*x[2]) + (((10*M_PI)-3.0) / 3.0) );
}

double g1(double *x){
    return x[0] + x[1] - 3;
}

double g2(double *x){
    return (x[0]*x[0]) + (x[1]*x[1]) - 9;
}

int main(){
    //Se genera el vector inicial
    double x[] = {0.1, 0.1, -0.1};
    double (*f[])(double *) = {f1, f2, f3};
    double (*g[])(double *) = {g1, g2};
    double h = 0.001;

    double **sol = jacobian_matrix(f, x, 0.0001, 3);
    double **sol1 = hessian_matrix(f, x, 0.0001, 3);

    double x1[] = {0.1, 0.1, -0.1};
    double *res1 = fixedPoint_nonLinear(R1, x1, 3, TOL, nMax);
    double x2[] = {0.1, 0.1, -0.1};
    double *res2 = newton_sys(f, x2, h, 3, TOL, nMax);
    double x3[] = {0.1, 0.1, -0.1};
    double *res3 = broyden_sys(f, x3, h, 3, TOL, nMax);
    double x4[] = {0.1, 0.1, -0.1};
    double *res4 = cg_Freeves(f, x4, h, 3, TOL, nMax);
    double y1[] = {1.0, 5.0};
    double *resg1 = fixedPoint_nonLinear(R2, y1, 2, TOL, nMax);
    double y2[] = {1.0, 5.0};
    double *resg2 = newton_sys(g, y2, h, 2, TOL, nMax);
    double y3[] = {1.0, 5.0};
    double *resg3 = broyden_sys(g, y3, h, 2, TOL, nMax);
    double y4[] = {1.0, 5.0};
    double *resg4 = cg_Freeves(g, y4, h, 2, TOL, nMax);
    
    printf("Solucion sistema 1\n");
    printf("x1\t\tx2\t\tx3\t\tMetodo\n");

    for(int i=0; i<3; i++) printf("%lf\t",res1[i]);
    printf("Punto fijo\n");
    for(int i=0; i<3; i++) printf("%lf\t",res2[i]);
    printf("Newton\n");
    for(int i=0; i<3; i++) printf("%lf\t",res3[i]);
    printf("Broyden\n");
    for(int i=0; i<3; i++) printf("%lf\t",res4[i]);
    printf("Gradiente\n");

    printf("Solucion sistema 2\n");
    printf("x1\t\tx2\t\tMetodo\n");

    for(int i=0; i<2; i++) printf("%lf\t",resg1[i]);
    printf("Punto fijo\n");
    for(int i=0; i<2; i++) printf("%lf\t",resg2[i]);
    printf("Newton\n");
    for(int i=0; i<2; i++) printf("%lf\t",resg3[i]);
    printf("Broyden\n");
    for(int i=0; i<2; i++) printf("%lf\t",resg4[i]);
    printf("Gradiente\n");


    print_mat(sol, "sol.txt", 3, 3);
    print_mat(sol1, "sol1.txt", 3, 3);

    free(sol[0]); //Memoria contigua
    free(sol);
    free(sol1[0]); //Memoria contigua
    free(sol1);

    return 0;
}
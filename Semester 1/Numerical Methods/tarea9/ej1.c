/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Tarea 9/EJ1 Taylor*********/
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
    //Se crea una variable para guardar el tamanio
    int sz;

    //Variable para guardar las evaluaciones
    double *eval = r_points(argv[1], &sz);

    //Creamos un vector donde almacenamos los puntos de prueba
    int szp;
    double *z = r_points(argv[2], &szp);

    //Se calcula la evaluacion del polinomio de taylor
    double sol, x0=0, error;
    
    //Se imprime una cabecera
    printf("z\t\tP_n(z)\t\tn\terror\t\tf(z)=exp(z)\tx0=%g\n",x0);
    for(int i=0; i< szp; i++){
        //Aplicamos la evaluacion
        sol = eval_taylor(eval, z[i], x0, 1);
        error = fabs(sol - exp(z[i]));
        printf("%lf\t%lf\t%d\t%g\n",z[i], sol, 1, error);

        sol = eval_taylor(eval, z[i], x0, 3);
        error = fabs(sol - exp(z[i]));
        printf("%lf\t%lf\t%d\t%g\n",z[i], sol, 3, error);

        sol = eval_taylor(eval, z[i], x0, 5);
        error = fabs(sol - exp(z[i]));
        printf("%lf\t%lf\t%d\t%g\n",z[i], sol, 5, error);

        sol = eval_taylor(eval, z[i], x0, 10);
        error = fabs(sol - exp(z[i]));
        printf("%lf\t%lf\t%d\t%g\n",z[i], sol, 10, error);

        printf("\n");
    }

    free(eval);
    free(z);
    return 0;
}

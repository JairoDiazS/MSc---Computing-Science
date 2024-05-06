/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/****Tarea 14 - Metodos para EDP's*****/
/**********Metodos Numericos***********/
/**************01/12/2023**************/
/**************************************/
/**************************************/

#include "tarea14.c"

double u0(double x){
    return 4*(x - (x*x));
}

int main(int argc, char** argv){
    //Se obtiene la solucion
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    double theta = atof(argv[3]);
    double alpha = atof(argv[4]);

    double T = 0.4;
    double a = 0.0;
    double b = 1.0;
    
    double **sol = theta_method(u0, theta, T, a, b, alpha, n, m);
    print_mat(sol, "sol.txt", n-2, m-2);

    free(sol[0]); //Memoria contigua
    free(sol);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "splot 'sol.txt' matrix with lines\n");
    fclose(gnuplotPipe);

    return 0;
}
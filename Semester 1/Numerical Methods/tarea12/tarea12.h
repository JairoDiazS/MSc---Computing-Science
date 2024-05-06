/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 12 Cabecera*********/
/***********Metodos Numericos**********/
/**************12/11/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA_12
#define TAREA_12

typedef struct descomposicion{
    double **Left;
    double **Right;
} Factor;

double fw_diff(double fx, double fh, double h);
double bw_diff(double fh, double fx, double h);
double ct_diff(double fd, double fu, double h);
double three_midp_diff(double fd, double fu, double h);
double three_endp_diff(double fx, double fh1, double fh2, double h);
double five_midp_diff(double fd1, double fd2, double fu1, double fu2, double h);
double five_endp_diff(double fx, double fh1, double fh2, double fh3, double fh4, double h);
double midp_secdiff(double fd, double fx, double fu, double h);
double **jacobian_matrix(double (**f)(double *), double *x, double h, int sz);
double **hessian_matrix(double (**f)(double *), double *x, double h, int sz);
double *fixedPoint_nonLinear(double *(*f)(double *), double *x0, int sz, double TOL, int nMax);
double *newton_sys(double (**f)(double *), double *x0, double h, int sz, double TOL, int nMax);
double *broyden_sys(double (**f)(double *), double *x0, double h, int sz, double TOL, int nMax);
double *cg_Freeves(double (**f)(double *), double *x0, double dh, int sz, double TOL, int nMax);
double *gradiente(double (**f)(double *), double *x, double h, int sz);
double **gauss_parc_inversa(double **matriz, int sz);
double **inverseMatrix(double **matriz, int sz);
double inf_norm(double *r1, double *r2, int sz);
double **mult_matxmat(double **m1, double **m2, int nRows, int nEqs, int nCols);
double *mult_matxvec(double **matriz, double *vector, int nRows, int nCols);
double *mult_vecxmat(double **matriz, double *vector, int nRows, int nCols);
double mult_vecxvec(double *v1, double *v2, int sz);
double **trans_mat(double **matriz, int nRows, int nCols);
Factor *QR(double **matriz, int sz);
double **GramS(double **matriz, int sz);
double *solver_lu(double **matriz, double *vectorb, int sz, int o);
double **fact_Cholesky(double **matriz, int sz);
double **fact_LuCrout(double **matriz, int sz);
double *lSolve(double **matriz, double *vec, int sz);
double *uSolve(double **matriz, double *vec, int sz);
double **genMatriz(int nRows, int nCols);
void print_mat(double **matriz, char *name, int nRows, int nCols);
void free_mat(double **matriz, int sz);
void free_factor(Factor *sol);

#endif
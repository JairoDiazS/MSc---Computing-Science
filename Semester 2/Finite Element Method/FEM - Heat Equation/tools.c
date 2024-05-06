/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/*************Herramientas*************/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Libreria de herramientas con programacion dinamica*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "tools.h"


//Subrutina para generar un arreglo dinamico
double *genVector(int size){
    //Se define el espacio
    double* vector = (double *)calloc(size, sizeof(double));
    if(vector == NULL){
		printf("Error de asignacion de memoria.\n");
		return NULL;
	}
    return vector;
}

//Subrutina para generar un arreglo dinamico
int *genVector_int(int size){
    //Se define el espacio
    int* vector = (int *)calloc(size, sizeof(int));
    if(vector == NULL){
		printf("Error de asignacion de memoria.\n");
		return NULL;
	}
    return vector;
}

//Subrutina para generar una matriz en 0's
double **genMatrix(int nRows, int nCols){
	//Definimos el espacio para la matriz
	double **matriz, *temp;
	matriz = (double **)malloc(nRows * sizeof(double *));
	if(matriz == NULL){
		printf("Error de asignacion de memoria.\n");
		return NULL;
	}
	temp = (double *)calloc(nRows * nCols, sizeof(double));
	if(temp == NULL){
		printf("Error de asignacion de memoria.\n");
		free(matriz);
		return NULL;
	}
	for(int i = 0; i< nRows; i++){
		matriz[i] = &temp[i * nCols];
	}
	return matriz;
}

//Subrutina para generar una matriz en 0's
int **genMatrix_int(int nRows, int nCols){
	//Definimos el espacio para la matriz
	int **matriz, *temp;
	matriz = (int **)malloc(nRows * sizeof(int *));
	if(matriz == NULL){
		printf("Error de asignacion de memoria.\n");
		return NULL;
	}
	temp = (int *)calloc(nRows * nCols, sizeof(int));
	if(temp == NULL){
		printf("Error de asignacion de memoria.\n");
		free(matriz);
		return NULL;
	}
	for(int i = 0; i< nRows; i++){
		matriz[i] = &temp[i * nCols];
	}
	return matriz;
}

//Subrutina para leer una matriz
void leerMatriz_int(int **Mat, char *name, int *nRows, int *nCols){
	FILE *file = fopen(name, "r");
	// Verificar si el archivo se abrió correctamente
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
		return;
    }

	/*Se leen las dimensiones de la matriz*/
	fscanf(file, "%d %d", nRows, nCols);
	// Se rellena la matriz
    for (int i = 0; i < *nRows; i++) {
        for (int j = 0; j < *nCols; j++) {
            fscanf(file, "%d", &Mat[i][j]);  // Corregir cómo se accede a la matriz
        }
    }

	fclose((file));
}

//Subrutina para leer una matriz
void leerMatriz_double(double **Mat, char *name, int *NElem, int *NNode){
	FILE *file = fopen(name, "r");
	// Verificar si el archivo se abrió correctamente
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
		return;
    }

	/*Se leen las dimensiones de la matriz*/
	fscanf(file, "%d %d", NElem, NNode);
	for(int i=0; i<*NElem; i++){
		for(int j=0; j<*NNode; j++){
			fscanf(file, "%lf", &Mat[i][j]);
		}
	}

	fclose((file));
}

//Subrutina para liberar una matriz contigua
void freeMat_int(int **mat){
	free(mat[0]);
	free(mat);
}

//Subrutina para liberar una matriz contigua
void freeMat_double(double **mat){
	free(mat[0]);
	free(mat);
}

//Subrutina para imprimir una matriz a un archivo
void print_mat(double **matriz, char *name, int nRows, int nCols){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            fprintf(file, "%lf\t", matriz[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

//Subrutina para imprimir una matriz a un archivo
void print_mat_int(int **matriz, char *name, int nRows, int nCols){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            fprintf(file, "%d\t", matriz[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

//Subrutina para imprimir una matriz a un archivo
void print_vec(double *vec, char *name, int sz){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int j=0; j<sz; j++){
        fprintf(file, "%lf\n", vec[j]);
    }
    fclose(file);
}

//Subrutina para imprimir una matriz a un archivo
void print_vec_int(int *vec, char *name, int sz){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int j=0; j<sz; j++){
        fprintf(file, "%d\n", vec[j]);
    }
    fclose(file);
}

//Subrutina para leer matrices desde la terminal
double **r_mat(const char *fn, int *nRows, int *nCols){
    //Abrimos el archivo en modo lectura
    FILE *file = fopen(fn, "r");
    if(file == NULL){
        printf("Error de apertura de archivo.\n");
        return NULL;
    }
    //Se lee la primer linea del archivo que debe tener el numero de evaluaciones
    fscanf(file, "%d %d", nRows, nCols);

    //Se crea espacio para el arreglo
    double **matriz = genMatrix(*nRows, *nCols);
    if(matriz == NULL){
        printf("Error de asignacion de memoria.\n");
        fclose(file);
        return NULL;
    }

    // Se rellena la matriz
    for (int i = 0; i < *nRows; i++) {
        for (int j = 0; j < *nCols; j++) {
            fscanf(file, "%lf", &matriz[i][j]);  // Corregir cómo se accede a la matriz
        }
    }

    fclose(file);

    return matriz;
}

//Subrutina para leer matrices desde la terminal
int **r_mat_int(const char *fn, int *nRows, int *nCols){
    //Abrimos el archivo en modo lectura
    FILE *file = fopen(fn, "r");
    if(file == NULL){
        printf("Error de apertura de archivo.\n");
        return NULL;
    }
    //Se lee la primer linea del archivo que debe tener el numero de evaluaciones
    fscanf(file, "%d %d", nRows, nCols);

    //Se crea espacio para el arreglo
    int **matriz = genMatrix_int(*nRows, *nCols);
    if(matriz == NULL){
        printf("Error de asignacion de memoria.\n");
        fclose(file);
        return NULL;
    }

    // Se rellena la matriz
    for (int i = 0; i < *nRows; i++) {
        for (int j = 0; j < *nCols; j++) {
            fscanf(file, "%d", &matriz[i][j]);  // Corregir cómo se accede a la matriz
        }
    }

    fclose(file);

    return matriz;
}

void print_postproc(char *fn, double *phi, double **q_pg, double **q_n, int NPoints, int NElem, int NDim){
    FILE *f = fopen(fn, "w");
    if(f == NULL){
        printf("Error al abrir el archivo de postproceso.\n");
        return;
    }
    fprintf(f, "GiD Post Results File 1.0\n");
    fprintf(f, "\n");
    fprintf(f, "Result \"U_Values\" \"Case_1\" 1 Scalar OnNodes\n");
    fprintf(f, "Values\n");
    for(int i=0; i<NPoints; i++){
        fprintf(f, "%6d %lf\n", i+1, phi[i]);   
    }
    fprintf(f, "End Values\n\n");

    fprintf(f, "Result \"Element_Fluxes\" \"Case_1\" 1 Vector OnGaussPoints \"GP_ELEMENT_1\"\n");
    fprintf(f, "ComponentNames \"X-Flux\", \"Y-Flux\", \"Z-Flux\"\n");
    fprintf(f, "Values\n");
    for(int i=0; i<NElem; i++){
        if(NDim==1){
            fprintf(f, "%6d %lf %lf %lf\n", i+1, q_pg[i][0], 0.0, 0.0);
        } else if(NDim==2){
            fprintf(f, "%6d %lf %lf %lf\n", i+1, q_pg[i][0], q_pg[i][1], 0.0);
        } else{
            fprintf(f, "%6d %lf %lf %lf\n", i+1, q_pg[i][0], q_pg[i][1], q_pg[i][2]);
        }
    }
    fprintf(f, "End Values\n\n");

    fprintf(f, "Result \"Nodal_Fluxes\" \"Case_1\" 1 Vector OnNodes\n");
    fprintf(f, "ComponentNames \"X-Flux\", \"Y-Flux\", \"Z-Flux\"\n");
    fprintf(f, "Values\n");
    for(int i=0; i<NPoints; i++){
        if(NDim==1){
            fprintf(f, "%6d %lf %lf %lf\n", i+1, q_n[i][0], 0.0, 0.0);
        } else if(NDim==2){
            fprintf(f, "%6d %lf %lf %lf\n", i+1, q_n[i][0], q_n[i][1], 0.0);
        } else{
            fprintf(f, "%6d %lf %lf %lf\n", i+1, q_n[i][0], q_n[i][1], q_n[i][2]);
        }
    }
    fprintf(f, "End Values\n\n");
}
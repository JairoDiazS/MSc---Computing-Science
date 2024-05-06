/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/************Elemento finito***********/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Elemento finito*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tools.h"
#include "algebra.h"
#include "solvers.h"

int main(int argc, char** argv){
    /*Declaracion de las variables globales*/
    int NDim;       //Tamanio de dimension
    int NNode;      //Numero de nodos por elemento
    int NPoints;    //Numero de puntos en la malla
    int NElem;      //Numero de elementos
    int NMats;      //Numero de materiales
    int NRestD;     //Numero de restricciones de Drichlet
    int NRestN;     //Numero de restricciones de Neumann
    int NPointG;    //Numero de puntos de cuadratura Gaussiana

    /*Lectura de archivos*/
    FILE *cnts_file = fopen(argv[1], "r");
    // Verifica si el archivo se abrió correctamente
    if (cnts_file == NULL) {
        printf("Error al abrir el archivo de conteos.\n");
        return 1;
    }
    fscanf(cnts_file, "NDIM %d ", &NDim);
    fscanf(cnts_file, "NNode %d ", &NNode);
    fscanf(cnts_file, "NPoints %d ", &NPoints);
    fscanf(cnts_file, "NElem %d ", &NElem);
    fscanf(cnts_file, "NMats %d ", &NMats);
    fscanf(cnts_file, "NRestD %d ", &NRestD);
    fscanf(cnts_file, "NRestN %d", &NRestN);

    printf("Numero de dimension: %d\n", NDim);
    printf("Numero de puntos: %d\n", NPoints);
    printf("Numero de nodos por elemento: %d\n", NNode);
    printf("Numero de elementos: %d\n", NElem);

    fclose(cnts_file);

    /*Lectura de la malla*/
    FILE *mesh_file = fopen(argv[2], "r");
    if (mesh_file == NULL) {
        printf("Error al abrir el archivo MESH.\n");
        return 1;
    }
    char elemType[1000] ;
    // Lee el numero de nodos y elementos
    fscanf(mesh_file, "MESH \"malla_1\" dimension %*d Elemtype %s Nnode %*d ", elemType);

    if(strcmp(elemType, "Line") == 0){
        // Comparacion correcta, elemType es igual a "Linear"
        NDim = 1;
    }

    /*Reservando el espacio de memoria*/
    int** LNods = genMatrix_int(NElem, NNode);   //Que nodos pertenecen a que elementos
    double** Coord = genMatrix(NPoints, NDim);  //Coordenadas de los puntos
    int* Mater = genVector_int(NElem);   //Coeficiente k para diferentes mats
    double** CMats = genMatrix(NMats, 2);   //Catalogo de materiales
    int* RestD_nodes = genVector_int(NRestD);  //Restricciones de Drichlet Nodos
    int* RestN_nodes =  genVector_int(NRestN);  //Restricciones de Neumann Nodos
    double* RestD = genVector(NRestD); //Restricciones de Drichlet
    double* RestN = genVector(NRestN); //Restricciones de Newmann

    //Generacion de la matriz de Rigidez
    /*Declaracion de variables locales*/
    double** DBMat = genMatrix(NDim, NNode);    //Resultado de matriz D*B
    double** DCart = genMatrix(NDim, NNode);    //Derivadas cartesianas
    double* FForma = genVector(NNode);  //Funcion de Forma
    double** Deriv = genMatrix(NNode, NDim);    //Matriz de derivadas en el espacio normalizado
    double** CoordEl = genMatrix(NNode, NDim);  //Coordenadas de cada nodo para un elemento
    double** Rigid = genMatrix(NPoints, NPoints);   //Matriz de rigidez
    double** BMat = genMatrix(NDim, NNode);     //Matriz B
    double** DMat = genMatrix(NNode, NDim);     //Matriz D
    double** Jacobian = genMatrix(NDim, NDim);  //Matriz Jacobiana
    double** invJacobian = genMatrix(NDim, NDim);   //Jacobiana inversa
    double** K_e = genMatrix(NNode, NNode);     //Matriz de rigidez elemental
    double** temp = genMatrix(NNode, NNode);    //Matriz temporal
    double *F = genVector(NPoints); //Vector F /del lado derecho
    double *F_e = genVector(NNode); //Vector F elemental

    /*Auxiliares*/
    double kq;
    double *x0 = genVector(NDim);
    double eval;
    double dJac;
    double Q;

    // Se solicita el espacio para cada una de las varibles secundarias
    double** P = genMatrix(NPoints, NDim);
    double* q_pg = genVector(NDim);
    double** q = genMatrix(NPoints, NDim);
    double* phi_e = genVector(NNode);
    double** p_e = genMatrix(NNode, NDim);
    double** temp1 = genMatrix(NNode, NDim);
    double** temp2 = genMatrix(NNode, NNode);
    double** m_e = genMatrix(NNode, NNode);
    double** M = genMatrix(NPoints, NPoints);
    double** q_pgflux = genMatrix(NElem, NDim);

    //Lectura de los nodos
    // if(fscanf(mesh_file, "Coordinates ")==1) printf("coords\n");
    // fscanf(mesh_file, "#node number coord-X coord-Y ");
    char buffer[10000];
    fgets(buffer, 10000, mesh_file);
    fgets(buffer, 10000, mesh_file);

    // Lee las coordenadas de los nodos
    if(NDim==1){
        for (int i = 0; i < NPoints; ++i) {
            fscanf(mesh_file, "%*d %lf %*lf ", &Coord[i][0]);
        }
    }
    else if(NDim==2){
        for (int i = 0; i < NPoints; ++i) {
            fscanf(mesh_file, "%*d %lf %lf ", &Coord[i][0], &Coord[i][1]);
        }
    }
    else if(NDim==3){
        for (int i = 0; i < NPoints; ++i) {
            fscanf(mesh_file, "%*d %lf %lf %lf ", &Coord[i][0], &Coord[i][1], &Coord[i][2]);
        }
    }

    fgets(buffer, 10000, mesh_file);

    // Lee la seccion de elementos
    fgets(buffer, 10000, mesh_file);
    fgets(buffer, 10000, mesh_file);

    for(int i=0; i<NElem; i++){
        fscanf(mesh_file, "%*d ");
        for(int j=0; j<NNode; j++){
            fscanf(mesh_file, "%d ", &LNods[i][j]);
            LNods[i][j]--;
        }
        fscanf(mesh_file, "%d ", &Mater[i]);
        Mater[i]--;
    }
    // Cierra el archivo despues de leer
    fclose(mesh_file);

    /*Leectura del archivo de condiciones iniciales*/
    FILE *cond_file = fopen(argv[3], "r");
    if(cond_file == NULL){
        printf("Error al abrir el archivo Condiciones iniciales.\n");
        return 1;
    }
    if(NRestD >0 && NRestN == 0){
        fgets(buffer, 10000, mesh_file);
        for(int i =0; i<NRestD; i++){
            fscanf(cond_file, "%d %lf ", &RestD_nodes[i], &RestD[i]);
            RestD_nodes[i]--;
        }
    } else if(NRestN >0 && NRestD == 0){
        fgets(buffer, 10000, mesh_file);
        for(int i =0; i<NRestN; i++){
            fscanf(cond_file, "%d %lf ", &RestN_nodes[i], &RestN[i]);
            RestD_nodes[i]--;
        }
    } else {
        fgets(buffer, 10000, mesh_file);
        for(int i =0; i<NRestN; i++){
            fscanf(cond_file, "%d %lf ", &RestD_nodes[i], &RestD[i]);
            RestD_nodes[i]--;
        }
        fgets(buffer, 10000, mesh_file);
        for(int i =0; i<NRestD; i++){
            fscanf(cond_file, "%d %lf ", &RestN_nodes[i], &RestN[i]);
            RestD_nodes[i]--;
        }
    }
    
    fclose(cond_file);

    /*Lectura de archivo de materiales*/
    FILE *mats_file = fopen(argv[4], "r");
    if(mats_file == NULL){
        printf("Error al abrir el archivo Condiciones iniciales.\n");
        return 1;
    }
    fgets(buffer, 10000, mesh_file);
    fgets(buffer, 10000, mesh_file);
    for(int i=0; i<NMats; i++){
        fscanf(mats_file, "%*d %lf %lf ", &CMats[i][0], &CMats[i][1]);
    }

    fclose(cond_file);

    print_mat(Coord, "coords.txt", NPoints, NDim);
    print_mat_int(LNods, "lnods.txt", NElem, NNode);
    print_vec(RestD, "rest.txt", NRestD);
    print_vec_int(RestD_nodes, "rest_n.txt", NRestD);
    print_mat(CMats, "mats.txt", NMats, 2);

    /*Primero resolvemos el sistema para determinar la matriz de rigidez y el
    vector de lado derecho*/

    //Calculando el numero de puntos de Gauss
    get_NPointG(NDim, NNode, &NPointG);
    double** PGauss = genMatrix(NPointG, NDim);  //Valores de los puntos de Gauss
    double* WGauss = genVector(NPointG);    //Valores de los pesos de Gauss
    //Se obtienen los valores de la cuadratura Gaussiana
    Gauss(PGauss, WGauss, NDim, NNode);

    //Inicializamos el ciclo a traves del numero de elementos
    int i, j, k, l, m;
    for(i=0; i<NElem; i++){
        //Inicializar la matriz de rigidez elemental
        for(j=0; j<NNode; j++){
            F_e[j] = 0.0;
            for(k = 0; k<NNode; k++){
                K_e[j][k] = 0.0;
            }
        }
        /*Esta ya esta inicializada en 0's*/
        for(j=0;j<NDim; j++){
            for(k=0; k<NNode; k++){
                BMat[j][k] = 0.0;
            }
        }

        //Cargar coordenadas del elemento
        for(j=0; j<NNode; j++){
                k = LNods[i][j];
            for(l=0; l<NDim; l++){
                CoordEl[j][l] = Coord[k][l];
            }
        }

        //Informacion del material
        /*Se supone material homogeneo*/
        j = Mater[i];    //Informacion del material para el elemento
        kq = CMats[j][1];  //Informacion del catalogo de matereiales
        Q = CMats[j][0];  //Informacion del catalogo de matereiales

        //Se inicializa la matriz D
        for(j=0; j<NDim; j++) DMat[j][j] = kq;

        /*Se establece en 0's*/
        for(k=0; k<NDim; k++){
            for(l=0; l<NDim; l++){
                Jacobian[k][l] = 0.0;
                invJacobian[k][l] = 0.0;
            }
        }

        //Inicializamos el ciclo sobre los puntos de integracion
        for(j=0; j<NPointG; j++){
            /*Se asignan los puntos de gauss*/
            for(k=0; k<NDim; k++){
                x0[k] = PGauss[j][k];
            } 

            //Evaluamos los puntos en cada valor de las coordenadas
            evalFForma(FForma, x0, NDim, NNode);

            //Obtenemos las derivadas
            evalDerive(Deriv, x0, NDim, NNode);
            if(i==412) print_mat(Deriv, "derivada.txt", NNode, NDim);

            //Se obtiene el Jacobiano
            evalJacobian(Jacobian, CoordEl, Deriv, NDim, NNode);
            if(i==412) print_mat(Jacobian, "jacobiano.txt", NDim, NDim);

            //Se obtiene el inverso del Jacobiano
            inverseMatrix(invJacobian, Jacobian, NDim);
            if(i==412) print_mat(invJacobian, "jacobiano_inv.txt", NDim, NDim);
            
            //Se calcula B
            //Se obtiene la derivada cartesiana
            evalDeriveCart(BMat, invJacobian, Deriv, NDim, NNode);

            //Se evalua la integral
            //Se obtiene el Jacobiano
            dJac = detMatrix(Jacobian, NDim);
            if(dJac<=0) printf("error del Jacobiano %lf\n", dJac);
            dJac = fabs(dJac);
            //printf("%lf\n", dJac);

            /*Se calcula DBMat*/
            mult_matxmat(DBMat, DMat, BMat, NDim, NDim, NNode);

            /*Se Calcula BtDBMat*/
            mult_matinvxmat(temp, BMat, DBMat, NNode, NDim, NNode);

            /*Se suma a la matriz elemental*/
            for(k=0; k<NNode; k++){
                F_e[k] += FForma[k] * Q * dJac * WGauss[j];
                for(l=0; l<NNode; l++){
                    K_e[k][l] += temp[k][l]*dJac*WGauss[j];
                }
            }
        }
        if(i==412) print_mat(K_e, "ke.txt", NNode, NNode);  
        if(i==412) print_mat(BMat, "BMAT.txt", NDim, NNode);
        ensamblarMatriz(Rigid, K_e, i, NNode, LNods);
        ensamblarVector(F, F_e, i, NNode, LNods);

    }

    printf("Finalizo correctamente.\n");
    printf("Numero de puntos de Gauss: %d\n", NPointG);

    /*Ahora, vamos a forzar las condiciones que se nos proponen*/
    for(i = 0; i<NRestD; i++){
        //Se selecciona el nodo de la condicion
        j = RestD_nodes[i];
        if(j==181) printf("ERROR\n");
        
        //Igualamos a 0 toda la fila y columna donde se encontro la restriccion
        for(k=0; k<NPoints; k++){
            Rigid[j][k] = 0.0;
        }

        //Se iguala a 1 la contribucion del nodo de la condicion
        Rigid[j][j] = 1.0;

        //Se suma la condicion al vector del lado derecho
        F[j] = RestD[i];
    }
    printf("Hola\n");
    print_mat(Rigid, "rigid.txt", NPoints, NPoints);
    for(int i=0; i<NPoints; i++){
        if(fabs(Rigid[i][i])<1E-8) printf("%d\t%lf\n",i, Rigid[i][i]);
    }
    //Se resuelve el sistema
    double* Phi = gradienteJacobi(Rigid, F, NPoints, 0.000001, 100000);

    /* Una vez se ha resuelto la variable principal continuamos el proceso para
    la variable secundaria*/

    // Ciclo sobre los elementos
    for(i=0; i<NElem; i++){
        // Se inicializa en 0's
        for(j=0; j<NDim; j++) q_pg[j] = 0.0;

        //Informacion del material
        /*Se supone material homogeneo*/
        j = Mater[i];    //Informacion del material para el elemento
        kq = CMats[j][1];  //Informacion del catalogo de matereiales
        Q = CMats[j][0];  //Informacion del catalogo de matereiales

        //Se inicializa la matriz D
        for(j=0; j<NDim; j++) DMat[j][j] = kq;

        /*Esta ya esta inicializada en 0's*/
        for(j=0;j<NDim; j++){
            for(k=0; k<NNode; k++){
                BMat[j][k] = 0.0;
            }
        }

        /*Se establece en 0's*/
        for(k=0; k<NDim; k++){
            for(l=0; l<NDim; l++){
                Jacobian[k][l] = 0.0;
                invJacobian[k][l] = 0.0;
            }
        }

        //Cargar coordenadas del elemento
        for(j=0; j<NNode; j++){
                k = LNods[i][j];
                phi_e[j] = Phi[k];
            for(l=0; l<NDim; l++){
                CoordEl[j][l] = Coord[k][l];
            }
        }

        //Se inicializan en 0's
        for(k=0; k<NNode; k++){
            for(l=0; l<NDim; l++){
                p_e[k][l] = 0.0;
                temp1[k][l] = 0.0;
            }
            for(l=0; l<NNode; l++){
                m_e[k][l] = 0.0;
                temp2[k][l] = 0.0;
            }
        }

        //Inicializamos el ciclo sobre los puntos de integracion
        for(j=0; j<NPointG; j++){
            /*Esta ya esta inicializada en 0's*/
            for(k=0; k<NDim; k++){
                x0[k] = PGauss[j][k];
            }

            //Obtenemos las derivadas
            evalDerive(Deriv, x0, NDim, NNode);

            //Se obtiene el Jacobiano
            evalJacobian(Jacobian, CoordEl, Deriv, NDim, NNode);

            //Se obtiene el inverso del Jacobiano
            inverseMatrix(invJacobian, Jacobian, NDim);
            
            //Se calcula B
            //Se obtiene la derivada cartesiana
            evalDeriveCart(BMat, invJacobian, Deriv, NDim, NNode);

            //Se evalua la integral
            //Se obtiene el Jacobiano
            dJac = detMatrix(Jacobian, NDim);
            //printf("%lf\n", dJac);

            /*Se calcula DBMat*/
            mult_matxmat(DBMat, DMat, BMat, NDim, NDim, NNode);

            // Se obtiene el flujo en el punto de Gauss
            mult_matxvec(q_pg, DBMat, phi_e, NDim, NNode);
            for(k=0;k<NDim;k++) q_pgflux[i][k] += q_pg[k];

            // Se multiplica por las funciones de forma
            mult_vecfxvecc(temp1, FForma, q_pg, NNode, NDim);

            //Se prepara para la matriz de masa
            mult_vecfxvecc(temp2, FForma, FForma, NNode, NNode);

            //Se agrega a la matriz p elemental/M elemental
            for(k=0; k<NNode; k++){
                for(l=0; l<NDim; l++){
                    p_e[k][l] += temp1[k][l]*WGauss[j]*dJac;
                }
                for(l=0; l<NNode; l++){
                    m_e[k][l] += temp2[k][l]*WGauss[j]*dJac;
                }
            }
        }
        // Se ensambla P
        ensamblarP(P, p_e, i, NDim, LNods, NNode);
        // Se ensambla M
        ensamblarMatriz(M, m_e, i, NNode, LNods);
    }
    for(i=0; i<NElem;i++){
        for(j=0;j<NDim;j++) q_pgflux[i][j] /= NNode;
    }

    print_vec(Phi, "phi_vec.txt", NPoints);
    print_mat(q_pgflux, "flux_pg.txt", NElem, NDim);

    //Resolvemos los flujos
    solver_flux_sys(q, M, P, NPoints, NDim);

    print_mat(q,"flux.txt", NPoints, NDim);

    print_postproc("post.res", Phi, q_pgflux, q, NPoints, NElem, NDim);

    freeMat_int(LNods);
    freeMat_double(Coord);
    free(Mater);
    free(CMats);
    free(RestD);
    free(RestN);
    freeMat_double(DBMat);
    freeMat_double(DCart);
    free(FForma);
    freeMat_double(Deriv);
    freeMat_double(CoordEl);
    freeMat_double(PGauss);
    free(WGauss);
    freeMat_double(Rigid);
    freeMat_double(BMat);
    freeMat_double(DMat);
    freeMat_double(Jacobian);
    freeMat_double(invJacobian);
    freeMat_double(K_e);
    freeMat_double(temp);
    free(F);
    free(F_e);
    free(x0);
    free(RestD_nodes);
    free(RestN_nodes);
    freeMat_double(P);
    free(q_pg);
    freeMat_double(q);
    free(phi_e);
    freeMat_double(p_e);
    freeMat_double(temp1);
    freeMat_double(temp2);
    freeMat_double(m_e);
    freeMat_double(M);
    free(Phi);
    freeMat_double(q_pgflux);

    return 0;
}
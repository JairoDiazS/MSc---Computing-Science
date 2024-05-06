/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 1 Cabecera**********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

using namespace std;

#ifndef TAREA1_H
#define TAREA1_H

#define PI 3.141592

class figuraGeometrica {
    public:
        double perimetro;
        double area;
        figuraGeometrica(double P, double A): perimetro(P), area(A) {}
        void setArea(){};
};

class circulo : public figuraGeometrica {
    public:
        double radio;

        circulo(double R) : figuraGeometrica(0,0), radio(R){
            setArea();
            setPerimetro();
        }
        void setArea() {
            area = radio * radio * PI;
        }
        void setPerimetro() {
            perimetro = 2 * PI * radio;
        }

        void setRadio(){
            radio = perimetro / (2 * PI);
        }
};

class cuadrado : public figuraGeometrica {
    public:
        double lado;

        cuadrado(double l) : figuraGeometrica(0,0), lado(l) {
            setPerimetro();
            setArea();
        }

        void setPerimetro(){
            perimetro = lado * 4;
        }

        void setArea(){
            area = lado * lado;
        }

        void setLado(){
            lado = perimetro / 4;
        }
};

vector<double> r_numeros(const char *);
void w_numeros(vector<double> &, const char *);
void dangling_function(vector<int>& , int);
double sumaArreglo(double *, int);
void randArray(double *, int);
double suma(double, double);
double resta(double, double);
double multiplicacion(double, double);
double division(double, double);
double safeDivision(double, double);

#endif


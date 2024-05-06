Tarea 10: METODOS Regresion por mínimos cuadrados, integración por métodos de Newton - Cotes abiertos y cerrados, integración por cuadratura gaussiana.
Hecho en Windows WSL
Compilacion: 	$ gcc ej1.c -o ej1 -lm	//Mínimos Cuadrados
		$ gcc ej2.c -o ej2 -lm	//Integración numérica


Ejecución:	./RUN #arch_ptosx grad_polinomio	//Mínimos cuadrados (el grado es uno menor del que se ingresa)
		./RUN					//Integración númerica
		NOTA!!! El primer valor de los archivos debe tener el numero de datos(pares o puntos) que contiene.
 
DESCRIPCION: 	

OPCIONES]					Ejemplo]
	1 Mínimos Cuadrados		./RUN puntosx.txt 4
	2 Integración numérica		./RUN

PROGRAMA PRINCIPAL]

ENTRADA: #arch_paresx n (Segun corresponda)
SALIDA: Escritura de archivos con los puntos hallados y/o impresion en terminal.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información o se manda al archivo.

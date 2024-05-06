Tarea 8: METODOS Interpolacion Taylor, Lagrange, Neville, Diferencias Divididas de Newton.
Hecho en Windows WSL
Compilacion: 	$ gcc ej1.c -o ej1 -lm	//Taylor
		$ gcc ej2.c -o ej2 -lm	//Lagrange
		$ gcc ej3.c -o ej3 -lm	//Neville
		$ gcc ej4.c -o ej4 -lm	//DD
		$ gcc ej5.c -o ej5 -lm	//Comparativa
		$ gcc ej6.c -o ej6 -lm	//Aplicacion

Ejecución:	./RUN #arch_evaluaciones #arch_puntos_prueba	//Taylor
		./RUN #arch_paresxy				//Lagrange
		./RUN #arch_paresxy				//Neville
		./RUN #arch_paresxy				//DD
		./RUN #arch_paresxy #arch_puntos_prueba		//Comparativa
		./RUN #arch_paresxy				//Aplicacion
	NOTA!!! El primer valor de los archivos debe tener el numero de datos(pares o puntos) que contiene.
 
DESCRIPCION: 	

OPCIONES]							Ejemplo]
	1 Método de Taylor				./RUN evaluaciones.txt puntos.txt
	2 Método de Lagrange				./RUN puntosxy.txt
	3 Método de Neville				./RUN puntosxy.txt
	4 Método de Diferencias divididas de Newton	./RUN puntosxy.txt
	5 Comparativa de métodos			./RUN puntosxy.txt puntos.txt
	6 Aplicación de métodos				./RUN puntosxy.txt

PROGRAMA PRINCIPAL]

ENTRADA: #arch_Matriz nombre de archivo de la matriz y/o #numEigens (Segun corresponda)
SALIDA: Output con max 10 elementos de la solución y la aproximación.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información o se manda al archivo.


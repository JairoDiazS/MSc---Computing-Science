Tarea 10: METODOS diferenciación: hacia delante, hacia atras, centrado, 3 puntos centrados, 3 puntos hacia delatne, 5 puntos centrado, 5 puntos hacia delante, segunda derivada, matriz jacobiana, matriz hessiana; Métodos para sistemas no lineales: punto fijo, newton, broyden y gradiente conjugado de Fletches - Reeves
Hecho en Windows WSL
Compilacion: 	$ gcc ej1.c -o ej1 -lm	//Diferenciacion
		$ gcc ej2.c -o ej2 -lm	//Sistemas no lineales


Ejecución:	./RUN		//Diferenciacion
		./RUN		//Sistemas no lineales (Aqui se obtienen las matrices, se escriben en archivos con nombres sol, sol1 					respectivamrente)
 
DESCRIPCION: 	

OPCIONES]				Ejemplo]
	1 Diferenciacióm		./RUN
	2 Sistemas no lineales		./RUN

PROGRAMA PRINCIPAL]

ENTRADA:
SALIDA: Escritura de archivos con los puntos hallados y/o impresion en terminal.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información o se manda al archivo.

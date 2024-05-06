Tarea 7: METODOS potencia, potencia inversa y jacobi para eigenvalores y vectores
Hecho en Windows WSL
Compilacion: 	$ gcc tarea7a.c -o potencia -lm
		$ gcc tarea7b.c -o potinv -lm
		$ gcc tarea7c.c -o jacobi -lm

Ejecución:	./RUN #arch_Matriz #numEigens 	//Solo para los primeros dos
		./RUN #arch_Matriz 		//Para el de jacobi
 
DESCRIPCION: 	

OPCIONES]								Ejemplo]
	1 Método de Potencia					./RUN matriz.txt 3
	2 Método de Potencia inversa				./RUN matriz.txt 3
	3 Método de Jacobi					./RUN matriz.txt

PROGRAMA PRINCIPAL]

ENTRADA: #arch_Matriz nombre de archivo de la matriz y/o #numEigens (Segun corresponda)
SALIDA: Output con max 10 elementos de la solución y la aproximación.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información o se manda al archivo.

#Comentarios adicionales
Si se desea validar o cambiar el número máximo de iteraciones y la tolerancia epsilon puede modificarlos en el precompilador lineas 13 y 14 respectivamente.


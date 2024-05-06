Tarea 6: METODOS Jacobi y Gauss - Seidel
Hecho en Windows WSL
Compilacion: 	$ gcc metJacobi.c -o jacobi -lm
		$ gcc metGaussseidel.c -o gauss -lm
Ejecución: ./RUN #arch_Matriz #arch_Vector
 
DESCRIPCION: 	

OPCIONES]							Ejemplo]
	1 Método de Jacobi					./RUN matriz.txt vector.txt
	2 Método de Gauss - Seidel				./RUN matriz.txt vector.txt

PROGRAMA PRINCIPAL]

ENTRADA: #arch_Matriz nombre de archivo de la matriz y #arch_vector nombre del archivo del vector.
SALIDA: Output con max 10 elementos de la solución y la aproximación.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información

#Comentarios adicionales
Si se desea validar o cambiar el número máximo de iteraciones y la tolerancia epsilon puede modificarlos en el precompilador lineas 13 y 14 respectivamente.




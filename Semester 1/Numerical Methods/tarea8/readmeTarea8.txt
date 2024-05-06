Tarea 8: METODOS QR(factorizacion), Gradiente Conjugado, Gradiente Conjugado Precondicionado(Jacobi), Rayleigh (Eigenvalor), Iteracion de subespacio.
Hecho en Windows WSL
Compilacion: 	$ gcc qr.c -o qr -lm
		$ gcc gardiente.c -o grad -lm
		$ gcc jacobigrad.c -o jacgrad -lm
		$ gcc rayleigh.c -o ray -lm
		$ gcc subspace.c -o sub -lm

Ejecución:	./RUN #arch_Matriz 			//QR
		./RUN #arch_Matriz #arch_Vector		//Gradiente-precondicionado
		.RUN #arch_Matriz			//Rayleigh
		.RUN #arch_Matriz #numEigen		//Subespacio
		
 
DESCRIPCION: 	

OPCIONES]								Ejemplo]
	1 Método de QR						./RUN matriz.txt
	2 Método de Gradiente Conjugado				./RUN matriz.txt vector.txt
	3 Método de Gradiente Conjugado Precondicionado		./RUN matriz.txt vector.txt
	4 Método de Rayleigh					./RUN matriz.txt
	5 Mètodo de Subespacio					./RUN matriz.txt 7

PROGRAMA PRINCIPAL]

ENTRADA: #arch_Matriz nombre de archivo de la matriz y/o #numEigens (Segun corresponda)
SALIDA: Output con max 10 elementos de la solución y la aproximación.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información o se manda al archivo.

#Comentarios adicionales
Si se desea validar o cambiar el número máximo de iteraciones y la tolerancia epsilon puede modificarlos en el precompilador lineas 13 y 14 respectivamente.

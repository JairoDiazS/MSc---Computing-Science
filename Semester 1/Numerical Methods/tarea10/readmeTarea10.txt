Tarea 10: METODOS Interpolacion Hermite, Cubica Natural, Cubica Fija.
Hecho en Windows WSL
Compilacion: 	$ gcc ej1.c -o ej1 -lm	//Hermite
		$ gcc ej2.c -o ej2 -lm	//Cubica natural (seccionada)
		$ gcc ej2b.c -o ej3 -lm	//Cubica natural (continua)
		$ gcc ej3.c -o ej4 -lm	//Cubica fija


Ejecución:	./RUN 							//Hermite
		./RUN #arch_paresxy1 #arch_paresxy2 #arch_paresxy3	//Cubica natural (seccionada)
		./RUN #arch_paresxy					//Cubica natural (continua)
		./RUN #arch_paresxy1 #arch_paresxy2 #arch_paresxy3	//Cubica fija
	NOTA!!! El primer valor de los archivos debe tener el numero de datos(pares o puntos) que contiene.
 
DESCRIPCION: 	

OPCIONES]							Ejemplo]
	1 Método de Hermite				./RUN
	2 Método de Cubica natural (seccionada)		./RUN puntosxy1.txt puntosxy2.txt puntosxy3.txt
	3 Cubica natural (continua)			./RUN puntosxy.txt
	4 Cubica fija					./RUN puntosxy1.txt puntosxy2.txt puntosxy3.txt

PROGRAMA PRINCIPAL]

ENTRADA: #arch_paresxy... (Segun corresponda)
SALIDA: Escritura de archivos con los puntos hallados.

	1. Se leen los argumentos de terminal
	2. Se leen los archivos
	3. Se resuelve de acuerdo al método elegido. 
	4. Se imprimen en terminal la información o se manda al archivo.


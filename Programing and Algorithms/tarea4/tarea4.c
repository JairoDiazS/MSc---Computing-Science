/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4/Header***********/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "tarea4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXLENGTH 255
#define MAXVALUE  255

//Implementaciones

unsigned char **pgmRead(char *fileName,int *rows,int *cols)
{
      FILE *filePointer;
      char line[MAXLENGTH]; /* for character input from file */
      int maximumValue = 0; /* max value from header */
      int binary;           /* flag to indicate if file is binary (P5) or ascii (P2)*/
      long numberRead = 0;  /* counter for number of pixels read */
      long i,j;             /* (i,j) for loops */
      int test,temp;        /* for detecting EOF(test) and temp storage */
      unsigned char *tempPtr, **image;

      /* Open the file, return an error if necessary. */
      if ((filePointer = fopen(fileName,"r")) == NULL) {
	   printf ("ERROR: cannot open file\n\n");
	   fclose (filePointer);
	   return (0);
      }

      *cols = *rows =0;

      /* Check the file signature ("Magic Numbers" P2 and P5); skip comments
         and blank lines (CR with no spaces before it).*/
      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n')
           fgets (line,MAXLENGTH,filePointer);

      if (line[0]=='P' && (line[1]=='2')) {
	   binary = 0;
	 /*   printf ("\nFile Format: P2\n"); */
      }
      else if (line[0]=='P' && (line[1]=='5')) {
	   binary = 1;
	  /*  printf ("\nFORMAT: P5\n"); */
      }
      else {
	   printf ("ERROR: incorrect file format\n\n");
	   fclose (filePointer);
	   return (0);
      }

      /* Input the width, height and maximum value, skip comments and blank
       * lines. */
      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n')
         fgets (line,MAXLENGTH,filePointer);
      sscanf (line,"%d %d",cols,rows);

      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n')
         fgets(line,MAXLENGTH,filePointer);
      sscanf (line,"%d",&maximumValue);

      if ((*cols)<1 ||(*rows)<1 || maximumValue<0 || maximumValue>MAXVALUE){
	   printf ("ERROR: invalid file specifications (cols/rows/max value)\n\n");
	   fclose (filePointer);
	   return (0);
      }

      // creating memory for the input image
      image = (unsigned char **)malloc((*rows) * sizeof(unsigned char *));
      if (image == NULL)
      {
         puts("\nFailure to allocate room for pointers");
         return(NULL);
      }

      tempPtr = (unsigned char *) malloc((*rows)*(*cols)*sizeof(unsigned char));
      if (tempPtr == NULL)
      {
         puts("\nFailure to allocate room for the array");
         return(NULL);
      }
      for (i = 0; i < *rows; i++)
      {
        image[i] = tempPtr + ( i * (*cols) );
      }


      /* Read in the data for binary (P5) or ascii (P2) PGM formats   */
      if (binary) {
	   for (i = 0; i < (*rows); i++) {
	        numberRead += fread((void *)&(image[i][0]),
		  sizeof(unsigned char),(*cols),filePointer);
		if (feof(filePointer)) break;
	   }
      }
      else {
	   for (i= 0; i < (*rows); i++) {
	        for (j =0; j < (*cols); j++) {
	             test = fscanf (filePointer,"%d",&temp);
		     if (test == EOF) break;
		     image[i][j] = (unsigned char)temp;

		     numberRead++;
		}
		if (test == EOF) break;
	   }
      }

      /* close the file and return 1 indicating success */
      fclose (filePointer);
      return (image);
}

/* INPUT: a filename (char*), the dimensions of the pixmap (rows,cols of
 *   type long), and a pointer to a 2D array (MAXROWS x MAXCOLS) in row
 *   major order.
 * OUTPUT: an integer is returned indicating if the desired file was written
 *   (in P5 PGM format (binary)).  A 1 is returned if the write was completed
 *   and 0 if it was not.  An error message is returned if the file is not
 *   properly opened.
 */
int pgmWrite(char* filename, int rows,int cols,unsigned char **image,char* comment_string)
{
      FILE* file;        /* pointer to the file buffer */
      int maxval;        /* maximum value in the image array */
      long nwritten = 0; /* counter for the number of pixels written */
      long i,j;          /* for loop counters */

      /* open the file; write header and comments specified by the user. */
      if ((file = fopen(filename, "w")) == NULL)	{
           printf("ERROR: file open failed\n");
	   return(0);
      }
      fprintf(file,"P5\n");

      if (comment_string != NULL) fprintf(file,"# %s \n", comment_string);

      /* write the dimensions of the image */
      fprintf(file,"%d %d \n", cols, rows);

      /* NOTE: MAXIMUM VALUE IS WHITE; COLOURS ARE SCALED FROM 0 - */
      /* MAXVALUE IN A .PGM FILE. */

      /* WRITE MAXIMUM VALUE TO FILE */
      fprintf(file, "%d\n", (int)255);

      /* Write data */
      for (i = 0;i < rows;i++) {
          nwritten += fwrite((void*)image[i],sizeof(unsigned char),cols,file);
      }
      printf("nwritten = %ld,",nwritten);

      fclose(file);
      return(1);
}

//Subrutina para imprimir una matriz
void imprimirMatriz(unsigned char **matriz, int nRows, int nCols){

	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			printf("%i\t",matriz[i][j]);
		}
		printf("\n");
	}
}

void mean_image(unsigned char **image, int rows, int cols, int wsz, char *newFn){
	//Partimos creando la ventana
	unsigned char **win=crea_img(wsz, wsz);
	//Creamos una matriz para ir guardando los resultados
	unsigned char **meanImg = crea_img(rows, cols);

	//Comenzamos a recorrer la imagen
	int prom=0;
	int cent=wsz/2;
	int mrows=rows-wsz+1;
	int mcols = cols-wsz+1;
	for(int i=0; i< mrows; i++){
		for(int j=0; j< mcols; j++){
			//Asignamos los valores de la matriz a la submatriz
			for(int k=0; k< wsz; k++){
				for(int l=0; l< wsz; l++){
					win[k][l]=image[i+k][j+l];
				}
			}
			//Calculamos el promedio
			prom = mat_mean(win, wsz, wsz);
			//Asignamos el valor del promedio a la nueva matriz
			meanImg[i+cent][j+cent] = prom;
		}
	}
	//Escribimos al archivo PGM
	pgmWrite(newFn, rows, cols, meanImg, NULL);

	//Liberamos los apuntadores
	freePgm(win);
	freePgm(meanImg);
}

//Genera una imagen inicializada en 0's
unsigned char **crea_img(int rows, int cols){
	//reservamos el espacio para la matriz
	unsigned char **image = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	unsigned char *tempPtr = (unsigned char *)malloc(rows * cols *sizeof(unsigned char));
	//Inicializamos la imagen y la asignamos a la matriz;
	for(int i=0; i<rows*cols; i++){
		tempPtr[i]= 0;
		if(i%cols==0) image[i/cols]=tempPtr + i;
	}
	return image;
}

//Calcular promedio de una matriz
double mat_mean(unsigned char **matriz, int rows, int cols){
	double sum=0;
	for(int i=0; i< rows; i++){
		for(int j=0; j< cols; j++) sum+=matriz[i][j];
	}
	sum = sum/(rows*cols);
	return sum;
}

//Libera la memoria aprovechando que es contigua
void freePgm(unsigned char **matriz){
	free(matriz[0]);
	free(matriz);
}

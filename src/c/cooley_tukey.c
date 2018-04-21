#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

void split (complex *matrix, int n) { // coloca os pares no inicio e impares da metade em diante

  complex *heap = malloc(sizeof(complex)*(n/2));
  int i;

  for (i = 0; i < n/2; i++)
    heap[i] = matrix[i*2+1];

  for (i = 0; i < n/2; i++)
    matrix[i] = matrix[i*2];

  for (i = 0; i < n/2; i++)
    matrix[i+n/2] = heap[i];

  free(heap);
}



void fft2 (complex *matrix, int n) {

  if (n >= 2) {
    split(matrix, n); // divide
    fft2(matrix, n/2); // recursao nos pares
    fft2(matrix+n/2, n/2); // recursao nos impares

    int i;

    for (i = 0; i < n/2; i++) { // combina
      complex evens = matrix[i];
      complex odds = matrix[i+n/2];
      complex twiddle = cexp(I*(-2*M_PI*i/n));

      matrix[i] = evens+twiddle*odds;
      matrix[i+n/2] = evens-twiddle*odds;
    }
  }
}


int main(int argc, char *argv[]) {

  complex *matrix = malloc(sizeof(complex)*4);
  matrix[0] = 0 + 0*I;
  matrix[1] = 1 + 0*I;
  matrix[2] = 2 + 0*I;
  matrix[3] = 3 + 0*I;

  FILE *input = fopen(argv[1], "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int height, width, size;
  int position = 0;
  
  if (input == NULL) {
    return 1;
  }

  else {

    read = getline(&line, &len, input);
    height = atoi(line);

    read = getline(&line, &len, input);
    width = atoi(line);

    size = width*height;

    complex *matrix = malloc(sizeof(complex)*size);
    
    while (position < size) {
      getline(&line, &len, input);
      matrix[position] = atoi(line) + 0*I;
      position++;
    }

    fclose(input);

    fft2(matrix, size);

    FILE *output = fopen(argv[2], "w+");
    
    position = 0;

    while (position < size) {
      if (cimag(matrix[position]) >= 0)
	  printf("%f+%fj\n", creal(matrix[position]), cimag(matrix[position]));

      else
	  printf("%f%fj\n", creal(matrix[position]), cimag(matrix[position]));

      position++;
    }

    return 0;
  }

}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>

#define EPSILON 1e-5

double difference(double a, double b);

complex *first_matrix, *second_matrix;
int matrix_size;

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


int run(char *input_file, char *output_file, int step) {

  FILE *input = fopen(input_file, "r");
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
    matrix_size = size;

    complex *matrix = malloc(sizeof(complex)*size);

    if (step == 0) {
        first_matrix = matrix;
    }
    else {
        second_matrix = matrix;
    }

    while (position < size) {
      getline(&line, &len, input);
      matrix[position] = atoi(line) + 0*I;
      position++;
    }

    fclose(input);

    fft2(matrix, size);

    if (step == 0) { // printa só o primeiro resultado
        FILE *output = fopen(output_file, "w+");

        position = 0;

        while (position < size) {
          if (cimag(matrix[position]) >= 0)
    	fprintf(output, "%f+%fj\n", creal(matrix[position]), cimag(matrix[position]));

          else
    	fprintf(output, "%f%fj\n", creal(matrix[position]), cimag(matrix[position]));

          position++;
        }

        fclose(output);
    }

    return 0;
  }

}

int compare() {


    FILE *detected = fopen("detected_failures.txt", "a");
    int i = 0;

    while (i < matrix_size) {
        if (creal(first_matrix[i]) != creal(second_matrix[i]) || cimag(first_matrix[i] != cimag(second_matrix[i]))) {
            fprintf(detected, "1\n");
            return 1;
        }
        i++;
    }

    fclose(detected);
    return 0;
}

int check() {

  int i = 1;
  int j = matrix_size-1;

  FILE *detected = fopen("detected_failures_selective.txt", "a");

  while (i < j) {
    if (difference(creal(first_matrix[i]), creal(first_matrix[j])) >= EPSILON || difference(cimag(first_matrix[i]), -cimag(first_matrix[j])) >= EPSILON) {
      fprintf(detected, "1\n");
      return -1;
    }
    i++;
    j--;
  }

  return 0;
}

double difference(double a, double b) {
  if (a > b) {
    return a - b;
  }
  else {
    return b - a;
  }
}

int main(int argc, char *argv[]) {

    run(argv[1], argv[2], 0);
    check();
}

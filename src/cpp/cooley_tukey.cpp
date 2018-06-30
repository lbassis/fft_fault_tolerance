#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

complex<double> *first_matrix, *second_matrix;
int matrix_size;

void split (complex<double> *matrix, int n) { // coloca os pares no inicio e impares da metade em diante

  complex<double> *heap = new complex<double>[n/2];
  int i;

  for (i = 0; i < n/2; i++)
    heap[i] = matrix[i*2+1];

  for (i = 0; i < n/2; i++)
    matrix[i] = matrix[i*2];

  for (i = 0; i < n/2; i++)
    matrix[i+n/2] = heap[i];

  delete[] heap;
}

void fft2 (complex<double> *matrix, int n) {

  if (n >= 2) {
    split(matrix, n); // divide
    fft2(matrix, n/2); // recursao nos pares
    fft2(matrix+n/2, n/2); // recursao nos impares

    int i;

    for (i = 0; i < n/2; i++) { // combina
      complex<double> evens = matrix[i];
      complex<double> odds = matrix[i+n/2];
      complex<double> twiddle = exp(complex<double>(0, -2*M_PI*i/n));

      matrix[i] = evens+twiddle*odds;
      matrix[i+n/2] = evens-twiddle*odds;
    }
  }
}


int run(char *input_file, char *output_file, int step) {

  string line;
  ifstream file (input_file);
  int width, height, size;



  if (file.is_open())
  {
    getline(file, line);
    width = atoi(line.c_str());
    getline(file, line);
    height = atoi(line.c_str());

    size = width*height;
    matrix_size = size;

    complex<double> *matrix = new complex<double>[size];

    if (step == 0) {
        first_matrix = matrix;
    }

    else {
        second_matrix = matrix;
    }

    complex<double> current;
    int position = 0;

    while (getline(file,line)) {
      current = complex<double>(atof(line.c_str()), 0.0);
      matrix[position] = current;
      position++;
    }


    file.close();

    fft2(matrix, size);

    if (step == 0) {
        ofstream output;
        output.open(output_file);
        for (int i = 0; i < size; i++) {
          if (matrix[i].imag() >= 0)
    	output << matrix[i].real() << "+" << matrix[i].imag() << "j" << endl;
          else
    	output << matrix[i].real() << matrix[i].imag() << "j" << endl;
        }
        output.close();
    }
  }

  else cout << "Unable to open file";
}

int compare() {


    ofstream detected;
    detected.open("detected_failures_cpp.txt");
    int i = 0;

    while (i < matrix_size) {
        if (first_matrix[i].real() != second_matrix[i].real() || first_matrix[i].imag() != second_matrix[i].imag()) {
            detected << "1" << endl;
            return 1;
        }
        i++;
    }

    detected.close();
    return 0;
}


int main(int argc, char *argv[]) {
    run(argv[1], argv[2], 0);
    run(argv[1], argv[2], 1);
    compare();
}

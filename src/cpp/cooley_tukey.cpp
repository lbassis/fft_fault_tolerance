#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

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


int main(int argc, char *argv[]) {

  string line;
  ifstream file (argv[1]);
  int width, height, size;



  if (file.is_open())
  {
    getline(file, line);
    width = atoi(line.c_str());
    getline(file, line);
    height = atoi(line.c_str());

    size = width*height;

    complex<double> *matrix = new complex<double>[size];
    complex<double> current;
    int position = 0;

    while (getline(file,line)) {
      current = complex<double>(atof(line.c_str()), 0.0);
      matrix[position] = current;
      position++;
    }


    file.close();

    fft2(matrix, size);

    ofstream output;
    output.open(argv[2]);
    for (int i = 0; i < size; i++) {
      if (matrix[i].imag() >= 0)
	output << matrix[i].real() << "+" << matrix[i].imag() << "j" << endl;
      else
	output << matrix[i].real() << matrix[i].imag() << "j" << endl;
    }
    output.close();

  }

  else cout << "Unable to open file";



}

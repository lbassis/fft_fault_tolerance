#include <iostream>
#include <cmath>
#include <complex>
//#include <opencv2/opencv.hpp>

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


int main() {

  complex<double> test[4];
  test[0] = complex<double>(1.0, 0.0);
  test[1] = complex<double>(2.0, 0.0);
  test[2] = complex<double>(3.0, 0.0);
  test[3] = complex<double>(4.0, 0.0);

  fft2(test, 4);

  for (int i = 0; i < 4; i++)
    cout << test[i].real() << "+" << test[i].imag() << "i" << endl;
}

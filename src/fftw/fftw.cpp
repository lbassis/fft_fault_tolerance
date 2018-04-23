#include <iostream>
#include <cmath>
#include <fftw3.h>
#include <cstdlib>
#include <fstream>


using namespace std;

fftw_complex *read_in(fftw_complex *input, char *filename, unsigned int *size) {

  string line;
  ifstream file (filename);
  int width, height;


  if (file.is_open())
  {
    getline(file, line);
    width = atoi(line.c_str());
    getline(file, line);
    height = atoi(line.c_str());

    *size = width*height;

    input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (*size));
    int position = 0;

    while (getline(file,line)) {
      input[position][0] = atof(line.c_str());
      input[position][1] = 0;
      position++;
    }
    file.close();
    return input;
  }
}


int main(int argc, char *argv[]) {
  
  fftw_complex *in, *out;
  fftw_plan p;
  unsigned int size;

  in = read_in(in, argv[1], &size);
  out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
  
  p = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);

  ofstream output(argv[2]);
  for (int i = 0; i < size; i++) {
    if (out[i][1] >= 0)
      output << out[i][0] << "+" << out[i][1] << "j" << endl;
    else
      output << out[i][0]  << out[i][1] << "j" << endl;
  }
    output.close();

  
  fftw_destroy_plan(p);
  fftw_free(in);
  fftw_free(out);

  return 0;
}

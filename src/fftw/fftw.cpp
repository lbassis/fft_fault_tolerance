#include <iostream>
#include <cmath>
#include <fftw3.h>
#include <cstdlib>
#include <fstream>


using namespace std;

fftw_complex *first_matrix, *second_matrix;

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

int run(char *input_file, char *output_file, int step) {

    fftw_complex *in, *out;
    fftw_plan p;
    unsigned int size;

    in = read_in(in, input_file, &size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);

    p = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);

    if (step == 0) {
        ofstream output(output_file);
        for (int i = 0; i < size; i++) {
          if (out[i][1] >= 0)
            output << out[i][0] << "+" << out[i][1] << "j" << endl;
          else
            output << out[i][0]  << out[i][1] << "j" << endl;
        }
          output.close();
    }


    fftw_destroy_plan(p);
    fftw_free(in);

    //fftw_free(out);

    if (step == 0)
        first_matrix = out;
    else
        second_matrix = out;

    return 0;
}

int compare() {


    ofstream detected;
    detected.open("detected_failures_fftw.txt", ios::app);
    int i = 0;

    while (i < matrix_size) {
        if (first_matrix[i][0] != second_matrix[i][0] || first_matrix[i][1] != second_matrix[i][1]) {
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
    run(argv[1], argv[2], 0);
    compare();
}

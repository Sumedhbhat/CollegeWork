#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
  double finalpi = 0.0;
  int nums;
  cout << "Enter the number of steps" << endl;
  cin >> nums;
  double steps = (double)1 / nums;

  time_t st, et;

  st = clock();
  printf("%d\n", omp_get_num_threads());
#pragma omp parallel reduction(+ : finalpi)
  for (int i = 0; i < nums; i++) {
    double x = (i + 0.5) * steps;
    double pi = (4 * steps) / (1 + (x * x));
    finalpi += pi;
  }
  et = clock();
  printf("Time taken in parallel is %lf\n", (double)(et - st) / CLOCKS_PER_SEC);
  cout << "The final value of pi is " << finalpi << endl;
  return 0;
}

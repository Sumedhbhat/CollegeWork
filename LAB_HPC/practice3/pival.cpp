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
#pragma omp parallel for reduction(+ : finalpi)
  for (int i = 0; i < nums; i++) {
    double x = (i + 0.5) * steps;
    double pi = (4 * steps) / (1 + (x * x));
    finalpi += pi;
  }
  cout << "The final value of pi is " << finalpi << endl;
  return 0;
}

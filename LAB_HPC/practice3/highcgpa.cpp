#include <climits>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
  double *cgpa;
  int n;
  cout << "Enter the number of students" << endl;
  cin >> n;
  cgpa = (double *)malloc(sizeof(double) * n);
  for (int i = 0; i < n; i++) {
    srand(i);
    cgpa[i] = (double)(rand() % 1000) / 10;
    cout << cgpa[i] << " ";
  }
  cout << endl;
  double highest = INT_MIN;
#pragma omp parallel for
  for (int i = 0; i < n; i++) {
#pragma omp critical
    if (highest < cgpa[i])
      highest = cgpa[i];
  }
  cout << "The highest cgpa is " << highest << endl;
  return 0;
}

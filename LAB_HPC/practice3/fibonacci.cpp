#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
  int n;
  cout << "Enter the number of numbers to be generated" << endl;
  cin >> n;
  int a[n];
  a[0] = 0;
  a[1] = 1;
  if (n == 1)
    cout << a[0] << endl;
  else if (n == 2)
    cout << a[0] << " " << a[1] << endl;
  else {
#pragma omp parallel
    {
#pragma omp single
      {
        cout << "The id of thread for computation " << omp_get_thread_num()
             << endl;
        for (int i = 1; i < n - 1; i++) {
          a[i + 1] = a[i] + a[i - 1];
        }
      }
#pragma omp single
      {
        cout << "The id of thread for printing " << omp_get_thread_num()
             << endl;
        for (int i = 0; i < n; i++) {
          cout << a[i] << endl;
        }
      }
    }
  }
}

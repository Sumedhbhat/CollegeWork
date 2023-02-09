#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main() {
  int n, m;
  cout << "Enter the size of the array and the vector" << endl;
  cin >> n >> m;
  if (m != n) {
    cout << "Multiplication is not possible" << endl;
    exit(0);
  }
  int **arr = (int **)malloc(n * sizeof(int *));
  int *vec = (int *)malloc(m * sizeof(int));
  int *sum = (int *)malloc(m * sizeof(int));
  for (int i = 0; i < n; i++)
    sum[i] = 0;
#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < n; i++) {
      srand(i);
      vec[i] = rand() % 10;
      arr[i] = (int *)malloc(sizeof(int) * n);
      for (int j = 0; j < n; j++) {
        arr[i][j] = rand() % 10;
      }
    }
  }

#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
#pragma omp critical
        sum[i] += arr[i][j] * vec[j];
      }
    }
  }
  cout << "Matrix * Vector Multiplication" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%3d ", arr[i][j]);
    if (i == n / 2)
      printf("* %3d = %6d\n", vec[i], sum[i]);
    else
      printf("  %3d   %6d\n", vec[i], sum[i]);
  }
  return 0;
}

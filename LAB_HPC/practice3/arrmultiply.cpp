#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char **argv) {
  int n, i;
  int **arr1, **arr2, **arr3;
  cout << "Enter the size of the array" << endl;
  cin >> n;

  arr1 = (int **)malloc(sizeof(int *) * n);
  arr2 = (int **)malloc(sizeof(int *) * n);
  arr3 = (int **)malloc(sizeof(int *) * n);
  for (i = 0; i < n; i++) {
    arr1[i] = (int *)malloc(sizeof(int) * n);
    arr2[i] = (int *)malloc(sizeof(int) * n);
    arr3[i] = (int *)malloc(sizeof(int) * n);
    for (j = 0; j < n; j++) {
      arr1[i][j] = rand() % 100;
      arr2[i][j] = rand() % 100;
      arr3[i][j] = 0;
    }
  }
  time_t st, et;

  st = clock();
#pragma omp parallel num_threads(64)
  {
    int j, k;
#pragma omp for
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        for (k = 0; k < n; k++)
          arr3[i][j] += arr1[i][k] * arr2[k][j];
  }
  et = clock();
  printf("Time taken in parallel is %lf\n", (double)(et - st) / CLOCKS_PER_SEC);

  int j, k;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      arr3[i][j] = 0;
    }
  st = clock();
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        arr3[i][j] += arr1[i][k] * arr2[k][j];
  et = clock();
  printf("Time taken in serial is %lf\n", (double)(et - st) / CLOCKS_PER_SEC);

  return 0;
}

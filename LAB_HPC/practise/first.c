#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int i, j, m, n;
  printf("Enter the size of the square matrix");
  scanf("%d", &m);
  printf("Enter the size of the resultant vector");
  scanf("%d", &n);

  if (m != n) {
    printf("Multiplication is not possible");
    exit(0);
  }
  int arr[n][n], res[n], vec[n];

#pragma omp parallel num_threads(n) private(j)
  {
#pragma omp for
    for (int i = 0; i < n; i++) {
      vec[i] = rand() % 100;
      for (int j = 0; j < n; j++) {
        arr[i][j] = rand() % 100;
      }
    }
  }

#pragma omp parallel
  {
#pragma omp for
      for (int i=0; i<n; i++) {
          res[0]=0;
          for (int j=0; j<n; j++) {
              res[i]+=arr[i][j]*vec[j];
          }
      }
  }

  for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
          printf("%3d",arr[i][j]);
      }
      if(i==n/2)
          printf("  *   %3d = %6d\n",vec[i],res[i]);
      else
          printf("      %3d   %6d\n",vec[i],res[i]);
  }
  return 0;
}

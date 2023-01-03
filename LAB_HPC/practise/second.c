#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int sec = 0;
  int ans = 0;
  printf("Enter the number of sections");
  scanf("%d", &sec);
  int arr[sec][100], size[sec];
#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < sec; i++) {
      size[i] = rand() % 20;
      int sum = 0;
      for (int j = 0; j < size[i]; j++) {
        arr[i][j] = rand() % 100;
        sum += arr[i][j];
      }
#pragma omp critical
      ans += sum;
    }
    
  }
printf("The total sum is %d\n", ans);
    for (int i=0; i<sec; i++) {
        printf("Section %d of size %d\n",i,size[i]);
    for (int j=0; j<size[i]; j++) {
        printf("%3d",arr[i][j]);
    }
    printf("\n");
  }
  return 0;
}

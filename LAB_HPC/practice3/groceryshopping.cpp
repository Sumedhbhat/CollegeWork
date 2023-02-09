#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

int main() {
  int n;
  cout << "Enter the number of sections" << endl;
  cin >> n;
  int *size = (int *)malloc(sizeof(int) * n);
  int **arr = (int **)malloc(sizeof(int *) * n);
  int sum = 0;
  int finalsum = 0;
#pragma omp parallel num_threads(n) firstprivate(sum)
  {
    int j;
#pragma omp for
    for (int i = 0; i < n; i++) {
      srand(i);
      size[i] = rand() % 20;
      arr[i] = (int *)malloc(sizeof(int) * size[i]);
      for (int j = 0; j < size[i]; j++) {
        arr[i][j] = rand() % 100;
        sum += arr[i][j];
      }
#pragma omp critical
      finalsum += sum;
    }
  }
  for (int i = 0; i < n; i++) {
    cout << "Section " << i << " of size " << size[i] << endl;
    for (int j = 0; j < size[i]; j++)
      cout << arr[i][j] << " ";
    cout << endl;
  }
  cout << "The final sum of all the items is " << finalsum << endl;
  return 0;
}

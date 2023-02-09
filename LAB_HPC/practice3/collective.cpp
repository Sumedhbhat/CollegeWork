#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {
  int size, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int sendbuf[100], recbuf;

  if (rank == 0) {
    for (int i = 0; i < size; i++) {
      srand(i);
      sendbuf[i] = rand() % 100;
      printf("%d\t", sendbuf[i]);
    }
  }
  MPI_Scatter(&sendbuf, 1, MPI_INT, &recbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
  printf("rank %d received %d\n", rank, recbuf);
  MPI_Finalize();
  return 0;
}

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {
  int size, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int sendbuf, recbuf[100];

  srand(rank);
  sendbuf = rand() % 100;
  printf("Rank %d %d\t\n", rank, sendbuf);
  MPI_Gather(&sendbuf, 1, MPI_INT, &recbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    printf("\n");
    for (int i = 0; i < size; i++) {
      printf("%d ", recbuf[i]);
    }
    printf("\n");
  }
  MPI_Finalize();
  return 0;
}

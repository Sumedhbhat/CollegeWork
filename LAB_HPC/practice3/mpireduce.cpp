#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {
  int send, sum = 0;
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  srand(rank);
  send = rand() % 100;

  if (rank == 0)
    printf("Size of the communicator is %d\n", size);
  printf("We are in process %d and have a total of %d\n", rank, send);
  MPI_Reduce(&send, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("The total sum from all the processes is %d\n", sum);
  }
  MPI_Finalize();
  return 0;
}

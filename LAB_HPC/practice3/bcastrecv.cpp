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
  int recvmsg;
  MPI_Status status;
  srand(rank);
  sendbuf = rand() % 100;
  printf("Rank %d %d\t\n", rank, sendbuf);
  if (rank == 0) {
    MPI_Bcast(&sendbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    MPI_Recv(&recvmsg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    printf("%d", recvmsg);
  }
  MPI_Finalize();
  return 0;
}

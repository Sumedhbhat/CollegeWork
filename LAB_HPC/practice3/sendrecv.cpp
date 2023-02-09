#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char **argv) {
  int size, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status status;
  int sendmsg, recvmsg;

  srand(rank);
  int next, prev;
  sendmsg = rank;

  if (rank == 0)
    prev = size - 1;
  else
    prev = rank - 1;
  if (rank == size - 1)
    next = 0;
  else
    next = rank + 1;
  time_t st, et;

  st = clock();
  if (rank % 2 == 0 && rank < size) {
    MPI_Send(&sendmsg, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    MPI_Recv(&recvmsg, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &status);
  } else if (rank % 2 != 0 && rank < size) {
    MPI_Recv(&recvmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
    MPI_Send(&sendmsg, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  et = clock();
  if (rank == 0)
    printf("%lf\n", (double)(et - st) / CLOCKS_PER_SEC);

  MPI_Request reqs[2];

  st = clock();
  MPI_Isend(&sendmsg, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &reqs[0]);
  MPI_Irecv(&recvmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &reqs[1]);
  MPI_Barrier(MPI_COMM_WORLD);
  et = clock();
  if (rank == 0)
    printf("%lf\n", (double)(et - st) / CLOCKS_PER_SEC);
  MPI_Finalize();
  return 0;
}

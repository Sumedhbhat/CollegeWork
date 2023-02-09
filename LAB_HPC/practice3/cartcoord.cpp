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

  MPI_Request reqs[8];
  MPI_Status stats[8];
  MPI_Comm cartcomm;
  int outbuf, recvmsg[4];
  int dims[2] = {4, 4}, periods[2] = {0, 0}, reorder = 0, coords[2],
      neighbours[4];
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Cart_coords(cartcomm, rank, 2, coords);
  MPI_Cart_shift(cartcomm, 0, 1, &neighbours[0], &neighbours[1]);
  MPI_Cart_shift(cartcomm, 1, 1, &neighbours[2], &neighbours[3]);
  outbuf = rank;

  for (int i = 0; i < 4; i++) {
    int source = neighbours[i];
    int dest = neighbours[i];
    MPI_Isend(&outbuf, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &reqs[i]);
    MPI_Irecv(&recvmsg[i], 1, MPI_INT, source, 0, MPI_COMM_WORLD, &reqs[i + 4]);
  }
  MPI_Waitall(8, reqs, stats);
  printf("The rank is %d and the outputs are %d %d %d %d\n", rank, recvmsg[0],
         recvmsg[1], recvmsg[2], recvmsg[3]);
  MPI_Finalize();
  return 0;
}

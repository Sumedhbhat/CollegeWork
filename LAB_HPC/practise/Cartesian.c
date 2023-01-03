#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int size, rank;
  int dims[2] = {4, 4}, periods[2] = {0, 0}, reorder = 0, outbuf = rand() % 100,
      inbuf[10] = {MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL,
                   MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL,
                   MPI_PROC_NULL, MPI_PROC_NULL};
  int coords[2] = {0, 0};
  int nbrs[4] = {0, 0, 0, 0};
  MPI_Comm comm;
  MPI_Request reqs[8];
  MPI_Status stats[8];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &comm);
  MPI_Comm_rank(comm, &rank);
  MPI_Cart_coords(comm, rank, 2, coords);
  MPI_Cart_shift(comm, 0, 1, &nbrs[0], &nbrs[1]);
  MPI_Cart_shift(comm, 1, 1, &nbrs[2], &nbrs[3]);
  printf("rank= %d coords= %d %d neighbors(u,d,l,r)= %d %d %d %d\n", rank,
         coords[0], coords[1], nbrs[0], nbrs[1], nbrs[2], nbrs[3]);
  outbuf = rank;
  for (int i = 0; i < 4; i++) {
    int dest = nbrs[i];
    int source = nbrs[i];
    MPI_Isend(&outbuf, 1, MPI_INT, dest, 1, MPI_COMM_WORLD, &reqs[i]);
    MPI_Irecv(&inbuf[i], 1, MPI_INT, source, 1, MPI_COMM_WORLD, &reqs[i + 4]);
  }
  MPI_Waitall(8, reqs, stats);
  printf("rank= %d inbuf(u,d,l,r)= %d %d %d %d\n", rank, inbuf[0], inbuf[1],
         inbuf[2], inbuf[3]);
  MPI_Finalize();
  return 0;
}

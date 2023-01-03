#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
    int size,rank;
    int next,prev;
    int inmsg;
    time_t et,st;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(rank==0) prev=size-1;
    else prev=rank-1;

    if(rank==size-1) next=0;
    else next=rank+1;
    st=clock();
    if(rank%2==0){
        MPI_Send(&rank,1,MPI_INT,next,0,MPI_COMM_WORLD);
        MPI_Recv(&inmsg,1,MPI_INT,prev,1,MPI_COMM_WORLD,&status);
    }else{
        MPI_Recv(&inmsg,1,MPI_INT,prev,0,MPI_COMM_WORLD,&status);
        MPI_Send(&rank,1,MPI_INT,next,1,MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    et=clock();
    if(rank==0)
    printf("Time taken by blocking send and receive is %lf\n",(double)(et-st)/CLOCKS_PER_SEC);
    MPI_Request reqs[2];
    if(rank==0) prev=size-1;
    else prev=rank-1;

    if(rank==size-1) next=0;
    else next=rank+1;
    st=clock();
    MPI_Isend(&rank,1,MPI_INT,next,0,MPI_COMM_WORLD,&reqs[0]);
    MPI_Irecv(&inmsg,1,MPI_INT,prev,0,MPI_COMM_WORLD,&reqs[1]);
    MPI_Barrier(MPI_COMM_WORLD);
    et=clock();
    if(rank==0)
    printf("Time taken by nonblocking send and receive is %lf\n",(double)(et-st)/CLOCKS_PER_SEC);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size,rank;
    int sum,total_sum;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int sendbuf[10],recbuf=0;
    for (int i=0; i<10; i++) {
        sendbuf[i]=rand()%100;
        printf("%d\n",sendbuf[i]);
    }
    MPI_Scatter(&sendbuf,1,MPI_INT,&recbuf,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("the rank is %d and the received variable is %d\n",rank,recbuf);
    for (int i=0; i<10; i++) {
        sendbuf[i]=0;
    }
    MPI_Gather(&recbuf,1,MPI_INT,&sendbuf,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
        for (int i=0; i<10; i++) {
            printf("%d \t",sendbuf[i]);
        }
    printf("\n");
    MPI_Finalize();
    return 0;
}

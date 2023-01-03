#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int size,rank;
    int sum,total_sum;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    srand(rank);
    sum=rand()%100;
    printf("The rank and size of the program are %d and %d %d\n",rank,size,sum);
    MPI_Reduce(&sum,&total_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("The final sum of the number is %d\n",total_sum);
    }
    return 0;
}

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,i;
    printf("Enter the number of terms");
    scanf("%d",&n);
    int fibonacci[n];
    fibonacci[0]=0;
    fibonacci[1]=1;
#pragma omp parallel num_threads(2)
    {
        int thread_num=omp_get_thread_num();
#pragma omp critical
        if(thread_num==0)
        {
            printf("computation happening in thread %d \n",thread_num);
            for (int i=2; i<n; i++) {
                fibonacci[i]=fibonacci[i-2]+fibonacci[i-1];
            }
        }
        else if(thread_num==1){
            printf("computation happening in thread %d \n",thread_num);
            for (int i=0; i<n; i++) {
                printf("%3d",fibonacci[i]);
            }
        }
printf("\n");
    }
    return 0;
}

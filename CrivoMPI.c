#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

int main(){

    MPI_Init(NULL,NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double inicio_proc,fim_proc,tempo_proc;
    long int i;
    long int tamanho, subtamanho;
    tamanho = 100000000;
    subtamanho = (int)tamanho/nprocs;
    int *vetor = NULL;
    long int raiz = floor(sqrt(tamanho));

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==0) {
        inicio_proc = MPI_Wtime();
    }
    vetor = (int *)malloc(tamanho*sizeof(int));

    for(int i=0;i<subtamanho;i++){
        vetor[i] = 1;
    }  

    for(long int i = 2;i<raiz;i++){
        if(vetor[i] == 1){
            for(long int j=i*i;j<subtamanho;j+=i){
                vetor[j] = 0;
            }
        }

    }

    if (rank == 0){
        fim_proc = MPI_Wtime();
        tempo_proc = fim_proc-inicio_proc;
        long int i;
        long int count = 0;
        for(i=2;i<tamanho;i++){
            if(vetor[i]==1){
                count++;
            }
        }
        printf("Tempo de processamento: %f\n",tempo_proc);
        printf("PRIMOSOIIII:%ld",count);

    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

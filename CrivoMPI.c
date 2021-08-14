#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define TAMANHO 100
#define SUBTAMANHO 100

int main(){

    MPI_Init(NULL,NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    double inicio_proc,fim_proc,tempo_proc;
    long int i;
    int *subvetor = NULL;
    int *vetor = NULL;

    if (rank == 0){
        vetor = (int *)malloc(TAMANHO*sizeof(int));
        for(long int i = 0;i<TAMANHO;i++){
            vetor[i] = 1;
            //printf("%d",vetor[i]);
        }

    }
    if (rank==0) {
        inicio_proc = MPI_Wtime();
    }
    subvetor = (int *)malloc(SUBTAMANHO*sizeof(int));
    MPI_Scatter(&vetor,SUBTAMANHO,MPI_INT,&subvetor,SUBTAMANHO,MPI_INT,0,MPI_COMM_WORLD);


    for(long int i = 2;i<SUBTAMANHO;i++){
        if(subvetor[i] == 1){
            for(long int j=i+i;j<SUBTAMANHO;j+=i){
                subvetor[j] = 0;
            }
        }

    }
    /*
    for(long int i = 2;i<SUBTAMANHO;i++){
        printf("%d",subvetor[i]);
    }
*/
    int *resultados = (int *)malloc(TAMANHO*sizeof(int));
    MPI_Gather(&subvetor,1,MPI_INT,&resultados,1,MPI_INT,0,MPI_COMM_WORLD);

   // for(long int i = 2;i<SUBTAMANHO;i++){
   //     printf("%d e %ld",resultados[i],i);
   // }
//

    if (rank == 0){
        fim_proc = MPI_Wtime();
        tempo_proc = fim_proc-inicio_proc;
        long int i;
        long int count = 0;
        for(i=2;i<TAMANHO;i++){
            printf("%d",resultados[i]);
            if(resultados[i]==1){
                count++;
            }
        }
        printf("Tempo de processamento: %f\n %ld",tempo_proc, count);
        printf("PRIMOS:%ld",count);

    }

    MPI_Finalize();
    return 0;
}

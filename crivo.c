#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define TAMANHO 10000000

int main(){
    long int i, j;
    int *table = (int *) malloc(TAMANHO * sizeof(int));
    long int raiz = floor(sqrt(TAMANHO));

    

    //execução serial
    for(i = 2;i <= TAMANHO;i++){
        table[i] = 1;
    }

    double inicio = omp_get_wtime();
    for(i = 2; i <= raiz;i++){
        if(table[i]==1){
            for(j= i+i;j<=TAMANHO;j+=i){
                table[j] = 0;
            }
        }
    }
    double fim = omp_get_wtime();
    double t_serial = fim-inicio;
    printf("Execucao serial: %f\n",t_serial);

    //execução paralela
    for(i = 2;i <= TAMANHO;i++){
        table[i] = 1;
    }

    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        
        for(i = 2; i <= raiz;i++){
            if(table[i]==1){
                #pragma omp for
                for(int j= i+i;j<=TAMANHO;j+=i){
                    table[j] = 0;
                }
            }
        }
    }
    fim = omp_get_wtime();

    double t_paralelo = fim - inicio;
	printf("Execucao paralela: %f\n",t_paralelo);
	double speedup = t_serial/t_paralelo;
	printf("Speedup: %.4f\n", t_serial/t_paralelo);
	printf("Eficiencia: %.4f\n",speedup/4.0);

    free(table);




    return 0;
}

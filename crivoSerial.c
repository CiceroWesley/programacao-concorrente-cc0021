#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define TAMANHO 100000000

int main(){
    long int i, j;
    int *table = (int *) malloc(TAMANHO * sizeof(int));
    long int raiz = floor(sqrt(TAMANHO));
    long int count = 0;



    //execução serial
    for(i = 2;i <= TAMANHO;i++){
        table[i] = 1;
    }

    double inicio = omp_get_wtime();
    for(i = 2; i <= raiz;i++){
        if(table[i]==1){
            for(j= i*i;j<=TAMANHO;j+=i){
                table[j] = 0;
            }
        }
    }
    double fim = omp_get_wtime();
    for(i = 2;i<=TAMANHO;i++){
        if(table[i]==1){
            count++;
        }
    }
    double t_serial = fim-inicio;
    printf("Execucao serial: %f\n",t_serial);
    printf("Primos: %ld",count);

return 0;

}

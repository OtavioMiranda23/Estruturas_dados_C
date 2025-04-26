#include <stdio.h>
#include <stdlib.h>

int maxR (int arr[], int len);
int maxI (int arr[], int len);
int testMaxR();

int main() {
    testMaxR();
}
/* Ao receber v e n >= 1, esta função devolve o valor de
* um elemento máximo do vetor v[0..n-1]. */
int maxR(int arr[], int len) {
    //se a instancia é pequena, resolva diretamente
    if(len == 1) return arr[0];
    //senão
    else {
        //reduza o tamanho do problema
        int newMaxR = maxR(arr, len -1); 
        //aplique o método a instancia menor
        if(newMaxR > arr[len -1]) return newMaxR;
        else return  arr[len -1];
    }
}

// 2.2.1 Escreva uma versão iterativa da função MaxR.
int maxI(int arr[], int len) {
    int max = arr[0];
    for (int i = 0; i < len - 1; i++) {
        if (arr[i+1] > max) max = arr[i+1];
    }
    return max;
}

// 2.2.6 Programa de teste. Escreva um pequeno programa para testar a função
// recursiva MáximoR. O seu programa deve pedir ao usuário que digite uma sequência de
// números ou gerar um vetor aleatório (veja Apêndice I).
// Importante: Para efeito de testes, acrescente ao seu programa uma função auxiliar
// que confira a resposta produzida por MáximoR.
int testMaxR() {
    int len_arr;
    int* ptr;
    printf("Digite o tamanho do seu array:\n");
    scanf("%i", &len_arr);
    ptr = malloc(sizeof(int) * len_arr);
    if (ptr == NULL) {
        printf("Memória indiponível\n");
        return 1;
    }
    for (int i = 0; i < len_arr; i++) {
        printf("Digite o item do seu array:\n");
        scanf("%i", &ptr[i]);            
    }
    printf("O array digitado foi:\n");
    for (int i = 0; i < len_arr; i++) {
        printf("%d", ptr[i]);
    }
    int maxArrR = maxR(ptr, len_arr);
    printf("Número máximo é: %d\n", maxArrR);
    free(ptr);
}
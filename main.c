#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 10
#define TAM_MINHOCA 5
struct Ponto{
    int x;
    int y;
    char simbolo;
};


typedef struct{

    struct Ponto segmentos[5];
} Minhoca;

int inicializar_matriz(char matriz[TAM][TAM]){
   for (int i = 0; i < TAM; i++){
    for (int j =  0; j < TAM; j++){
        matriz[i][j] = ' ';
    }
   }
    return 0; 
}

Minhoca inicializar_minhoca(){
    Minhoca minhoca;
    minhoca.segmentos[0].simbolo = 'C';
    for (int i = 1; i < TAM_MINHOCA - 1; i++){
        minhoca.segmentos[i].simbolo = '*';
    }
    minhoca.segmentos[TAM_MINHOCA - 1].simbolo = '•';
    return minhoca;
}

/*
TODO: 
Inicializar a matriz
Criar o vetor(minhoca)
Lógica de movimento(A cabeca move primeiro e cada parte segue a anterior)
Criar obstaculos aleatorios
JOGADOR ESCOLHE -> Onde a gente começa e QTD movimentos!
Terminar jogo
Contar casas que passaram



*/

int main(){
    char matriz[TAM][TAM];
    inicializar_matriz(matriz);
    Minhoca minhoca = inicializar_minhoca();
    return 0;
}
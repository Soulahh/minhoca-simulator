#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 10
#define TAM_MINHOCA 5
enum{
    UP,
    DOWN,
    LEFT,
    RIGHT
};



typedef struct{
    int x;
    int y;
    char simbolo;
} Ponto;


typedef struct{

    Ponto segmentos[5];
} Minhoca;

void inicializar_matriz(char matriz[TAM][TAM]){
   for (int i = 0; i < TAM; i++){
    for (int j =  0; j < TAM; j++){
        matriz[i][j] = ' ';
    }
   }
}

Minhoca inicializar_minhoca(){
    Minhoca minhoca;
    minhoca.segmentos[0].simbolo = 'C';
    for (int i = 1; i < TAM_MINHOCA - 1; i++){
        minhoca.segmentos[i].simbolo = '*';
    }
    minhoca.segmentos[TAM_MINHOCA - 1].simbolo = '.';
    return minhoca;
}
int checar_se_casa_ta_limpa(int x, int y, char matriz[TAM][TAM]){
    if((x < 0 || x >= TAM) || (y < 0 || y >= TAM))
        return 0;
    if(matriz[x][y] == ' ')
        return 1;
    return 0;
}


void inserir_minhoca_no_mapa(Minhoca *minhoca, char matriz[TAM][TAM], Ponto ponto){
    matriz[ponto.x][ponto.y] = minhoca->segmentos[0].simbolo; //insere a cabeça da minhoca na matriz
    int x = ponto.x;
    int y = ponto.y;
    for(int i = 1;i<TAM_MINHOCA;i++){

            minhoca->segmentos[i-1].x = x;
            minhoca->segmentos[i-1].y = y;
            if (checar_se_casa_ta_limpa(x+1, y, matriz)) {
                matriz[x+1][y] = minhoca->segmentos[i].simbolo;
                minhoca->segmentos[i].x = x+1;
                minhoca->segmentos[i].y = y;
                x++;
            } else if (checar_se_casa_ta_limpa(x-1, y, matriz)) {
                matriz[x-1][y] = minhoca->segmentos[i].simbolo;
                minhoca->segmentos[i].x = x-1;
                minhoca->segmentos[i].y = y;
                x--;
            } else if (checar_se_casa_ta_limpa(x, y+1, matriz)) {
                matriz[x][y+1] = minhoca->segmentos[i].simbolo;
                minhoca->segmentos[i].x = x;
                minhoca->segmentos[i].y = y+1;
                y++;
            } else if (checar_se_casa_ta_limpa(x, y-1, matriz)) {
                matriz[x][y-1] = minhoca->segmentos[i].simbolo;
                minhoca->segmentos[i].x = x;
                minhoca->segmentos[i].y = y-1;
                y--;
            }

    }
}

void mover_cima(Minhoca *minhoca, char matriz[TAM][TAM]){
    for(int i = TAM_MINHOCA-1; i > 0; i--){;
        (*minhoca).segmentos[i].x = (*minhoca).segmentos[i-1].x;
        (*minhoca).segmentos[i].y = (*minhoca).segmentos[i-1].y;
    }
    (*minhoca).segmentos[0].x--;
}

void mover_baixo(Minhoca *minhoca, char matriz[TAM][TAM]){
    for(int i = TAM_MINHOCA-1; i > 0; i--){;
        (*minhoca).segmentos[i].x = (*minhoca).segmentos[i-1].x;
        (*minhoca).segmentos[i].y = (*minhoca).segmentos[i-1].y;
    }
    (*minhoca).segmentos[0].x++;
}

void mover_esquerda(Minhoca *minhoca, char matriz[TAM][TAM]){
    for(int i = 4; i > 0; i--){;
        (*minhoca).segmentos[i].x = (*minhoca).segmentos[i-1].x;
        (*minhoca).segmentos[i].y = (*minhoca).segmentos[i-1].y;
    }
    (*minhoca).segmentos[0].y--;
}

void mover_direita(Minhoca *minhoca, char matriz[TAM][TAM]){
    for(int i = 4; i > 0; i--){;
        (*minhoca).segmentos[i].x = (*minhoca).segmentos[i-1].x;
        (*minhoca).segmentos[i].y = (*minhoca).segmentos[i-1].y;
    }
    (*minhoca).segmentos[0].y++;
}


void mover_minhoca(Minhoca *minhoca, char matriz[TAM][TAM],int direcao){
    switch(direcao){
        case UP:
            mover_cima(minhoca, matriz);
            break;
        case DOWN:
            mover_baixo(minhoca, matriz);
            break;
        case LEFT:
            mover_esquerda(minhoca, matriz);
            break;
        default:
            mover_direita(minhoca, matriz);
            break;
    }
}

void imprimir_matriz(char matriz[TAM][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

/*
TODO: 
Inicializar a matriz
Criar o vetor(minhoca)
Inserir a minhoca no mapa (primeiro arbitrariamente)
Lógica de movimento(A cabeca move primeiro e cada parte segue a anterior)
Criar obstaculos aleatorios
JOGADOR ESCOLHE -> Onde a gente começa e QTD movimentos!
Terminar jogo
Contar casas que passaram



*/

int main(){
    Ponto ponto;
    ponto.x = 0;
    ponto.y = 0;
    char matriz[TAM][TAM];
    inicializar_matriz(matriz);
    Minhoca minhoca = inicializar_minhoca();

    do{
        printf("Insira o ponto inicial da minhoca: (formato: 'x y'): ");
        scanf("%d %d", ponto.x,ponto.y);
    } while((ponto.x < 0 || ponto.x > 10) || (ponto.y < 0 || ponto.y > 10));


    inserir_minhoca_no_mapa(&minhoca, matriz, ponto);
    imprimir_matriz(matriz);
    return 0;
}
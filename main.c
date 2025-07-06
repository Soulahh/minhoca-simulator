#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

void atualizar_mapa_com_minhoca(Minhoca *minhoca, char matriz[TAM][TAM]) {

    for (int i = 0; i < TAM_MINHOCA; i++) {
        int x = minhoca->segmentos[i].x;
        int y = minhoca->segmentos[i].y;
        matriz[x][y] = minhoca->segmentos[i].simbolo;
    }
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

void atualizar_simbolos(Minhoca *minhoca){
    minhoca->segmentos[0].simbolo = 'C';
    for(int i = 1; i < TAM_MINHOCA - 1; i++){
        minhoca->segmentos[i].simbolo = '*';
    }
    minhoca->segmentos[TAM_MINHOCA-1].simbolo = '.';
}

int mover_minhoca(Minhoca *minhoca, char matriz[TAM][TAM], int direcao, int visitadas[TAM][TAM], int *casas_visitadas){

    int nova_x = minhoca->segmentos[0].x;
    int nova_y = minhoca->segmentos[0].y;

    switch(direcao){
        case UP:    nova_x--; break;
        case DOWN:  nova_x++; break;
        case LEFT:  nova_y--; break;
        case RIGHT: nova_y++; break;
        default:    return 0;
    }
    
    if(!checar_se_casa_ta_limpa(nova_x,nova_y,matriz))
        return 0;
    
    for(int i = TAM_MINHOCA - 1; i > 0; i--){
        minhoca->segmentos[i].x = minhoca->segmentos[i-1].x;
        minhoca->segmentos[i].y = minhoca->segmentos[i-1].y;
    }

    minhoca->segmentos[0].x = nova_x;
    minhoca->segmentos[0].y = nova_y;
    if (!visitadas[nova_x][nova_y]){
        visitadas[nova_x][nova_y] = 1;
        (*casas_visitadas)++;
    }
    atualizar_simbolos(minhoca);
    return 1;
}

void imprimir_matriz(char matriz[TAM][TAM]){
    printf("\n\n\n");
    printf("\n--------------------------------------------------\n");
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("| %c |", matriz[i][j]);
        }
        printf("\n--------------------------------------------------\n");
    }
    printf("\n");
}

void adicionar_obstaculos(int qtd, char matriz[TAM][TAM], Ponto obstaculos[qtd]){
    for(int i = 0; i < qtd; i++){
        matriz[obstaculos[i].x][obstaculos[i].y] = '#';
    }
}

void gerar_obstaculos(int qtd_obstaculos, char matriz[TAM][TAM], Ponto obstaculos[qtd_obstaculos]){
    int cont = 0;
    while(cont < qtd_obstaculos){
        int x = rand() % TAM;
        int y = rand() % TAM;

        if(matriz[x][y] == ' '){
            obstaculos[cont].x = x;
            obstaculos[cont].y = y;
            obstaculos[cont].simbolo = '#';
            cont++;
        }
    }
}

int tentar_mover_aleatorio(Minhoca *minhoca, char matriz[TAM][TAM], int visitadas[TAM][TAM], int *casas_visitadas) {
    int direcoes[4] = {UP, DOWN, LEFT, RIGHT};

    // Embaralhar o array de direções
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = direcoes[i];
        direcoes[i] = direcoes[j];
        direcoes[j] = temp;
    }

    // Tentar mover em cada direção, na ordem embaralhada
    for (int i = 0; i < 4; i++) {
        if (mover_minhoca(minhoca, matriz, direcoes[i], visitadas, casas_visitadas)) {
            return 1; // Movimento feito com sucesso
        }
    }

    return 0; // Não conseguiu mover para lugar nenhum
}

void terminar_jogo(int *casas_visitadas, int qtd_obstaculos){
    int casas_nao_visitadas = (TAM * TAM) - qtd_obstaculos - (*casas_visitadas);
    printf("\nO numero de casas visitadas foi: %d\n", *casas_visitadas);
    printf("O numero de casas nao visitadas foi: %d\n",casas_nao_visitadas);
    exit(0);
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
    srand(time(NULL));
    Ponto ponto;
    int quantidade_obstaculos, quantidade_movimentos;
    ponto.x = 0;
    ponto.y = 0;
    char matriz[TAM][TAM];
    int visitadas[TAM][TAM] = {0};
    int casas_visitadas = 0;
    inicializar_matriz(matriz);
    Minhoca minhoca = inicializar_minhoca();


    printf("\nDefina a quantidade de obstaculos: ");
    do{
    scanf("%d", &quantidade_obstaculos);
    if (quantidade_obstaculos > ((TAM * TAM) - TAM_MINHOCA) || quantidade_obstaculos < 0)
        printf("\nQuantidade invalida. Tente novamente: ");
    }while(quantidade_obstaculos > ((TAM * TAM) - TAM_MINHOCA) || quantidade_obstaculos < 0);

    Ponto obstaculos[quantidade_obstaculos];

    do{
        printf("Insira o ponto inicial da minhoca: (formato: 'x y'): ");
        scanf("%d %d", &ponto.x, &ponto.y);
        if ((ponto.x < 0 || ponto.x >= TAM) || (ponto.y < 0 || ponto.y >= TAM))
            printf("\nPosicao invalida. Tente novamente: ");
    } while((ponto.x < 0 || ponto.x >= TAM) || (ponto.y < 0 || ponto.y >= TAM));

    do {
        printf("\nInsira a quantidade de movimentos: ");
        scanf("%d", &quantidade_movimentos);
    } while(quantidade_movimentos <= 0);

    inserir_minhoca_no_mapa(&minhoca, matriz, ponto);
    visitadas[minhoca.segmentos[0].x][minhoca.segmentos[0].y] = 1;
    casas_visitadas = 1;
    printf("%d %d\n", minhoca.segmentos[0].x, minhoca.segmentos[0].y);

    gerar_obstaculos(quantidade_obstaculos, matriz, obstaculos);
    adicionar_obstaculos(quantidade_obstaculos, matriz, obstaculos);

    for (int i = 0; i < quantidade_movimentos; i++){
        Ponto cauda_antiga = minhoca.segmentos[TAM_MINHOCA - 1];
        if (!tentar_mover_aleatorio(&minhoca,matriz,visitadas,&casas_visitadas)){
            printf("\nNenhum movimento possivel!\n");
            terminar_jogo(&casas_visitadas, quantidade_obstaculos);
        }
        inicializar_matriz(matriz);
        adicionar_obstaculos(quantidade_obstaculos, matriz, obstaculos);
        atualizar_mapa_com_minhoca(&minhoca, matriz);
        fflush(stdin);
        printf("Pressione ENTER para ver o próximo movimento!\n");
        getchar();
        system("cls");
        imprimir_matriz(matriz);
    }
    terminar_jogo(&casas_visitadas, quantidade_obstaculos);
    return 0;
}
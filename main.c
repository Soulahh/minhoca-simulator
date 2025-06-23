#include <stdio.h>
#include <string.h>
#define TAM 10
struct Ponto{
    int x;
    int y;
};


int inicializar_matriz(char matriz[TAM][TAM]){
   for (int i = 0; i < TAM; i++){
    for (int j =  0; j < TAM; j++){
        matriz[i][j] = ' ';
    }
   }
    return 0; 
}


int main(){
    char matriz[TAM][TAM];

    return 0;
}
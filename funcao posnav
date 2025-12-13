#include <stdio.h>
#include <stdlib.h>

int N = 10;

void posnav(char tabuleiro[N][N], int linha, int coluna, int tamanho, char direcao) {
   
    if (direcao == 'H') {
        if (coluna + tamanho > N) {
            printf("Navio nao cabe nessa posicao!\n");
            return;
        }
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] == 'S') {
                printf("Espaco ja ocupado!\n");
                return;
            }
        }
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha][coluna + i] = 'S';
        }
    } 
    else if (direcao == 'V') {
        if (linha + tamanho > N) {
            printf("Navio nao cabe nessa posicao!\n");
            return;
        }
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] == 'S') {
                printf("Espaco ja ocupado!\n");
                return;
            }
        }
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna] = 'S';
        }
    } 
    else {
        printf("Direcao invalida!\n");
        return;
    }

    printf("Navio posicionado com sucesso!\n");
}

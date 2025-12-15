int atacar(char tabuleiro[N][N], int linha, int coluna) {
    if(tabuleiro[linha][coluna] == 'N') { // verifica se há um navio
        tabuleiro[linha][coluna] = 'O';
        printf("Acertou!\n");
        return 0;
    } else if(tabuleiro[linha][coluna] == '~') { // verifica se é água
        tabuleiro[linha][coluna] = 'X';
        printf("Errou!\n");
        return 0;
    } else {
        printf("Erro! Posicao invalida!\n"); // coordenada invalida ou ja ocupada
        return -1;
    }
}

//falta implementar a funcao pra dizer se o navio afundou apos o ataque
}

int atacar(char tabuleiro[N][N], int linha, int coluna) {
    if(tabuleiro[linha][coluna]=='S') {
        tabuleiro[linha][coluna]='O';
        printf("Acertou!\n");
        return 1;
    } else if(tabuleiro[linha][coluna]=='.') {
        tabuleiro[linha][coluna]='X';
        printf("Agua!\n");
        return 0;
    } else {
        printf("Ja atacado antes!\n");
        return 0;
    }
}

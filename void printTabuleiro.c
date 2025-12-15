void printTabuleiro(char tabuleiro[N][N], int spot) {
    printf("\n");
    for(int j=0; j<N ; j++)
        printf("%c", 'A'+ j);
    printf("\n");

    for(int i=0; i<N; i++) {
        printf("d", i + 1);
        for(int j=0; j<N; j++) {
            if(tabuleiro[i][j] == 'N' && !spot) // se ambos forem verdadeiros
                printf("~");
            else printf("%c", tabuleiro[i][j]);
        }
        printf("\n");
    }
}
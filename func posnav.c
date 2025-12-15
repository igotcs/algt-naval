int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna) {
    if(direcao == 'H') || direcao == 'h'){ // compara coluna pois o barco é posicionado horizontalmente
        if(coluna+tamanho > N)
            return 1;  // se nao couber no tabuleiro

        for(int i=0; i<tamanho; i++)
            if(tabuleiro[linha][coluna+i] == 'N')
                return 1; // se colidir com outro navio

        for(int i=0; i<tamanho; i++)
            tabuleiro[linha][coluna+i] = 'N';
                return 0; // posicionado com sucesso
    }
    else if (direcao == 'V') || direcao == 'v'){
        if(linha+tamanho > N)
            return 1; // se nao couber no tabuleiro

        for(int i=0; i<tamanho; i++)
            if(tabuleiro[linha+i][coluna] == 'N')
                return 1; // se colidir com outro navio

        for(int i=0; i<tamanho; i++)
            tabuleiro[linha+i][coluna] = 'N';
             return 0; // posicionado com sucesso
    }
    return 1; //se nao for H nem V.
}
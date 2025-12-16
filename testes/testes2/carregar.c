int carregarJogo(char nome_arq[] ,
                 char tabuleiro1[10][10], char tabuleiro2[10][10],
                 char nome1[], size_t nome1_size,
                 char nome2[], size_t nome2_size,
                 int jogadorAtual, int rodadas,
                 int acertos1, int acertos2, int erros1, int erros2)
{
    FILE *p 
    p = fopen(nome_arq, "r");
    if (!p) {
      printf("ERRO AO CARREGAR O JOGO OU NAO EXISTE JOGO SALVO");
      return 0;}
  
    fscanf(p,"%s", nome1);
    fscanf(p,"%s",nome2);
    fscanf(p,"%d %d %d %d %d %d", jogadorAtual, rodadas, acertos1, acertos2, erros1, erros2);
   
    /* lê tabuleiro1 */
    for (int i = 0; i < 10; ++i) {
        char line[10];
        if ((int)strlen(line) < 10) { fclose(p); return 0; }
        for (int j = 0; j < 10; ++j) tab1[i][j] = line[j];
    }

    /* lê tabuleiro2 */
    for (int i = 0; i < 10; ++i) {
        char line[10];
        if ((int)strlen(line) < 10) { fclose(p); return 0; }
        for (int j = 0; j < 10; ++j) tab2[i][j] = line[j];
    }

    fclose(p);
    return 1;
}

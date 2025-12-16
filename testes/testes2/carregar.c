int carregarJogo(char nome_arq[] ,
                 char tabuleiro1[10][10], char tabuleiro2[10][10],
                 char nome1[], size_t nome1_size,
                 char nome2[], size_t nome2_size,
                 int *jogadorAtual, int *rodadas,
                 int *acertos1, int *acertos2, int *erros1, int *erros2)
{
    FILE *p 
    p = fopen(nome_arq, "r");
    if (!p) {
      printf("ERRO AO CARREGAR O JOGO OU NAO EXISTE JOGO SALVO");
      return 0;}
  
    /* remove '\n' finais */
    nome1[strcspn(nome1, "\r\n")] = '\0';
    nome2[strcspn(nome2, "\r\n")] = '\0';

    /* lê os inteiros de estado */
    if (fscanf(p, "%d %d %d %d %d %d\n",
               jogadorAtual, rodadas, acertos1, acertos2, erros1, erros2) != 6) {
        fclose(fp);
        return 0;
    }

    /* lê tabuleiro1 */
    for (int i = 0; i < 10; ++i) {
        char line[32];
        if (!fgets(line, sizeof line, p)) { fclose(p); return 0; }
        /* valida e copia até 10 chars */
        if ((int)strlen(line) < 10) { fclose(p); return 0; }
        for (int j = 0; j < 10; ++j) tab1[i][j] = line[j];
    }

    /* lê tabuleiro2 */
    for (int i = 0; i < 10; ++i) {
        char line[32];
        if (!fgets(line, sizeof line, p)) { fclose(p); return 0; }
        if ((int)strlen(line) < 10) { fclose(p); return 0; }
        for (int j = 0; j < 10; ++j) tab2[i][j] = line[j];
    }

    fclose(p);
    return 1;
}

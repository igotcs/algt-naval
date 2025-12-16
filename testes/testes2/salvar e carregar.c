int salvarJogo( char nome_arq,
               char tab1[10][10], char tab2[10][10],
               char nome1, char nome2,
               int jogadorAtual, int rodadas,
               int acertos1, int acertos2, int erros1, int erros2)
{
    FILE *p;
    p = fopen(filename, "w");
    if (!p) {
      printf("ERRO AO SALVAR O ARQUIVO");
      return 0;}

    /* nomes */
    fprintf(p, "%s\n", nome1);
    fprintf(p, "%s\n", nome2);

    /* estado geral */
    fprintf(p, "%d %d %d %d %d %d\n", jogadorAtual, rodadas, acertos1, acertos2, erros1, erros2);

    /* tabuleiro1: 10 linhas de 10 chars (sem espaços) */
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            fputc(tab1[i][j], p);
        }
        fputc('\n', p);
    }

    /* tabuleiro2 */
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            fputc(tab2[i][j], p);
        }
        fputc('\n', p);
    }

    fclose(p);
    return 1;
}


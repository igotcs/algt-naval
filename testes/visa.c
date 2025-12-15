#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int N = 10;

// ---------- PROTÓTIPOS ----------
void menu();
void inicializarTabuleiro(char tabuleiro[N][N]);
void imprimirTabuleiro(char tabuleiro[N][N], int revelarNavios);
int posicionarNavio(char tabuleiro[N][N], int tamanho, char letra, char direcao, int linha, int coluna);
int atacar(char tabuleiro[N][N], int linha, int coluna);
void salvarResultados(char nome1[], char nome2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas);

// Estrutura para os navios
struct n {
    char nav[50];
    int tamanho;
    char letra;
};

int main() {
    char tabuleiro1[N][N], tabuleiro2[N][N];
    char nome1[50], nome2[50];
    int opt = 0;

    struct n navio[3];
    strcpy(navio[0].nav, "Cruzeiro do Kaka");
    strcpy(navio[1].nav, "Charles");
    strcpy(navio[2].nav, "Bote");
    navio[0].tamanho = 4;
    navio[1].tamanho = 3;
    navio[2].tamanho = 2;
    navio[0].letra = 'K';
    navio[1].letra = 'C';
    navio[2].letra = 'B';

    char ent[128];

    while (opt != 4) {
        menu();
        printf("ESCOLHA UMA OPÇAO: ");
        if (!fgets(ent, sizeof ent, stdin)) break;
        if (sscanf(ent, "%d", &opt) != 1) {
            printf("OPÇAO INVALIDA!\n");
            continue;
        }

        if (opt == 1) {
            printf("Nome jogador 1: ");
            if (!fgets(nome1, sizeof nome1, stdin)) return 0;
            nome1[strcspn(nome1, "\n")] = '\0';
            printf("Nome jogador 2: ");
            if (!fgets(nome2, sizeof nome2, stdin)) return 0;
            nome2[strcspn(nome2, "\n")] = '\0';

            inicializarTabuleiro(tabuleiro1);
            inicializarTabuleiro(tabuleiro2);

            int linha;
            char c, d;

            // POSICIONAMENTO JOGADOR 1
            for (int i = 0; i < 3; i++) {
                int colocado = 0;
                while (!colocado) {
                    printf("=== %s, POSICIONE SEUS NAVIOS ===\n", nome1);
                    imprimirTabuleiro(tabuleiro1, 1);
                    printf("\nNavio: %s (Tamanho %d)\n", navio[i].nav, navio[i].tamanho);
                    printf("Digite Linha (1-10), Coluna (A-J) e Direcao (H/V): ");
                    if (!fgets(ent, sizeof ent, stdin)) return 0;
                    if (sscanf(ent, "%d %c %c", &linha, &c, &d) != 3) {
                        printf("ENTRADA INVALIDA!\nEXEMPLO DE ENTRADA: 5 B H\n");
                        continue;
                    }
                    c = toupper((unsigned char)c);
                    d = toupper((unsigned char)d);
                    if (linha < 1 || linha > 10 || c < 'A' || c > 'J' || (d != 'H' && d != 'V')) {
                        printf("VALORES FORA DO INTERVALO PERMITIDO!\nLinha 1-10, Coluna A-J, Direcao H ou V.\n");
                        continue;
                    }
                    if (!posicionarNavio(tabuleiro1, navio[i].tamanho, navio[i].letra, d, linha - 1, c - 'A')) {
                        printf("NAO FOI POSSIVEL POSICIONAR O NAVIO NESSA POSICAO (sobreposicao ou fora do tabuleiro)\n");
                        continue;
                    }
                    colocado = 1;
                }
            }

            // POSICIONAMENTO JOGADOR 2
            for (int i = 0; i < 3; i++) {
                int colocado = 0;
                while (!colocado) {
                    printf("=== %s, POSICIONE SEUS NAVIOS ===\n", nome2);
                    imprimirTabuleiro(tabuleiro2, 1);
                    printf("\nNavio: %s (Tamanho %d)\n", navio[i].nav, navio[i].tamanho);
                    printf("Digite Linha (1-10), Coluna (A-J) e Direcao (H/V): ");
                    if (!fgets(ent, sizeof ent, stdin)) return 0;
                    if (sscanf(ent, "%d %c %c", &linha, &c, &d) != 3) {
                        printf("ENTRADA INVALIDA!\n EXEMPLO DE ENTRADA: 5 B H\n");
                        continue;
                    }
                    c = toupper((unsigned char)c);
                    d = toupper((unsigned char)d);
                    if (linha < 1 || linha > 10 || c < 'A' || c > 'J' || (d != 'H' && d != 'V')) {
                        printf("VALORES FORA DO INTERVALO PERMITIDO!\nLinha 1-10, Coluna A-J, Direcao H ou V.\n");
                        continue;
                    }
                    if (!posicionarNavio(tabuleiro2, navio[i].tamanho, navio[i].letra, d, linha - 1, c - 'A')) {
                        printf("NAO FOI POSSIVEL POSICIONAR O NAVIO NESSA POSICAO (sobreposicao ou fora do tabuleiro).\n");
                        continue;
                    }
                    colocado = 1;
                }
            }

            // LOOP DE JOGO
            int jogadorAtual = 1;
            int rodadas = 0, acertos1 = 0, acertos2 = 0, erros1 = 0, erros2 = 0;

            while (1) {
                int l_ataque;
                char c_ataque;
                int resp = -1;
                if (jogadorAtual == 1) {
                    printf("\n--- VEZ DE %s ---\n", nome1);
                    imprimirTabuleiro(tabuleiro2, 0);
                    do {
                        printf("Alvo (Ex: 5 B): ");
                        if (!fgets(ent, sizeof ent, stdin)) return 0;
                        if (sscanf(ent, "%d %c", &l_ataque, &c_ataque) != 2) {
                            printf("ENTRADA INVALIDA!\nEXEMPLO: 5 B\n");
                            continue;
                        }
                        c_ataque = toupper((unsigned char)c_ataque);
                        if (l_ataque < 1 || l_ataque > 10 || c_ataque < 'A' || c_ataque > 'J') {
                            printf("COORDENADA FORA DO INTERVALO PERMITIDO!\n");
                            continue;
                        }
                       resp = atacar(tabuleiro2, l_ataque - 1, c_ataque - 'A');
                    } while (resp == -1);
                    if (resp)
                        acertos1++; 
                    else 
                        erros1++;
                    jogadorAtual = 2;
                } else {
                    printf("\n--- VEZ DE %s ---\n", nome2);
                    imprimirTabuleiro(tabuleiro1, 0);
                    resp = -1;
                    do {
                        printf("Alvo (Ex: 5 B): ");
                        if (!fgets(ent, sizeof ent, stdin)) return 0;
                        if (sscanf(ent, "%d %c", &l_ataque, &c_ataque) != 2) {
                            printf("ENTRADA INVALIDA!\nEXEMPLO: 5 B\n");
                            continue;
                        }
                        c_ataque = toupper((unsigned char)c_ataque);
                        if (l_ataque < 1 || l_ataque > 10 || c_ataque < 'A' || c_ataque > 'J') {
                            printf("COORDENADA FORA DO INTERVALO PERMITIDO!\n");
                            continue;
                        }
                       resp = atacar(tabuleiro1, l_ataque - 1, c_ataque - 'A');
                    } while (resp== -1);
                    if (resp) 
                        acertos2++; 
                    else 
                        erros2++;
                    jogadorAtual = 1;
                }

                rodadas++;
                // Verifica fim
                int fim1 = 1, fim2 = 1;
                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++) {
                        if (tabuleiro1[i][j] == 'K' || tabuleiro1[i][j] == 'C' || tabuleiro1[i][j] == 'B') fim1 = 0;
                        if (tabuleiro2[i][j] == 'K' || tabuleiro2[i][j] == 'C' || tabuleiro2[i][j] == 'B') fim2 = 0;
                    }
                if (fim1 || fim2) break;

                printf("\nPressione Enter para passar a vez...");
                if (!fgets(buf, sizeof buf, stdin)) break;
            }

            printf("\n=== JOGO ENCERRADO ===\n");
            if (acertos1 > acertos2) printf("Vencedor: %s\n", nome1);
            else if (acertos2 > acertos1) printf("Vencedor: %s\n", nome2);
            else printf("Empate!\n");

            salvarResultados(nome1, nome2, acertos1, acertos2, erros1, erros2, rodadas);
            printf("\nPressione "ENTER" para voltar ao menu...");
            if (!fgets(buf, sizeof buf, stdin)) break;

        } else if (opt == 3) {
            system("clear");
            printf("[ INSTRUÇÕES ]\n");
            printf("o Objetivo do Jogo: Afundar todos os navios inimigos\n");
            printf("o Cada jogador começa o jogo posicionando seus navios em um tabuleiro com 10x10,\n"
                   "no qual as colunas sao letras (de A a J), e as linhas sao numeros (de 1 a 10).\n");
            printf("o Os tipos de embarcacao sao os seguintes:\n"
                   "1. Cruzeiro do Kaka – 4 celulas\n"
                   "2. Charles – 3 celulas\n"
                   "3. Bote – 2 celulas\n");
            printf("o Duas embarcacoes nao podem ocupar a mesma celula\n");
            printf("o Uma embarcacao nao pode ser posicionada fora do tabuleiro\n");
            printf("o Após o inicio do jogo, cada jogador terá acesso ao tabuleiro organizado pelo adversario,\n"
                   "com os navios escondidos. Os jogadores se revezam em turnos para atirar nos navios adversarios\n");
            printf("o Após cada tiro a tela mostrara uma resposta:\n"
                   "1. Agua\n"
                   "2. Acertou\n");
            printf("o Quando um navio for afundado, aparecera 'Afundou' na tela\n\n\n");
            printf("Pressione Enter para voltar ao menu...");
            if (!fgets(buf, sizeof buf, stdin)) break;
        }
    }
    return 0;
}

// ---------- biblioteca funções ----------

void inicializarTabuleiro(char tabuleiro[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tabuleiro[i][j] = '~';
}

void imprimirTabuleiro(char tabuleiro[N][N], int revelarNavios) {
    printf("\n    ");
    for (int j = 0; j < N; j++) printf("%c ", 'A' + j);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < N; j++) {
            if ((tabuleiro[i][j] == 'K' || tabuleiro[i][j] == 'C' || tabuleiro[i][j] == 'B') && !revelarNavios)
                printf("~ ");
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

/* Retorna 1 se posicionou com sucesso, 0 caso contrario */
int posicionarNavio(char tabuleiro[N][N], int tamanho, char letra, char direcao, int linha, int coluna) {
    // valida indices basicos
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N) return 0;

    if (direcao == 'H') {
        if (coluna + tamanho > N) return 0; // extrapola borda
        // verifica sobreposicao
        for (int i = 0; i < tamanho; i++)
            if (tabuleiro[linha][coluna + i] != '~') return 0;
        // escreve
        for (int i = 0; i < tamanho; i++)
            tabuleiro[linha][coluna + i] = letra;
    } else { // vertical
        if (linha + tamanho > N) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tabuleiro[linha + i][coluna] != '~') return 0;
        for (int i = 0; i < tamanho; i++)
            tabuleiro[linha + i][coluna] = letra;
    }
    return 1;
}

int atacar(char tabuleiro[N][N], int linha, int coluna) {
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N)
        return 0; // fora do tabuleiro tratamos como água

    char cell = tabuleiro[linha][coluna];

    /* já atacado */
    if (cell == 'X' || cell == 'O') {
        printf("Essa celula ja foi atacada. Escolha outra.\n");
        return -1;
    }

    /* agua */
    if (cell == '~') {
        tabuleiro[linha][coluna] = 'X';
        printf("\nAGUA!\n");
        return 0;
    }

    /* se for letra de navio */
    if (cell == 'K' || cell == 'C' || cell == 'B') {
        char letra = cell;
        tabuleiro[linha][coluna] = 'O';
        printf("\nACERTOU!\n");

        /* verifica se ainda existe alguma célula com a mesma letra */
        int restante = 0;
        for (int i = 0; i < N && !restante; i++) {
            for (int j = 0; j < N; j++) {
                if (tabuleiro[i][j] == letra) { restante = 1; break; }
            }
        }

        if (!restante) {
            const char *nome;
            switch (letra) {
                case 'K': nome = "Cruzeiro do Kaka"; break;
                case 'C': nome = "Charles"; break;
                case 'B': nome = "Bote"; break;
                default:  nome = "Navio"; break;
            }
            printf("AFUNDOU: %s\n", nome);
        }
        return 1;
    }

    /* caso inesperado: tratar como água */
    tabuleiro[linha][coluna] = 'X';
    printf("\nAGUA!\n");
    return 0;
}


void salvarResultados(char nome1[], char nome2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas) {
    FILE *fp = fopen("resultado.txt", "w");
    if (!fp) return;
    fprintf(fp, "Relatorio Final\n%s: %d acertos\n%s: %d acertos\nRodadas: %d\n", nome1, acertos1, nome2, acertos2, rodadas);
    fclose(fp);
}

void menu() {
     printf("0 0 0   0 0 0 0  0 0 0 0  0 0 0 0  0        0     0  0 0 0 0\n" 
           "0    0  0     0     0     0     0  0        0     0  0     0\n"
           "0 0 0   0 0 0 0     0     0 0 0 0  0        0 0 0 0  0 0 0 0\n" 
           "0    0  0     0     0     0     0  0        0     0  0     0\n"
           "0 0 0   0     0     0     0     0  0 0 0 0  0     0  0     0\n");
    printf("         0     0  0 0 0 0  0       0  0 0 0 0  0\n" 
           "         0 0   0  0     0   0     0   0     0  0\n"
           "         0  0  0  0 0 0 0    0   0    0 0 0 0  0\n" 
           "         0   0 0  0     0     0 0     0     0  0\n"     
           "         0     0  0     0      0      0     0  0 0 0 0\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 0 00 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" 
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~ 00 00 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~ 000 00 0 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" 
           "~~~~~~~~~~~~~~~~~~~~~~~~~ 0000 00 00 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "~~~~~~~~~~~~~~~~~~~~~~~ 000000 00 000 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"  
           "~~~~~~~~~~~~~~~~~~~~~~ 0000000 00 0000 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n"
           "~~~~~~~~~~~~~~ 0000000000000000000000000000 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" 
           "~~~~~~~~~~~~~~~~ 000000000000000000000000 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1 - NOVO JOGO\n");
    printf("2 - CONTINUAR JOGO\n");
    printf("3 - INTRUÇÕES\n");
    printf("4 - SAIR\n");
}

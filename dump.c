#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10 // Definindo N como constante

void menu();
void innitTabuleiro(char tabuleiro[N][N]);
void printTabuleiro(char tabuleiro[N][N], int spot);
int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna);
int atacar(char tabuleiro[N][N], int linha, int coluna);

int main() {
    char tabuleiro1[N][N], tabuleiro2[N][N];
    char jogador1[50], jogador2[50];
    int opt = 0;

    menu();
    printf("Escolha uma opcao: ");
    scanf("%d", &opt);

    if (opt == 1) {
        printf("Insira o nome do Jogador 1: ");
        scanf("%s", jogador1);
        printf("Insira o nome do Jogador 2: ");
        scanf("%s", jogador2);

        innitTabuleiro(tabuleiro1);
        innitTabuleiro(tabuleiro2);

        char Navios[3][30] = {"Cruzeiro do Kaka", "Charles", "Bote"};
        int tamanhoN[3] = {4, 3, 2};
        int linha, res;
        char cl, dir;

        // POSICIONAMENTO JOGADOR 1
        for (int i = 0; i < 3; i++) {
            do {
                system("clear || cls");
                printf("%s, Posicione seu navio: %s (%d celulas)\n", jogador1, Navios[i], tamanhoN[i]);
                printTabuleiro(tabuleiro1, 1);
                printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V): ");
                scanf("%d %c %c", &linha, &cl, &dir);

                cl = toupper(cl);
                dir = toupper(dir);

                res = posnav(tabuleiro1, tamanhoN[i], dir, linha - 1, cl - 'A');
                if (res == 1) printf("Erro ao posicionar! Tente novamente.\n");
            } while (res == 1);
        }

        // POSICIONAMENTO JOGADOR 2
        for (int i = 0; i < 3; i++) {
            do {
                system("clear || cls");
                printf("%s, Posicione seu navio: %s (%d celulas)\n", jogador2, Navios[i], tamanhoN[i]);
                printTabuleiro(tabuleiro2, 1);
                printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V): ");
                scanf("%d %c %c", &linha, &cl, &dir);

                cl = toupper(cl);
                dir = toupper(dir);

                res = posnav(tabuleiro2, tamanhoN[i], dir, linha - 1, cl - 'A');
                if (res == 1) printf("Erro ao posicionar! Tente novamente.\n");
            } while (res == 1);
        }

        // GAME ENGINE
        int jogadorAtual = 1;
        int rodadas = 0, acertos1 = 0, acertos2 = 0;

        while (1) {
            system("clear || cls");
            int l_atk, resultado;
            char c_atk;

            if (jogadorAtual == 1) {
                printf("\n--- TURNO DE %s ---\n", jogador1);
                printTabuleiro(tabuleiro2, 0); // Esconde navios do oponente
                printf("Alvo (Linha Coluna): ");
                scanf("%d %c", &l_atk, &c_atk);
                resultado = atacar(tabuleiro2, l_atk - 1, toupper(c_atk) - 'A');
                if (resultado == 0) {
                    acertos1++;
                    jogadorAtual = 2;
                }
            } else {
                printf("\n--- TURNO DE %s ---\n", jogador2);
                printTabuleiro(tabuleiro1, 0);
                printf("Alvo (Linha Coluna): ");
                scanf("%d %c", &l_atk, &c_atk);
                resultado = atacar(tabuleiro1, l_atk - 1, toupper(c_atk) - 'A');
                if (resultado == 0) {
                    acertos2++;
                    jogadorAtual = 1;
                }
            }

            // Verifica Fim de Jogo
            int fim1 = 1, fim2 = 1;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (tabuleiro1[i][j] == 'N') fim1 = 0;
                    if (tabuleiro2[i][j] == 'N') fim2 = 0;
                }
            }
            if (fim1 || fim2) break;

            printf("Pressione Enter para continuar...");
            getchar(); getchar();
        }
        printf("\nJOGO ENCERRADO! Vencedor: %s\n", acertos1 > acertos2 ? jogador1 : jogador2);
    }
    return 0;
}

// --- FUNÇÕES ---

void menu() {
    printf("1. Novo Jogo\n3. Instrucoes\n4. Sair\n");
}

void innitTabuleiro(char tabuleiro[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tabuleiro[i][j] = '~';
}

int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna) {
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N) return 1;

    if (direcao == 'H') {
        if (coluna + tamanho > N) return 1;
        for (int i = 0; i < tamanho; i++)
            if (tabuleiro[linha][coluna + i] == 'N') return 1;
        for (int i = 0; i < tamanho; i++)
            tabuleiro[linha][coluna + i] = 'N';
        return 0;
    } else if (direcao == 'V') {
        if (linha + tamanho > N) return 1;
        for (int i = 0; i < tamanho; i++)
            if (tabuleiro[linha + i][coluna] == 'N') return 1;
        for (int i = 0; i < tamanho; i++)
            tabuleiro[linha + i][coluna] = 'N';
        return 0;
    }
    return 1;
}

void printTabuleiro(char tabuleiro[N][N], int spot) {
    printf("   A B C D E F G H I J\n");
    for (int i = 0; i < N; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < N; j++) {
            if (tabuleiro[i][j] == 'N' && spot == 0) printf("~ ");
            else printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int atacar(char tabuleiro[N][N], int linha, int coluna) {
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N || tabuleiro[linha][coluna] == 'O' || tabuleiro[linha][coluna] == 'X') {
        printf("Posicao invalida ou ja atacada!\n");
        return -1;
    }
    if (tabuleiro[linha][coluna] == 'N') {
        tabuleiro[linha][coluna] = 'O';
        printf("Acertou!\n");

        // Lógica simples de "Afundou" (Verifica se sobrou algum 'N' no mapa)
        int sobrouAlgum = 0;
        for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(tabuleiro[i][j] == 'N') sobrouAlgum = 1;
        if(!sobrouAlgum) printf("O NAVIO AFUNDOU E ERA O ULTIMO!\n");

        return 0;
    } else {
        tabuleiro[linha][coluna] = 'X';
        printf("Agua!\n");
        return 0;
    }
}
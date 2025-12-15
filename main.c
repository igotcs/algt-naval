#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int N = 10;
void menu();
void innitTabuleiro(char tabuleiro[N][N]);
void printTabuleiro(char tabuleiro[N][N], int spot);
void posnav(char tabuleiro[N][N], int tamanho, char letra, char direcao, int linha, int coluna);
int atacar(char tabuleiro[N][N], int linha, int coluna);
void salvarResultados(char jogador1[], char jogador2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas);

int main() {
    char tabuleiro1[N][N], tabuleiro2[N][N];
    char jogador1[50], jogador2[50];
    int opt = 0;

    if (opt != 4) {
        menu();
        printf("Escolha uma opcao: ");
        }

        if (opt == 1) {
            printf("Insira o nome do Jogador 1: ");
            scanf("%s", jogador1);
            printf("Insira o nome do jogador2: ");
            scanf("%s", jogador2);

            innitTabuleiro(tabuleiro1);
            innitTabuleiro(tabuleiro2);

            char Navios[3][30] = {"Cruzeiro do Kaka","Charles","Bote"};
            int tamanhoN [3] = {4,3,2};

            int linha;
            char cl, dir;

            // navios do jogador 1
            for(int i=0; i<3; i++) {

                printf("%s, Digite as coordenadas do seu navio\n", jogador1);
                printTabuleiro(tabuleiro1, 1); // mostra tabuleiro
                printf("Navio: %s (Tamanho %d)\n", Navios[i], tamanhoN[i]);
                printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V): ");
                scanf("%d" "%c" "%c", &linha, &cl, &dir);

                cl = toupper(cl);
                dir = toupper(dir);

                int coluna = cl - 'A';
                int linhaIdx = linha - 1;



            }

            // navios dos jogador 2
            for(int i=0; i<3; i++) {

                printf("%s, Digite as coordenadas do seu navio\n", jogador1);
                printTabuleiro(tabuleiro1, 1); // mostra tabuleiro
                printf("Navio: %s (Tamanho %d)\n", Navios[i], tamanhoN[i]);
                printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V): ");
                scanf("%d" "%c" "%c", &linha, &cl, &dir);

                cl = toupper(cl);
                dir = toupper(dir);

            }

            // game engine
            int jogadorAtual = 1;
            int rodadas = 0, acertos1 = 0, acertos2 = 0, erros1 = 0, erros2 = 0;

            while(1) {

                int lin_ataque;
                char cl_ataque;

                if (jogadorAtual == 1) {
                    printf("Turno de %s ", jogador1);
                    printTabuleiro(tabuleiro2, 0);
                    printf("Digite as coordenadas do alvo (Ex: 4 F H): ");
                    scanf("%d %c", &lin_ataque, &cl_ataque);
                    cl_ataque = toupper(cl_ataque);


                    if (atacar(tabuleiro2, lin_ataque-1, cl_ataque - 'A'))
                        acertos1++;
                        else erros1++;

                    jogadorAtual = 2;

                    if (jogadorAtual == 1) {
                        int resultadoatk;

                        do {
                            printf("Turno de %s ", jogador2);
                            printTabuleiro(tabuleiro2, 0); // 0 esconde os navios do oponente

                            printf("Digite as coordenadas do alvo (Ex: 4 B): ");
                            if (scanf("%d %c", &lin_ataque, &cl_ataque) != 2) {
                            }

                            cl_ataque = toupper(cl_ataque);

                            // Chamamos a função e guardamos o retorno
                            resultadoatk = atacar(tabuleiro2, lin_ataque - 1, cl_ataque - 'A');

                            if (resultadoatk == 0) {
                                acertos1++;
                            }
                            else if (resultadoatk == -1) {
                                printf("Pressione Enter para tentar novamente...");
                                getchar(); getchar();
                            }

                        } while (resultadoatk == -1); // Repete enquanto o tiro for inválido

                        jogadorAtual = 2; // Só passa o turno quando o tiro for válido
                    }

                }


                rodadas++;

                int fim1=1, fim2=1;
                for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
                    if(tabuleiro1[i][j] == 'N') fim1 = 0;
                    if(tabuleiro2[i][j] == 'N') fim2 = 0;
                }
                if (fim1 || fim2)
                break;
                printf("\nPressione Enter para passar a vez...");
                getchar(); getchar();
            }

            printf("Jogo encerrado!\n");
            if (acertos1 > acertos2) printf("Vencedor: %s\n", jogador1);
            else if (acertos2 > acertos1) printf("Vencedor: %s\n", jogador2);
            else printf("Empate!\n");

            salvarResultados(jogador1, jogador2, acertos1, acertos2, erros1, erros2, rodadas);
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); getchar();

        }
             else if (opt == 3) {
            printf("As intrucoes do jogo sao as seguintes:\n\n");

                 printf("No inicio do jogo, cada jogador deve posicionar seus navios manualmente em um tabuleiro 10x10\n"
                "no qual as linhas sao letras de 1 a 10 e as colunas são letras de A a J.");
                 printf("Os tipos de embarcacao sao os seguintes:\n"
                 "1. Cruzeiro do Kaka – 4 celulas\n"
                 "2. Charles – 3 celulas\n"
                 "3. Bote – 2 celulas\n");
                 printf("Duas embarcacoes nao podem ocupar uma mesma celula\n");
                 printf("Uma embarcacao nao pode ser posicionada fora do tabuleiro\n");
                 printf("Apos o inicio do jogo, os jogadores se alternam em turnos de ataque. Cada jogada insiste em\n"
                 "informar coordenadas (linha e coluna) para atacar o tabuleiro do adversario.");
                 printf("o Após cada tiro a tela mostrará uma resposta:\n"
                 "1. Errou!\n"
                 "2. Acertou!\n");
                 "2. Afundou, quando uma embarcacao adversario for totalmente destruida.\n");
                 printf("O jogo termina quando todos os navios de um dos dois jogadores forem destruidos.\n\n'");

        }
    }
    return 0;
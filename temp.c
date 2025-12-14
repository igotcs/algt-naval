#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 10; // referencia

// ---------- declaramento de funcoes ----------
void menu();
void inicializarTabuleiro(char tabuleiro[N][N]);
void imprimirTabuleiro(char tabuleiro[N][N], int revelarNavios);
void posicionarNavio(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna);
int atacar(char tabuleiro[N][N], int linha, int coluna);
void salvarResultados(char nome1[], char nome2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas);

// ---------- funcao main ----------
int main() {
    char tabuleiro1[N][N], tabuleiro2[N][N];
    char nome1[50], nome2[50];
    int opt;
    
    while(1) {
        menu();
        printf("Escolha uma opcao:\n");
        scanf("%d", &opt);

        if (opt == 1) {
            printf("[ NOVO JOGO ]\n");
            
            // nomes
            printf("Nome jogador 1: ");
            scanf("%s", nome1);
            
            printf("Nome jogador 2: ");
            scanf("%s", nome2);

            // inicializa tabuleiros
            inicializarTabuleiro(tabuleiro1);
            inicializarTabuleiro(tabuleiro2);
             struct n {
        char nav[50];
        int tamanho;
    };
    struct n navio[3];
    strcpy (navio[0].nav, "Cruzeiro do Kaká");
    strcpy (navio[1].nav, "Charles");
    strcpy (navio[2].nav, "Bote");
    navio[0].tamanho = 4;
    navio[1].tamanho = 3;
    navio[2].tamanho = 2;
            int linha, coluna, convchar = 65;
                char c;
                char d;
            // posicionamento manual de navios (exemplo 3 navios por jogador)
            for(int i=0; i<3; i++) {
                printf("\n%s, posicione navio %s (linha 1-10 coluna A-J, direcao H/V, tamanho %d): ", nome1, navio[i].nav, navio[i].tamanho);
                scanf("%d %c %c", &linha, &c, &d);
                coluna = c - convchar;
                linha += -1;
                posicionarNavio(tabuleiro1, navio[i].tamanho, d, linha, coluna);
            }

            for(int i=0; i<3; i++) {
                printf("\n%s, posicione navio %s (linha 1-10 coluna A-J, direcao H/V, tamanho %d): ", nome2, navio[i].nav, navio[i].tamanho);
                scanf("%d %c %c", &linha, &c, &d);
                coluna = c - convchar;
                linha += -1;
                posicionarNavio(tabuleiro2, navio[i].tamanho, d, linha, coluna);
            }

            // loop de jogo
            int jogadorAtual = 1;
            int rodadas = 0;
            int acertos1 = 0, acertos2 = 0, erros1 = 0, erros2 = 0;
            while(1) {
                rodadas++;
                int linha, coluna;
                if (jogadorAtual == 1) {
                    printf("\nVez de %s\n", nome1);
                    imprimirTabuleiro(tabuleiro2, 0); // não revela navios
                    printf("Digite linha e coluna para atacar: ");
                    scanf("%d %d", &linha, &coluna);
                    int resultado = atacar(tabuleiro2, linha, coluna);
                    if (resultado) acertos1++; else erros1++;
                    jogadorAtual = 2;
                } else {
                    printf("\nVez de %s\n", nome2);
                    imprimirTabuleiro(tabuleiro1, 0);
                    printf("Digite linha e coluna para atacar: ");
                    scanf("%d %d", &linha, &coluna);
                    int resultado = atacar(tabuleiro1, linha, coluna);
                    if (resultado) acertos2++; else erros2++;
                    jogadorAtual = 1;
                }

                // verifica fim do jogo
                int fim1=1, fim2=1;
                for(int i=0;i<N;i++) for(int j=0;j<N;j++) {if(tabuleiro1[i][j]=='S') fim1=0; if(tabuleiro2[i][j]=='S') fim2=0;}
                if(fim1 || fim2) break;
            }

            // resultado
            printf("\n=== JOGO ENCERRADO ===\n");
            if (acertos1 > acertos2) printf("Vencedor: %s\n", nome1);
            else if (acertos2 > acertos1) printf("Vencedor: %s\n", nome2);
            else printf("Empate!\n");
            printf("%s - Acertos: %d, Erros: %d\n", nome1, acertos1, erros1);
            printf("%s - Acertos: %d, Erros: %d\n", nome2, acertos2, erros2);
            printf("Rodadas: %d\n", rodadas);

            salvarResultados(nome1, nome2, acertos1, acertos2, erros1, erros2, rodadas);

        } 
        else if (opt == 2) {
            printf("[ CONTINUAR JOGO ] - Ainda nao implementado\n");
        } 
        else if (opt == 3) {
            system("clear");
            printf("[ INSTRUÇÕES ]\n");
             printf("o Objetivo do Jogo: Afundar todos os navios inimigos\n");
        printf("o Cada jogador começa o jogo posicionando seus navios em um tabuleiro com 10x10,\n" 
            "no qual as linhas são letras (de A a J), e as colunas são números(de 1 a 10). ");
        printf("o Os tipos de embarcação são os seguintes:\n"
            "1. Cruzeiro do Kaka – 4 células\n"
            "2. Charles – 3 células\n"
            "3. Bote – 2 células\n");
        printf("o Duas embarcações não podem ocupar uma mesma célula\n");
        printf("o Uma embarcação não pode ser posicionada fora do tabuleiro\n");
        printf("o Após o inicio do jogo, cada jogador terá acesso ao tabuleiro organizado pelo adversário,\n"
            "com os navios escondidos.Os jogadores se revezam em turnos para atirar nos navios adversários\n");
        printf("o Após cada tiro a tela mostrará uma resposta:\n"
        "1. Água\n"
        "2. Acertou\n");
        printf("o Quando um navio for afundado, aparecerá 'Afundou na tela\n\n\n'");
        printf("0 0 0   0 0 0 0  0      0          0  0 0 0 0  0 0 0 0  0 0 0 0    000\n" 
               "0    0  0     0  0 0  0 0          0  0     0  0        0     0    000\n"
               "0 0 0   0     0  0  00  0          0  0     0  0   0 0  0     0    000\n" 
               "0    0  0     0  0      0    0     0  0     0  0     0  0     0    000\n"
               "0 0 0   0 0 0 0  0      0    0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0     0\n");
}
        else if (opt == 4) {
            printf("SAINDO...\n");
            break;
        } 
        else {
            printf("OPCAO INVALIDA!\n");
        }
    }

    return 0;
}

// ---------- FUNCOES ----------

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
void inicializarTabuleiro(char tabuleiro[N][N]) {
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            tabuleiro[i][j] = '~';
}

void imprimirTabuleiro(char tabuleiro[N][N], int revelarNavios) {
    printf("  ");
    for(int j=0;j<N;j++)  printf("%c ", 'A'+i);
    printf("\n");
    for(int i=1;i<N+1;i++) {
        printf("%d ",i);
        for(int i=0;i<N;j++) {
            if(tabuleiro[j][i]=='S' && !revelarNavios) printf("~ ");
            else printf("%c ", tabuleiro[j][i]);
        }
        printf("\n");
    }
}

void posicionarNavio(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna) {
    if(direcao =='H') {
        if(coluna+tamanho>N) { printf("Navio nao cabe!\n"); return; }
        for(int i=0;i<tamanho;i++) if(tabuleiro[linha][coluna+i]=='S'){printf("Espaco ocupado!\n"); return;}
        for(int i=0;i<tamanho;i++) tabuleiro[linha][coluna+i]='S';
    } else if(direcao=='V') {
        if(linha+tamanho>N) { printf("Navio nao cabe!\n"); return; }
        for(int i=0;i<tamanho;i++) if(tabuleiro[linha+i][coluna]=='S'){printf("Espaco ocupado!\n"); return;}
        for(int i=0;i<tamanho;i++) tabuleiro[linha+i][coluna]='S';
    } else printf("Direcao invalida!\n");
    printf("Navio posicionado com sucesso!\n");
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

void salvarResultados(char nome1[], char nome2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas) {
    FILE *fp = fopen("resultado.txt","w");
    if(!fp) { printf("Erro ao abrir arquivo!\n"); return;}
    fprintf(fp,"Vencedor: %s\n", acertos1>acertos2?nome1:(acertos2>acertos1?nome2:"Empate"));
    fprintf(fp,"%s - Acertos: %d, Erros: %d\n", nome1, acertos1, erros1);
    fprintf(fp,"%s - Acertos: %d, Erros: %d\n", nome2, acertos2, erros2);
    fprintf(fp,"Rodadas: %d\n", rodadas);
    fclose(fp);
    printf("Resultados salvos em resultado.txt\n");
}






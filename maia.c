
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 10; 

// ---------- PROTÓTIPOS ----------
void menu();
void inicializarTabuleiro(char tabuleiro[N][N]);
void imprimirTabuleiro(char tabuleiro[N][N], int revelarNavios);
void posicionarNavio(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna);
int atacar(char tabuleiro[N][N], int linha, int coluna);
void salvarResultados(char nome1[], char nome2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas);

// Estrutura para os navios
struct n {
    char nav[50];
    int tamanho;
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

    while (opt != 4) {
        menu();
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opt) != 1) {
            while(getchar() != '\n'); 
            continue;
        }
        getchar(); 

        if (opt == 1) {
            printf("Nome jogador 1: ");
            scanf("%s", nome1);
            printf("Nome jogador 2: ");
            scanf("%s", nome2);

            inicializarTabuleiro(tabuleiro1);
            inicializarTabuleiro(tabuleiro2);

            int linha;
            char c, d;

            // POSICIONAMENTO JOGADOR 1
            for(int i=0; i<3; i++) {
            
                printf("=== %s, POSICIONE SEUS NAVIOS ===\n", nome1);
                imprimirTabuleiro(tabuleiro1, 1);
                printf("\nNavio: %s (Tamanho %d)\n", navio[i].nav, navio[i].tamanho);
                printf("Digite Linha (1-10), Coluna (A-J) e Direcao (H/V): ");
                scanf("%d %c %c", &linha, &c, &d);
                
                if (c >= 'a') c -= 32;
                if (d >= 'a') d -= 32;
                posicionarNavio(tabuleiro1, navio[i].tamanho, d, linha-1, c - 'A');
            }

            // POSICIONAMENTO JOGADOR 2
            for(int i=0; i<3; i++) {
                
                printf("=== %s, POSICIONE SEUS NAVIOS ===\n", nome2);
                imprimirTabuleiro(tabuleiro2, 1);
                printf("\nNavio: %s (Tamanho %d)\n", navio[i].nav, navio[i].tamanho);
                printf("Digite Linha (1-10), Coluna (A-J) e Direcao (H/V): ");
                scanf("%d %c %c", &linha, &c, &d);
                
                if (c >= 'a') c -= 32;
                if (d >= 'a') d -= 32;
                posicionarNavio(tabuleiro2, navio[i].tamanho, d, linha-1, c - 'A');
            }

            // LOOP DE JOGO
            int jogadorAtual = 1;
            int rodadas = 0, acertos1 = 0, acertos2 = 0, erros1 = 0, erros2 = 0;
            
            while(1) {
                system("clear || cls");
                int l_ataque;
                char c_ataque;

                if (jogadorAtual == 1) {
                    printf("\n--- VEZ DE %s ---\n", nome1);
                    imprimirTabuleiro(tabuleiro2, 0);
                    printf("Alvo (Ex: 5 B): ");
                    scanf("%d %c", &l_ataque, &c_ataque);
                    if (c_ataque >= 'a') c_ataque -= 32;

                    if (atacar(tabuleiro2, l_ataque-1, c_ataque - 'A')) acertos1++; else erros1++;
                    jogadorAtual = 2;
                } else {
                    printf("\n--- VEZ DE %s ---\n", nome2);
                    imprimirTabuleiro(tabuleiro1, 0);
                    printf("Alvo (Ex: 5 B): ");
                    scanf("%d %c", &l_ataque, &c_ataque);
                    if (c_ataque >= 'a') c_ataque -= 32;

                    if (atacar(tabuleiro1, l_ataque-1, c_ataque - 'A')) acertos2++; else erros2++;
                    jogadorAtual = 1;
                }
                
                rodadas++;
                // Verifica fim
                int fim1=1, fim2=1;
                for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
                    if(tabuleiro1[i][j]=='S') fim1=0;
                    if(tabuleiro2[i][j]=='S') fim2=0;
                }
                if(fim1 || fim2) 
                break;
                printf("\nPressione Enter para passar a vez...");
                getchar(); getchar(); 
            }

            printf("\n=== JOGO ENCERRADO ===\n");
            if (acertos1 > acertos2) printf("Vencedor: %s\n", nome1);
            else if (acertos2 > acertos1) printf("Vencedor: %s\n", nome2);
            else printf("Empate!\n");
            
            salvarResultados(nome1, nome2, acertos1, acertos2, erros1, erros2, rodadas);
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); getchar();

        } else if (opt == 3) {
            system("clear || cls");
            printf("[ INSTRUÇÕES ]\nAfunde os navios inimigos (S) acertando as coordenadas.\n");
            printf("O = Acerto | X = Erro (Agua) | ~ = Desconhecido\n");
            printf("\nPressione Enter para voltar...");
            getchar();
        }
    }
    return 0;
}

// ---------- IMPLEMENTAÇÃO DAS FUNÇÕES ----------

void inicializarTabuleiro(char tabuleiro[N][N]) {
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            tabuleiro[i][j] = '~';
}

void imprimirTabuleiro(char tabuleiro[N][N], int revelarNavios) {
    printf("\n    ");
    for(int j=0; j<N ;j++) printf("%c ", 'A'+ j);
    printf("\n");

    for(int i=0; i<N; i++) {
        printf("%2d ", i + 1);
        for(int j=0; j<N; j++) {
            if(tabuleiro[i][j] == 'S' && !revelarNavios) printf("~ ");
            else printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarNavio(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna) {
    if(direcao =='H') {
        if(coluna+tamanho > N) return;
        for(int i=0; i<tamanho; i++) if(tabuleiro[linha][coluna+i]=='S') return;
        for(int i=0; i<tamanho; i++) tabuleiro[linha][coluna+i]='S';
    } else {
        if(linha+tamanho > N) return;
        for(int i=0; i<tamanho; i++) if(tabuleiro[linha+i][coluna]=='S') return;
        for(int i=0; i<tamanho; i++) tabuleiro[linha+i][coluna]='S';
    }
}

int atacar(char tabuleiro[N][N], int linha, int coluna) {
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N) return 0;

    if(tabuleiro[linha][coluna] == 'S') {
        tabuleiro[linha][coluna] = 'O';
        printf("\nACERTOU!\n");
        return 1;
    } else {
        if(tabuleiro[linha][coluna] == '~') tabuleiro[linha][coluna] = 'X';
        printf("\nAGUA!\n");
        return 0;
    }
}

void salvarResultados(char nome1[], char nome2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas) {
    FILE *fp = fopen("resultado.txt","w");
    if(!fp) return;
    fprintf(fp,"Relatorio Final\n%s: %d acertos\n%s: %d acertos\nRodadas: %d", nome1, acertos1, nome2, acertos2, rodadas);
    fclose(fp);
}

void menu() {
    printf("\n=== BATALHA NAVAL ===\n1 - NOVO JOGO\n2 - CONTINUAR\n3 - INSTRUCOES\n4 - SAIR\n");
}

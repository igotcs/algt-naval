#include <stdio.h>
#include <stdlib.h>

void menu();

int main() {
    int opt;
    struct ponto {
            int linha;
            char coluna;}
        
    char tabuleiro[10][10];
    char linha = '1', coluna = 'A';
    for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        tabuleiro[i][j][0] = linha 

        tabuleiro[i][j][1] = coluna
            
    }
}


    while (1) {
        menu();
        printf("ESCOLHA UMA OPÇÃO: ");
        scanf("%d", &opt);

        if (opt == 1) {
            system("clear");
            printf("[ NOVO JOGO ]\n");
            // futuramente: iniciar tabuleiros, pedir nomes, posicionar navios
        } 
        else if (opt == 2) {
            system("clear");
            printf("[ CONTINUAR JOGO ]\n");
            // futuramente: carregar arquivo
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
        else if (opt==4) {
            printf("SAINDO...");
            break;}
        else {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
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








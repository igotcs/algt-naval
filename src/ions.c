#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10

void menu();
void innitTabuleiro(char tabuleiro[N][N]);
void printTabuleiro(char tabuleiro[N][N], int spot);
int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna, char letra);
int atacar(char tabuleiro[N][N], int linha, int coluna);

int main() {
    char tabuleiro1[N][N], tabuleiro2[N][N];
    char jogador1[50], jogador2[50];
    char nome_arq;
    strcpy(nome_arq,"data.txt");
    int opt = 0;

    while (opt !=4) {

        menu();
        printf("Escolha uma opcao:\n\n");
        scanf("%d", &opt);

        if (opt == 1) {
            printf("Insira o nome do Jogador 1: ");
            scanf("%s", jogador1);
            printf("Insira o nome do jogador2: ");
            scanf("%s", jogador2);

            innitTabuleiro(tabuleiro1);
            innitTabuleiro(tabuleiro2);

            char Navios[3][30] = {"Cruzeiro do Kaka","Charles","Bote"};
            int tamanhoN[3] = {4,3,2};

            int linha;
            char cl, dir;



            // navios do jogador 1
        for (int i = 0; i < 3; i++) {

            int cond = 0;

            while (!cond) {
                printf("%s, Digite as coordenadas do seu navio:\n", jogador1);
                printTabuleiro(tabuleiro1, 1);
                printf("\nNavio: %s (Tamanho %d)\n", Navios[i], tamanhoN[i]);
                printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V): ");
                scanf("%d %c %c", &linha, &cl, &dir);


            linha--;                    // 1–10 → 0–9
            cl = toupper(cl) - 'A';     // A–J → 0–9
            dir = toupper(dir);

        char letraN[3] = {'K', 'C', 'B'};
        cond = posnav(tabuleiro1, tamanhoN[i], dir, linha, cl, letraN[i]);


        if (!cond){
             printf("\nNao foi possivel posicionar o navio. Tente novamente.\n\n");
            }else printf("Navio posicionado com sucesso.\n");
            }
        }

            // navios dos jogador 2
            for (int i = 0; i < 3; i++) {

            int cond = 0;

            while (!cond) {
                printf("%s, Digite as coordenadas do seu navio:\n", jogador2);
                printTabuleiro(tabuleiro2, 1);
                printf("\nNavio: %s (Tamanho %d)\n", Navios[i], tamanhoN[i]);
                printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V): ");
                scanf("%d %c %c", &linha, &cl, &dir);


            linha--;                    // 1–10 → 0–9
            cl = toupper(cl) - 'A';     // A–J → 0–9
            dir = toupper(dir);

        char letraN[3] = {'K', 'C', 'B'};
        cond = posnav(tabuleiro2, tamanhoN[i], dir, linha, cl, letraN[i]);


        if (!cond){
             printf("\nNao foi possivel posicionar o navio. Tente novamente.\n\n");
            }else printf("Navio posicionado com sucesso.\n");
            }
        }

            // game engine
            int jogadorAtual = 1;
            int rodadas = 0, acertos1 = 0, acertos2 = 0, erros1 = 0, erros2 = 0;



                int lin_ataque;
                char cl_ataque;
                int fim1 = 1;
                int fim2 = 1;

                while (1) {
                int resultadoatk=0;
                fim1 = 1;
                fim2 = 1;

                //jogador 1
                if (jogadorAtual == 1) {
                printf("Vez de %s\n", jogador1);
                printTabuleiro(tabuleiro2, 0);
            do{
                printf("Digite as coordenadas do alvo (Ex: 4 F): ");
                scanf("%d %c", &lin_ataque, &cl_ataque);

                resultadoatk = atacar(tabuleiro2, lin_ataque - 1, toupper(cl_ataque) - 'A');

                if (resultadoatk == 1 || resultadoatk == 3)
                acertos1++;
                else if (resultadoatk == 2)
                 erros1++;
            }while(resultadoatk==0);
                    //jogador 2
                    jogadorAtual = 2;
                    salvarJogo(nome_arq, tabuleiro1, tabuleiro2, jogador1, jogador2, jogadorAtual, rodadas, acertos1, acertos2, erros1, erros2);
            }
            else {
                printf("Vez de %s\n", jogador2);
                printTabuleiro(tabuleiro1, 0);
                resultadoatk=0;
                do{
                printf("Digite as coordenadas do alvo (Ex: 4 B): ");
                scanf("%d %c", &lin_ataque, &cl_ataque);

             resultadoatk = atacar(tabuleiro1, lin_ataque - 1, toupper(cl_ataque) - 'A');

                if (resultadoatk == 1 || resultadoatk == 3)
                 acertos2++;
                else if (resultadoatk == 2)
                 erros2++;
                }while(resultadoatk==0);
                jogadorAtual = 1;
                salvarJogo(nome_arq, tabuleiro1, tabuleiro2, jogador1, jogador2, jogadorAtual, rodadas, acertos1, acertos2, erros1, erros2);
            }

                rodadas++;

                for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (tabuleiro1[i][j] == 'K' || tabuleiro1[i][j] == 'C' || tabuleiro1[i][j] == 'B')
                        fim1 = 0;
                    if (tabuleiro2[i][j] == 'K' || tabuleiro2[i][j] == 'C' || tabuleiro2[i][j] == 'B')
                         fim2 = 0;
             }
                 }

                if (fim1 || fim2)
                     break;
                    }





            printf("Jogo encerrado!\n");
            printf("O Jogador %s teve %d acertos e %d erros.\n", jogador1, acertos1, erros1);
            printf("O Jogador %s teve %d acertos e %d erros.\n", jogador2, acertos2, erros2);
            printf("O jogo acabou apos %d rodadas\n\n", rodadas);

            if (fim2)
            printf("VENCEDOR: %s\n", jogador1);
            else if (fim1)
            printf("VENCEDOR: %s\n", jogador2);

            printf("\nPressione Enter para voltar ao menu...");
            getchar(); getchar();
                }
                if (opt == 2) { 
                   carregarJogo(nome_arq , tabuleiro1, tabuleiro2, jogador1, jogador2, jogadorAtual, rodadas, acertos1, acertos2, erros1, erros2);
                     int lin_ataque;
                char cl_ataque;
                int fim1 = 1;
                int fim2 = 1;

                while (1) {
                int resultadoatk=0;
                fim1 = 1;
                fim2 = 1;

                //jogador 1
                if (jogadorAtual == 1) {
                printf("Vez de %s\n", jogador1);
                printTabuleiro(tabuleiro2, 0);
            do{
                printf("Digite as coordenadas do alvo (Ex: 4 F): ");
                scanf("%d %c", &lin_ataque, &cl_ataque);

                resultadoatk = atacar(tabuleiro2, lin_ataque - 1, toupper(cl_ataque) - 'A');

                if (resultadoatk == 1 || resultadoatk == 3)
                acertos1++;
                else if (resultadoatk == 2)
                 erros1++;
            }while(resultadoatk==0);

                    //jogador 2
                    jogadorAtual = 2;
            }
            else {
                printf("Vez de %s\n", jogador2);
                printTabuleiro(tabuleiro1, 0);
                resultadoatk=0;
                do{
                printf("Digite as coordenadas do alvo (Ex: 4 B): ");
                scanf("%d %c", &lin_ataque, &cl_ataque);

             resultadoatk = atacar(tabuleiro1, lin_ataque - 1, toupper(cl_ataque) - 'A');

                if (resultadoatk == 1 || resultadoatk == 3)
                 acertos2++;
                else if (resultadoatk == 2)
                 erros2++;
                }while(resultadoatk==0);
                jogadorAtual = 1;
            }

                rodadas++;

                for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (tabuleiro1[i][j] == 'K' || tabuleiro1[i][j] == 'C' || tabuleiro1[i][j] == 'B')
                        fim1 = 0;
                    if (tabuleiro2[i][j] == 'K' || tabuleiro2[i][j] == 'C' || tabuleiro2[i][j] == 'B')
                         fim2 = 0;
             }
                 }

                if (fim1 || fim2)
                     break;
                    }





            printf("Jogo encerrado!\n");
            printf("O Jogador %s teve %d acertos e %d erros.\n", jogador1, acertos1, erros1);
            printf("O Jogador %s teve %d acertos e %d erros.\n", jogador2, acertos2, erros2);
            printf("O jogo acabou apos %d rodadas\n\n", rodadas);

            if (fim2)
            printf("VENCEDOR: %s\n", jogador1);
            else if (fim1)
            printf("VENCEDOR: %s\n", jogador2);

            printf("\nPressione Enter para voltar ao menu...");
            getchar(); getchar();
                }
                }
             if (opt == 3) {
                printf("As intrucoes do jogo sao as seguintes:\n\n");

                 printf("No inicio do jogo, cada jogador deve posicionar seus navios manualmente em um tabuleiro 10x10\n"
                "no qual as linhas sao letras de 1 a 10 e as colunas sao letras de A a J.");
                 printf("Os tipos de embarcacao sao os seguintes:\n"
                 "1. Cruzeiro do Kaka: 4 celulas\n"
                 "2. Charles: 3 celulas\n"
                 "3. Bote: 2 celulas\n");
                 printf("Duas embarcacoes nao podem ocupar uma mesma celula\n");
                 printf("Uma embarcacao nao pode ser posicionada fora do tabuleiro\n");
                 printf("Apos o inicio do jogo, os jogadores se alternam em turnos de ataque. Cada jogada insiste em\n"
                 "informar coordenadas (linha e coluna) para atacar o tabuleiro do adversario.\n");
                 printf("Apos cada tiro a tela mostrara uma resposta:\n"
                 "1. Errou!\n"
                 "2. Acertou!\n"
                 "3. Afundou, quando uma embarcacao adversario for totalmente destruida.\n");
                 printf("O jogo termina quando todos os navios de um dos dois jogadores forem destruidos.\n\n");
             }

            if (opt == 4) {
                printf("Saindo do jogo...\n");
            }
        }
      return 0;
    }


int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna, char letra) {

    direcao = toupper(direcao);

    if (direcao == 'H') {
        if (coluna < 0 || coluna + tamanho > N) // verifica coluna pq a direcao é H (Horizontal)
        return 0; // se for maior que o tamanho do tabuleiro, retorna 0, erro

        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] == 'K' || tabuleiro[linha][coluna + i] == 'C' || tabuleiro[linha][coluna + i] == 'B')
            return 0; // se ja houver navio, retorna 0, erro
        }

        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha][coluna + i] = letra;
        }
        return 1; // se der certo, retorna 1, no int 'cond'
    }
    else if (direcao == 'V') {
        if (linha < 0 || linha + tamanho > N)
            return 0;

        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] == 'K' || tabuleiro[linha + i][coluna] == 'C' || tabuleiro[linha + i][coluna] == 'B')
                return 0;
        }
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna] = letra;
        }
        return 1;
    }
    return 0;
}

void menu() {

    printf("Bem vindo a Batalha Naval!\n\n");
    printf("Escolha uma opcao abaixo:\n");
    printf("1. Novo Jogo.\n");
    printf("2. Continuar Jogo.\n");
    printf("3. Instrucoes.\n");
    printf("4. Sair do Jogo.\n");

}
void innitTabuleiro(char tabuleiro[N][N]) {
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            tabuleiro[i][j] = '~'; // percorre todos os elementos N pra criar uma matriz [N][N] de elemento ~
}

void printTabuleiro(char tabuleiro[N][N], int spot) {
    printf("\n"); //cria um espaço pra ficar bonitinho
    for(int j=0; j<N ; j++)
        printf("%2c", 'A'+ j); // cria uma matriz [j] correspondente as colunas, de N elementos, no caso N = 10
    printf("\n");

    for(int i=0; i<N; i++) {
        printf("%d", i + 1); // i + 1 são os elementos de 0 a 9. lá em cima tem a funcao linha-- pra garantir que cumpra esse intervalo
        for(int j=0; j<N; j++) {
            if((tabuleiro[i][j] == 'K' || tabuleiro[i][j] == 'C' || tabuleiro [i][j] == 'B') && !spot) // se ambos forem verdadeiros
                printf(" ~");
            else printf("%2c", tabuleiro[i][j]);
        }
        printf("\n");
    }
}
int atacar(char tabuleiro[N][N], int linha, int coluna){

    char alvo = tabuleiro[linha][coluna];

    if(alvo == 'K' || alvo == 'C' || alvo == 'B'){
        tabuleiro[linha][coluna] = 'O'; // marca como atingido
        printf("Acertou!\n");

        int afundou = 1;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(tabuleiro[i][j] == alvo){
                    afundou = 0;
                }
            }
        }

        if(afundou == 1){
            if(alvo == 'K')
            printf("Cruzeiro do Kaka adversario afundou!\n");
            else if(alvo == 'C')
            printf("Charles adversario afundou!\n");
            else if(alvo == 'B')
            printf("Bote adversario afundou!\n");
                return 3;
        }

        return 1; // retorna 1 se acertou
    }
    else if(alvo == '~'){
        tabuleiro[linha][coluna] = 'X';
        printf("Errou!\n");
        return 2; // retorna 2 se errou
    }
    else {
        printf("Erro! Posicao invalida!\n"); // coordenada invalida ou ja atingida
        return 0;
    }
} 
int salvarJogo( char nome_arq[],
               char tab1[10][10], char tab2[10][10],
               char nome1, char nome2,
               int jogadorAtual, int rodadas,
               int acertos1, int acertos2, int erros1, int erros2)
{
    FILE *p;
    p = fopen(nome_arq, "w");
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
int carregarJogo(char nome_arq[] ,
                 char tab1[10][10], char tab2[10][10],
                 char nome1[], char nome2[],
                 int jogadorAtual, int rodadas,
                 int acertos1, int acertos2, int erros1, int erros2)
{
    FILE *p; 
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

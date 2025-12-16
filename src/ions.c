#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10
#define ARQUIVO_SALVAMENTO "salvamento.dat"

// --- Estrutura de Dados ---
// Define todos os dados necessários para salvar/carregar o estado do jogo
typedef struct {
    char jogador1[50];
    char jogador2[50];
    char tabuleiro1[N][N];
    char tabuleiro2[N][N];
    int acertos1;
    int acertos2;
    int erros1;
    int erros2;
    int rodadas;
    int jogadorAtual; // 1 ou 2
    int jogoEmAndamento; // 0 ou 1
} EstadoDoJogo;

// --- Protótipos das Funções ---
void menu();
void limpar_buffer();
void initTabuleiro(char tabuleiro[N][N]);
void printTabuleiro(char tabuleiro[N][N], int spot);
int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna, char letra);
int atacar(char tabuleiro[N][N], int linha, int coluna);
int salvarJogo(EstadoDoJogo *estado);
int carregarJogo(EstadoDoJogo *estado);
void exibirInstrucoes();
void salvarResultados(char jogador1[], char jogador2[], int acertos1, int acertos2, int erros1, int erros2, int rodadas);


// --- Funções de Salvar/Carregar (Implementação) ---

int salvarJogo(EstadoDoJogo *estado) {
    FILE *arquivo = fopen(ARQUIVO_SALVAMENTO, "wb");

    if (arquivo == NULL) {
        printf("❌ Erro ao abrir arquivo para salvar!\n");
        return 0;
    }

    // Escreve a struct inteira no arquivo
    fwrite(estado, sizeof(EstadoDoJogo), 1, arquivo);
    fclose(arquivo);

    printf("\n✅ Jogo salvo com sucesso em '%s'.\n", ARQUIVO_SALVAMENTO);
    return 1;
}

int carregarJogo(EstadoDoJogo *estado) {
    FILE *arquivo = fopen(ARQUIVO_SALVAMENTO, "rb");

    if (arquivo == NULL) {
        // Arquivo não existe, não há jogo salvo
        printf("\n❌ Nao ha um jogo salvo para carregar.\n");
        return 0;
    }

    // Lê a struct inteira do arquivo
    fread(estado, sizeof(EstadoDoJogo), 1, arquivo);
    fclose(arquivo);

    printf("\n✅ Jogo carregado com sucesso!\n");
    return 1;
}

// --- Funções Auxiliares (Implementação) ---

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("--- Bem Vindo a Batalha Naval! ---\n\n");
    printf("Escolha uma opcao abaixo:\n");
    printf("1. Novo Jogo.\n");
    printf("2. Continuar Jogo.\n");
    printf("3. Instrucoes.\n");
    printf("4. Sair do Jogo.\n");
}

void initTabuleiro(char tabuleiro[N][N]) {
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            tabuleiro[i][j] = '~';
}

void printTabuleiro(char tabuleiro[N][N], int spot) {
    printf("\n  "); // Espaço para alinhamento
    for(int j=0; j<N ; j++)
        printf("%2c", 'A'+ j);
    printf("\n");

    for(int i=0; i<N; i++) {
        printf("%d", i + 1);
        for(int j=0; j<N; j++) {
            // Se 'spot' for 0 (modo ataque), esconde navios ('K', 'C', 'B')
            if((tabuleiro[i][j] == 'K' || tabuleiro[i][j] == 'C' || tabuleiro [i][j] == 'B') && !spot)
                printf(" ~");
            else 
                printf("%2c", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posnav(char tabuleiro[N][N], int tamanho, char direcao, int linha, int coluna, char letra) {

    direcao = toupper(direcao);

    // 1. Verificação de limites e coordenadas iniciais
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N)
        return 0;

    if (direcao == 'H') {
        if (coluna + tamanho > N) 
            return 0; // Navio sai do tabuleiro

        // 2. Verificação de colisão
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] != '~')
            return 0; // Colisão com outro navio
        }

        // 3. Posicionamento
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha][coluna + i] = letra;
        }
        return 1;
    }
    else if (direcao == 'V') {
        if (linha + tamanho > N)
            return 0; // Navio sai do tabuleiro

        // 2. Verificação de colisão
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna] != '~')
                return 0; // Colisão com outro navio
        }
        
        // 3. Posicionamento
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna] = letra;
        }
        return 1;
    }
    return 0; // Direção inválida
}

int atacar(char tabuleiro[N][N], int linha, int coluna){
    
    // Proteção contra acesso fora dos limites
    if (linha < 0 || linha >= N || coluna < 0 || coluna >= N) {
        printf("Posicao fora dos limites do tabuleiro (1-10, A-J).\n");
        return 0;
    }
    
    char alvo = tabuleiro[linha][coluna];

    if(alvo == 'K' || alvo == 'C' || alvo == 'B'){
        tabuleiro[linha][coluna] = 'O'; // Marca como atingido
        printf("🎯 Acertou!\n");

        int afundou = 1;
        // Verifica se o navio de tipo 'alvo' ainda tem peças não atingidas
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(tabuleiro[i][j] == alvo){
                    afundou = 0;
                    break; // Sai do loop interno e externo se encontrar uma peça
                }
            }
            if (!afundou && i < N) break;
        }

        if(afundou == 1){
            printf("💣 Afundou o ");
            if(alvo == 'K') printf("Cruzeiro do Kaka ");
            else if(alvo == 'C') printf("Charles ");
            else if(alvo == 'B') printf("Bote ");
            printf("adversario!\n");
            return 3; // Retorna 3 se afundou
        }
        return 1; // Retorna 1 se acertou
    }
    else if(alvo == '~'){
        tabuleiro[linha][coluna] = 'X';
        printf("💧 Errou!\n");
        return 2; // Retorna 2 se errou
    }
    else if (alvo == 'X' || alvo == 'O') {
        printf("⚠️ Erro! Posicao ja atacada.\n");
        return 0;
    }
    // Caso de erro de lógica (deveria ser coberto pela verificação de limites ou já atacado)
    return 0;
}

void exibirInstrucoes() {
    printf("--- Instrucoes do Jogo ---\n\n");
    printf("No inicio, posicione seus navios em um tabuleiro 10x10 (Linhas 1-10, Colunas A-J).\n\n");
    printf("Os navios sao:\n"
           "1. Cruzeiro do Kaka (K) – 4 celulas\n"
           "2. Charles (C) – 3 celulas\n"
           "3. Bote (B) – 2 celulas\n\n");
    printf("Regras de Posicionamento:\n"
           "* Duas embarcacoes nao podem se sobrepor.\n"
           "* Uma embarcacao nao pode ser posicionada fora do tabuleiro.\n\n");
    printf("Regras de Ataque:\n"
           "Os jogadores se alternam atacando as coordenadas do adversario.\n"
           "* Tiro na agua ('~' -> 'X'): Errou! (Retorno 2)\n"
           "* Tiro em navio ('K'/'C'/'B' -> 'O'): Acertou! (Retorno 1)\n"
           "* Tiro que destrói o navio: Afundou! (Retorno 3)\n\n");
    printf("O jogo termina quando todos os navios de um dos dois jogadores forem destruidos.\n\n");
}

void salvarResultados(char jogador1[], char jogador2[],
                      int acertos1, int acertos2,
                      int erros1, int erros2, int rodadas) {
    // Implementacao basica de salvamento de resultados em arquivo de texto
    FILE *arquivo = fopen("resultados.txt", "a"); // 'a' = append (adicionar)

    if (arquivo == NULL) {
        printf("Erro ao salvar resultados!\n");
        return;
    }

    fprintf(arquivo, "--- JOGO ENCERRADO ---\n");
    fprintf(arquivo, "Rodadas: %d\n", rodadas);
    fprintf(arquivo, "Vencedor: %s\n", (acertos2 >= 9) ? jogador1 : jogador2);
    fprintf(arquivo, "%s: Acertos=%d, Erros=%d\n", jogador1, acertos1, erros1);
    fprintf(arquivo, "%s: Acertos=%d, Erros=%d\n", jogador2, acertos2, erros2);
    fprintf(arquivo, "------------------------\n\n");

    fclose(arquivo);
    printf("Resultados finais salvos em 'resultados.txt'.\n");
}

// --- Função Principal (Main) ---

int main() {
    
    EstadoDoJogo estado;
    estado.jogoEmAndamento = 0;
    int opt = 0;

    while (opt != 4) {
        menu();
        printf("Escolha uma opcao:\n");
        
        // Uso de 'if' para capturar apenas a opção e ignorar o restante do buffer
        if (scanf("%d", &opt) != 1) {
             printf("Opcao invalida. Tente novamente.\n");
             limpar_buffer();
             continue;
        }
        limpar_buffer(); // Limpa o buffer após ler o inteiro

        if (opt == 1) {
            // --- NOVO JOGO ---
            
            printf("Iniciando Novo Jogo.\n");
            
            // 1. Inicializa o estado do jogo
            estado.rodadas = 0;
            estado.acertos1 = estado.acertos2 = 0;
            estado.erros1 = estado.erros2 = 0;
            estado.jogadorAtual = 1;
            estado.jogoEmAndamento = 1; // O jogo começa agora

            printf("Insira o nome do Jogador 1: ");
            scanf("%49s", estado.jogador1);
            limpar_buffer();
            printf("Insira o nome do Jogador 2: ");
            scanf("%49s", estado.jogador2);
            limpar_buffer();

            initTabuleiro(estado.tabuleiro1);
            initTabuleiro(estado.tabuleiro2);

            // Definição dos navios
            char Navios[3][30] = {"Cruzeiro do Kaka","Charles","Bote"};
            int tamanhoN[3] = {4,3,2};
            char letraN[3] = {'K', 'C', 'B'};

            int linha;
            char cl, dir;

            // 2. Posicionamento dos Navios (Jogador 1 e 2)
            for (int jogador = 1; jogador <= 2; jogador++) {
                char (*tabuleiro_alvo)[N] = (jogador == 1) ? estado.tabuleiro1 : estado.tabuleiro2;
                char *nome_jogador = (jogador == 1) ? estado.jogador1 : estado.jogador2;
                
                printf("\n--- Posicionamento de Navios: %s ---\n", nome_jogador);

                for (int i = 0; i < 3; i++) {
                    int cond = 0;
                    while (!cond) {
                        printTabuleiro(tabuleiro_alvo, 1);
                        printf("\nNavio: %s (Tamanho %d, Letra: %c)\n", Navios[i], tamanhoN[i], letraN[i]);
                        printf("Digite a linha (1-10), coluna (A-J) e direcao (H/V) (Ex: 4 F H): ");
                        
                        // Leitura mais robusta
                        if (scanf("%d %c %c", &linha, &cl, &dir) != 3) {
                            printf("\nEntrada invalida. Use o formato: LINHA COLUNA DIRECAO\n");
                            limpar_buffer();
                            continue;
                        }
                        limpar_buffer(); // Limpa o buffer após a leitura

                        // Conversão e validação
                        int col_idx = toupper(cl) - 'A';
                        char dir_upper = toupper(dir);
                        int lin_idx = linha - 1;

                        cond = posnav(tabuleiro_alvo, tamanhoN[i], dir_upper, lin_idx, col_idx, letraN[i]);

                        if (!cond){
                            printf("\nNao foi possivel posicionar o navio. Verifique limites ou colisoes. Tente novamente.\n\n");
                        } else {
                            printf("Navio posicionado com sucesso.\n");
                        }
                    }
                }
            }
        } 
        
        else if (opt == 2) {
            // --- CONTINUAR JOGO ---
            if (carregarJogo(&estado)) {
                 estado.jogoEmAndamento = 1;
                 printf("Continuando o jogo...\n");
            } else {
                continue; // Volta ao menu se o carregamento falhar
            }
        } 
        
        else if (opt == 3) {
            // --- INSTRUÇÕES ---
            exibirInstrucoes();
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // Espera a tecla Enter
            continue;
        }

        // --- GAME ENGINE (Inicia após Novo Jogo ou Carregar) ---

        if (estado.jogoEmAndamento == 1) {
            
            int lin_ataque;
            char cl_ataque;
            int resultadoatk;
            int fim1; // Flag para navios de J1 afundados
            int fim2; // Flag para navios de J2 afundados

            while (1) {
                
                // Variáveis re-inicializadas a cada rodada (Correção do Erro Crítico 2)
                fim1 = 1; // Assume que todos os navios de J1 afundaram
                fim2 = 1; // Assume que todos os navios de J2 afundaram
                
                resultadoatk = 0;

                // --- VEZ DO JOGADOR ATUAL ---
                
                char *nome_atacante = (estado.jogadorAtual == 1) ? estado.jogador1 : estado.jogador2;
                char (*tabuleiro_alvo)[N] = (estado.jogadorAtual == 1) ? estado.tabuleiro2 : estado.tabuleiro1;

                printf("\n--- Vez de %s (Rodada %d) ---\n", nome_atacante, estado.rodadas + 1);
                printTabuleiro(tabuleiro_alvo, 0); // Mostrar tabuleiro do alvo (escondendo navios)

                do {
                    printf("Digite as coordenadas do alvo (Ex: 4 F): ");
                    if (scanf("%d %c", &lin_ataque, &cl_ataque) != 2) {
                        printf("Entrada invalida. Tente novamente.\n");
                        limpar_buffer();
                        continue;
                    }
                    limpar_buffer();
                    
                    int lin_idx = lin_ataque - 1;
                    int col_idx = toupper(cl_ataque) - 'A';

                    resultadoatk = atacar(tabuleiro_alvo, lin_idx, col_idx);

                    if (resultadoatk == 1 || resultadoatk == 3) { // Acertou ou Afundou
                         if (estado.jogadorAtual == 1) estado.acertos1++;
                         else estado.acertos2++;
                    } else if (resultadoatk == 2) { // Errou
                         if (estado.jogadorAtual == 1) estado.erros1++;
                         else estado.erros2++;
                    }
                    // Se resultadoatk == 0 (Posição já atacada/Inválida), o loop 'do-while' continua.

                } while (resultadoatk == 0);

                // --- VERIFICAÇÃO DE FIM DE JOGO ---
                
                // Percorre ambos os tabuleiros para verificar se sobrou algum navio
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        // Verifica Tabuleiro 1 (do Jogador 1)
                        if (estado.tabuleiro1[i][j] == 'K' || estado.tabuleiro1[i][j] == 'C' || estado.tabuleiro1[i][j] == 'B')
                            fim1 = 0; // Jogo 1 ainda tem navios
                        // Verifica Tabuleiro 2 (do Jogador 2)
                        if (estado.tabuleiro2[i][j] == 'K' || estado.tabuleiro2[i][j] == 'C' || estado.tabuleiro2[i][j] == 'B')
                            fim2 = 0; // Jogo 2 ainda tem navios
                    }
                }

                if (fim1 || fim2) break; // Sai do loop 'while(1)' se alguém perdeu

                // --- ALTERNAR JOGADOR ---
                estado.rodadas++;
                estado.jogadorAtual = (estado.jogadorAtual == 1) ? 2 : 1;
                
                // --- OPÇÃO DE SALVAR ---
                printf("\n(Digite 'S' para salvar o jogo ou pressione ENTER para continuar a rodada %d)\n", estado.rodadas + 1);
                char salva_opt = getchar();
                if (salva_opt == 's' || salva_opt == 'S') {
                    salvarJogo(&estado);
                    estado.jogoEmAndamento = 0; // Sai do loop principal do jogo para voltar ao menu
                    break;
                }
                limpar_buffer(); // Limpa o buffer se apenas ENTER foi pressionado
            } // Fim do while(1)

            // --- FIM DE JOGO (Resultado) ---
            if (estado.jogoEmAndamento == 1) { // Só entra se o jogo realmente terminou, e não foi salvo

                printf("\n\n=============== JOGO ENCERRADO! ===============\n");
                printf("O Jogo acabou apos %d rodadas.\n\n", estado.rodadas);

                if (fim2) {
                    printf("🏆 VENCEDOR: %s 🏆\n", estado.jogador1);
                } else if (fim1) {
                    printf("🏆 VENCEDOR: %s 🏆\n", estado.jogador2);
                } else {
                     // Caso de erro, mas teoricamente o break impede isso
                }

                printf("%s teve %d acertos e %d erros.\n", estado.jogador1, estado.acertos1, estado.erros1);
                printf("%s teve %d acertos e %d erros.\n", estado.jogador2, estado.acertos2, estado.erros2);

                salvarResultados(estado.jogador1, estado.jogador2, estado.acertos1, estado.acertos2, estado.erros1, estado.erros2, estado.rodadas);
                
                estado.jogoEmAndamento = 0; // Finaliza o estado
            }
            
            printf("\nPressione Enter para voltar ao menu...");
            getchar(); // Espera a tecla Enter
        }
    }

    printf("\nObrigado por jogar Batalha Naval. Saindo...\n");
    return 0;
}

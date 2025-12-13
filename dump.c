#include <stdio.h>
#include <stdlib.h>

void menu();

int main() {
    int opt;

    while (1) {
        menu();
        printf("escolha uma opcao: ");
        scanf("%d", &opt);

        if (opt == 1) {
            printf("[ novo jogo ]\n");
            // futuramente: iniciar tabuleiros, pedir nomes, posicionar navios
        } 
        else if (opt == 2) {
            printf("[ continuar jogo ]\n");
            // futuramente: carregar arquivo
        } 
        else if (opt == 3) {
            printf("fechando...\n");
            break;
        } 
        else {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}

void menu() {
    printf("\n===== BATALHA NAVAL =====\n");
    printf("1 - novo jogo\n");
    printf("2 - continuar jogo\n");
    printf("3 - instrucoes\n");
    printf("4 - sair\n");
}

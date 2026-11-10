#include <stdio.h>
#include "estruturas.h"
#include "jogadores.h"
#include "jogos.h"
#include "comunidades.h"
#include "membros.h"
#include "eventos.h"
#include "relatorios.h"
#include "utils.h"

void exibirMenuPrincipal(void) {
    printf("\n===== DESMOZ =====\n");
    printf("1 - Gerenciar jogadores\n");
    printf("2 - Gerenciar jogos\n");
    printf("3 - Gerenciar comunidades\n");
    printf("4 - Gerenciar membros\n");
    printf("5 - Gerenciar eventos\n");
    printf("6 - Consultar relatorios\n");
    printf("0 - Encerrar sistema\n");
}

int main(void) {
    int opcao;

    printf("Bem-vindo ao Desmoz!\n");

    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        opcao = lerInteiro();

        if (opcao == 1) {
            menuJogadores();
        } else if (opcao == 2) {
            menuJogos();
        } else if (opcao == 3) {
            menuComunidades();
        } else if (opcao == 4) {
            menuMembros();
        } else if (opcao == 5) {
            menuEventos();
        } else if (opcao == 6) {
            menuRelatorios();
        } else if (opcao == 0) {
            printf("\nEncerrando Desmoz...\n");
        } else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
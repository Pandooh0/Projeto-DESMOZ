#include <stdio.h>
#include "estruturas.h"
#include "jogadores.h"
#include "jogos.h"
#include "comunidades.h"
#include "membros.h"
#include "eventos.h"
#include "relatorios.h"
#include "utils.h"

static void exibirMenuPrincipal(void) {
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

        switch (opcao) {
            case 1: menuJogadores(); break;
            case 2: menuJogos(); break;
            case 3: menuComunidades(); break;
            case 4: menuMembros(); break;
            case 5: menuEventos(); break;
            case 6: menuRelatorios(); break;
            case 0: printf("\nEncerrando Desmoz...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

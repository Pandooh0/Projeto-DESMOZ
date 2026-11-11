#include <stdio.h>
#include "comunidades.h"
#include "eventos.h"
#include "jogadores.h"
#include "relatorios.h"
#include "utils.h"

static void exibirResumo(void) {
	printf("\n--- RESUMO DO SISTEMA ---\n");
	printf("Jogadores: %d\n", totalDeJogadores());
	printf("Comunidades: %d\n", totalDeComunidades());
	printf("Eventos: %d (%d abertos)\n", totalDeEventos(), contarEventosAbertos());
}

void menuRelatorios(void) {
	int opcao;

	do {
		printf("\n--- RELATORIOS ---\n");
		printf("1 - Resumo\n2 - Jogadores\n3 - Comunidades\n4 - Eventos\n0 - Voltar\n");
		printf("Escolha uma opcao: ");
		opcao = lerNumeroEntre(0, 4);
		switch (opcao) {
			case 1: exibirResumo(); break;
			case 2: listarJogadores(); break;
			case 3: listarComunidades(); break;
			case 4: listarEventos(); break;
		}
	} while (opcao != 0);
}

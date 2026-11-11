#include <stdio.h>
#include "estruturas.h"
#include "comunidades.h"
#include "jogadores.h"
#include "membros.h"
#include "utils.h"

#define MAX_VINCULOS (MAX_JOGADORES * MAX_COMUNIDADES)

static int jogadoresVinculados[MAX_VINCULOS];
static int comunidadesVinculadas[MAX_VINCULOS];
static int totalVinculos = 0;

int ehMembro(int codigoJogador, int codigoComunidade) {
	int i;

	for (i = 0; i < totalVinculos; i++) {
		if (jogadoresVinculados[i] == codigoJogador &&
			comunidadesVinculadas[i] == codigoComunidade) return 1;
	}
	return 0;
}

static int adicionarVinculo(int codigoJogador, int codigoComunidade) {
	if (ehMembro(codigoJogador, codigoComunidade) || totalVinculos >= MAX_VINCULOS)
		return 0;
	jogadoresVinculados[totalVinculos] = codigoJogador;
	comunidadesVinculadas[totalVinculos] = codigoComunidade;
	totalVinculos++;
	return 1;
}

void vincularResponsavel(int codigoJogador, int codigoComunidade) {
	adicionarVinculo(codigoJogador, codigoComunidade);
}

int contarMembros(int codigoComunidade) {
	int i, total = 0;

	for (i = 0; i < totalVinculos; i++)
		if (comunidadesVinculadas[i] == codigoComunidade) total++;
	return total;
}

void listarMembrosDaComunidade(int codigoComunidade) {
	int i, encontrou = 0;

	for (i = 0; i < totalVinculos; i++) {
		if (comunidadesVinculadas[i] == codigoComunidade) {
			printf("- ");
			mostrarNomeJogador(jogadoresVinculados[i]);
			printf("\n");
			encontrou = 1;
		}
	}
	if (!encontrou) printf("Nenhum membro cadastrado nessa comunidade.\n");
}

static void vincularMembro(void) {
	int codigoJogador, codigoComunidade;

	printf("Codigo do jogador: ");
	codigoJogador = lerInteiro();
	if (buscarJogador(codigoJogador) == -1) {
		printf("Jogador nao encontrado.\n");
		return;
	}
	printf("Codigo da comunidade: ");
	codigoComunidade = lerInteiro();
	if (buscarComunidade(codigoComunidade) == -1) {
		printf("Comunidade nao encontrada.\n");
		return;
	}
	if (adicionarVinculo(codigoJogador, codigoComunidade))
		printf("Membro vinculado com sucesso.\n");
	else printf("Esse jogador ja e membro ou o limite de vinculos foi atingido.\n");
}

void menuMembros(void) {
	int opcao, codigoComunidade;

	do {
		printf("\n--- MEMBROS ---\n1 - Vincular jogador a comunidade\n2 - Listar membros da comunidade\n0 - Voltar\n");
		printf("Escolha uma opcao: ");
		opcao = lerNumeroEntre(0, 2);
		if (opcao == 1) vincularMembro();
		if (opcao == 2) {
			printf("Codigo da comunidade: ");
			codigoComunidade = lerInteiro();
			if (buscarComunidade(codigoComunidade) == -1)
				printf("Comunidade nao encontrada.\n");
			else listarMembrosDaComunidade(codigoComunidade);
		}
	} while (opcao != 0);
}
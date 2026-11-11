#include <stdio.h>
#include "estruturas.h"
#include "../src/jogadores.h"
#include "utils.h"

typedef struct {
	int codigo;
	char nome[TAM_TEXTO];
} Jogador;

static Jogador jogadores[MAX_JOGADORES];
static int totalJogadores = 0;

int buscarJogador(int codigo) {
	int i;

	for (i = 0; i < totalJogadores; i++) {
		if (jogadores[i].codigo == codigo) return i;
	}
	return -1;
}

int totalDeJogadores(void) {
	return totalJogadores;
}

void mostrarNomeJogador(int codigo) {
	int pos = buscarJogador(codigo);

	if (pos == -1) printf("(jogador desconhecido)");
	else printf("%s", jogadores[pos].nome);
}

void listarJogadores(void) {
	int i;

	if (totalJogadores == 0) {
		printf("Nenhum jogador cadastrado.\n");
		return;
	}
	for (i = 0; i < totalJogadores; i++)
		printf("%d - %s\n", jogadores[i].codigo, jogadores[i].nome);
}

void cadastrarJogador(void) {
	if (totalJogadores >= MAX_JOGADORES) {
		printf("Limite de jogadores atingido.\n");
		return;
	}

	printf("Nome do jogador: ");
	lerTextoObrigatorio(jogadores[totalJogadores].nome, TAM_TEXTO);
	jogadores[totalJogadores].codigo = totalJogadores + 1;
	printf("Jogador cadastrado! Codigo: %d\n", jogadores[totalJogadores].codigo);
	totalJogadores++;
}

static void buscarJogadorPorCodigo(void) {
	int pos;

	printf("Codigo do jogador: ");
	pos = buscarJogador(lerInteiro());
	if (pos == -1) printf("Jogador nao encontrado.\n");
	else printf("%d - %s\n", jogadores[pos].codigo, jogadores[pos].nome);
}

void menuJogadores(void) {
	int opcao;

	do {
		printf("\n--- JOGADORES ---\n");
		printf("1 - Cadastrar jogador\n2 - Listar jogadores\n3 - Buscar jogador\n0 - Voltar\n");
		printf("Escolha uma opcao: ");
		opcao = lerNumeroEntre(0, 3);
		switch (opcao) {
			case 1: cadastrarJogador(); break;
			case 2: listarJogadores(); break;
			case 3: buscarJogadorPorCodigo(); break;
		}
	} while (opcao != 0);
}

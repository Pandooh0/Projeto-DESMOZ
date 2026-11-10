#include <stdio.h>
#include "estruturas.h"
#include "jogos.h"
#include "utils.h"

Jogo jogos[MAX_JOGOS] = {
    {1,  "Minecraft",         "Sandbox",       "Multiplataforma"},
    {2,  "Fortnite",          "Battle Royale", "Multiplataforma"},
    {3,  "Counter Strike 2",  "FPS",           "PC"},
    {4,  "Valorant",          "FPS tatico",    "PC"},
    {5,  "Overwatch",         "FPS de herois", "Multiplataforma"},
    {6,  "League of Legends", "MOBA",          "PC"},
    {7,  "Roblox",            "Sandbox",       "Multiplataforma"},
    {8,  "Rocket League",     "Esporte",       "Multiplataforma"},
    {9,  "Apex Legends",      "Battle Royale", "Multiplataforma"},
    {10, "Free Fire",         "Battle Royale", "Mobile"},
    {11, "GTA V",             "Acao",          "Multiplataforma"},
    {12, "Dota 2",            "MOBA",          "PC"}
};
int totalJogos = 12;

int buscarJogo(int codigo) {
    int i;

    for (i = 0; i < totalJogos; i++) {
        if (jogos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void mostrarNomeJogo(int codigo) {
    int pos = buscarJogo(codigo);

    if (pos == -1) {
        printf("(jogo desconhecido)");
    } else {
        printf("%s", jogos[pos].nome);
    }
}

void listarJogos(void) {
    int i;

    if (totalJogos == 0) {
        printf("Nenhum jogo cadastrado.\n");
        return;
    }

    for (i = 0; i < totalJogos; i++) {
        printf("%d - %s [%s, %s]\n", jogos[i].codigo, jogos[i].nome,
               jogos[i].genero, jogos[i].plataforma);
    }
}

void cadastrarJogo(void) {
    Jogo novo;
    int i;

    if (totalJogos >= MAX_JOGOS) {
        printf("Limite de jogos atingido.\n");
        return;
    }

    printf("Nome do jogo: ");
    lerTextoObrigatorio(novo.nome, TAM_TEXTO);

    for (i = 0; i < totalJogos; i++) {
        if (textosIguais(jogos[i].nome, novo.nome) == 1) {
            printf("Esse jogo ja esta no catalogo.\n");
            return;
        }
    }

    printf("Genero (ex.: FPS, MOBA, RPG): ");
    lerTextoObrigatorio(novo.genero, TAM_TEXTO);

    printf("Plataforma (ex.: PC, Mobile, Console): ");
    lerTextoObrigatorio(novo.plataforma, TAM_TEXTO);

    novo.codigo = totalJogos + 1;
    jogos[totalJogos] = novo;
    totalJogos++;

    printf("Jogo cadastrado! Codigo: %d\n", novo.codigo);
}

void buscarJogoPorCodigo(void) {
    int pos;

    printf("Codigo do jogo: ");
    pos = buscarJogo(lerInteiro());

    if (pos == -1) {
        printf("Jogo nao encontrado.\n");
        return;
    }

    printf("\nCodigo: %d\n", jogos[pos].codigo);
    printf("Nome: %s\n", jogos[pos].nome);
    printf("Genero: %s\n", jogos[pos].genero);
    printf("Plataforma: %s\n", jogos[pos].plataforma);
}

void alterarJogo(void) {
    int pos;

    printf("Codigo do jogo: ");
    pos = buscarJogo(lerInteiro());

    if (pos == -1) {
        printf("Jogo nao encontrado.\n");
        return;
    }

    printf("Jogo: %s\n", jogos[pos].nome);

    printf("Novo genero: ");
    lerTextoObrigatorio(jogos[pos].genero, TAM_TEXTO);

    printf("Nova plataforma: ");
    lerTextoObrigatorio(jogos[pos].plataforma, TAM_TEXTO);

    printf("Jogo alterado com sucesso!\n");
}

void menuJogos(void) {
    int opcao;

    do {
        printf("\n--- JOGOS ---\n");
        printf("1 - Cadastrar jogo\n");
        printf("2 - Listar jogos\n");
        printf("3 - Buscar jogo\n");
        printf("4 - Alterar jogo\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerNumeroEntre(0, 4);

        if (opcao == 1) {
            cadastrarJogo();
        } else if (opcao == 2) {
            listarJogos();
        } else if (opcao == 3) {
            buscarJogoPorCodigo();
        } else if (opcao == 4) {
            alterarJogo();
        }
    } while (opcao != 0);
}
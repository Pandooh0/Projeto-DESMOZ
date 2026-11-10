#include <stdio.h>
#include "estruturas.h"
#include "comunidades.h"
#include "jogos.h"
#include "jogadores.h"
#include "membros.h"
#include "eventos.h"
#include "utils.h"

Comunidade comunidades[MAX_COMUNIDADES];
int totalComunidades = 0;

int buscarComunidade(int codigo) {
    int i;

    for (i = 0; i < totalComunidades; i++) {
        if (comunidades[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int totalDeComunidades(void) {
    return totalComunidades;
}

void mostrarNomeComunidade(int codigo) {
    int pos = buscarComunidade(codigo);

    if (pos == -1) {
        printf("(comunidade desconhecida)");
    } else {
        printf("%s", comunidades[pos].nome);
    }
}

void listarComunidadesResumido(void) {
    int i;

    for (i = 0; i < totalComunidades; i++) {
        printf("%d - %s\n", comunidades[i].codigo, comunidades[i].nome);
    }
}

void mostrarComunidade(int i) {
    printf("\nCodigo: %d\n", comunidades[i].codigo);
    printf("Nome: %s\n", comunidades[i].nome);
    if (comunidades[i].descricao[0] != '\0') {
        printf("Descricao: %s\n", comunidades[i].descricao);
    }
    printf("Jogo principal: ");
    mostrarNomeJogo(comunidades[i].codJogoPrincipal);
    printf("\nResponsavel: ");
    mostrarNomeJogador(comunidades[i].codResponsavel);
    printf("\nMembros: %d\n", contarMembros(comunidades[i].codigo));
    printf("Eventos: %d\n", contarEventosDaComunidade(comunidades[i].codigo, 0));
}

void listarComunidades(void) {
    int i;

    if (totalComunidades == 0) {
        printf("Nenhuma comunidade cadastrada.\n");
        return;
    }

    for (i = 0; i < totalComunidades; i++) {
        mostrarComunidade(i);
    }
}

int escolherJogoPrincipal(void) {
    int codigo;

    printf("\nJogos disponiveis:\n");
    listarJogos();
    printf("Codigo do jogo principal (0 = cadastrar um novo jogo): ");
    codigo = lerInteiro();

    if (codigo == 0) {
        cadastrarJogo();
        printf("\nJogos disponiveis:\n");
        listarJogos();
        printf("Codigo do jogo principal: ");
        codigo = lerInteiro();
    }

    if (buscarJogo(codigo) == -1) {
        printf("Jogo nao encontrado.\n");
        return 0;
    }
    return codigo;
}

void criarComunidade(void) {
    Comunidade nova;
    int i;
    int codJogo;
    int codResponsavel;

    if (totalComunidades >= MAX_COMUNIDADES) {
        printf("Limite de comunidades atingido.\n");
        return;
    }

    printf("Nome da comunidade: ");
    lerTextoObrigatorio(nova.nome, TAM_TEXTO);

    for (i = 0; i < totalComunidades; i++) {
        if (textosIguais(comunidades[i].nome, nova.nome) == 1) {
            printf("Ja existe uma comunidade com esse nome.\n");
            return;
        }
    }

    printf("Descricao (pode deixar vazia): ");
    lerTexto(nova.descricao, TAM_DESCRICAO);

    codJogo = escolherJogoPrincipal();
    if (codJogo == 0) {
        return;
    }

    printf("Codigo do jogador responsavel: ");
    codResponsavel = lerInteiro();
    if (buscarJogador(codResponsavel) == -1) {
        printf("Jogador nao encontrado. Cadastre o jogador no menu de jogadores primeiro.\n");
        return;
    }

    nova.codigo = totalComunidades + 1;
    nova.codJogoPrincipal = codJogo;
    nova.codResponsavel = codResponsavel;

    comunidades[totalComunidades] = nova;
    totalComunidades++;

    vincularResponsavel(codResponsavel, nova.codigo);

    printf("Comunidade criada! Codigo: %d\n", nova.codigo);
}

void buscarComunidadePorCodigo(void) {
    int pos;

    printf("Codigo da comunidade: ");
    pos = buscarComunidade(lerInteiro());

    if (pos == -1) {
        printf("Comunidade nao encontrada.\n");
        return;
    }
    mostrarComunidade(pos);
}

void alterarComunidade(void) {
    int pos;
    int i;
    Comunidade copia;

    printf("Codigo da comunidade: ");
    pos = buscarComunidade(lerInteiro());

    if (pos == -1) {
        printf("Comunidade nao encontrada.\n");
        return;
    }

    printf("Novo nome: ");
    lerTextoObrigatorio(copia.nome, TAM_TEXTO);

    for (i = 0; i < totalComunidades; i++) {
        if (i != pos && textosIguais(comunidades[i].nome, copia.nome) == 1) {
            printf("Ja existe outra comunidade com esse nome.\n");
            return;
        }
    }

    printf("Nova descricao (pode deixar vazia): ");
    lerTexto(copia.descricao, TAM_DESCRICAO);

    copiarTexto(comunidades[pos].nome, copia.nome);
    copiarTexto(comunidades[pos].descricao, copia.descricao);

    printf("Comunidade alterada com sucesso!\n");
}

void consultarMembros(void) {
    int pos;

    printf("Codigo da comunidade: ");
    pos = buscarComunidade(lerInteiro());

    if (pos == -1) {
        printf("Comunidade nao encontrada.\n");
        return;
    }

    printf("\nMembros de %s:\n", comunidades[pos].nome);
    listarMembrosDaComunidade(comunidades[pos].codigo);
}

void consultarEventos(void) {
    int pos;

    printf("Codigo da comunidade: ");
    pos = buscarComunidade(lerInteiro());

    if (pos == -1) {
        printf("Comunidade nao encontrada.\n");
        return;
    }

    printf("\nEventos de %s:\n", comunidades[pos].nome);
    listarEventosDaComunidade(comunidades[pos].codigo);
}

void menuComunidades(void) {
    int opcao;

    do {
        printf("\n--- COMUNIDADES ---\n");
        printf("1 - Criar comunidade\n");
        printf("2 - Listar comunidades\n");
        printf("3 - Buscar comunidade\n");
        printf("4 - Alterar comunidade\n");
        printf("5 - Consultar membros\n");
        printf("6 - Consultar eventos\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerNumeroEntre(0, 6);

        if (opcao == 1) {
            criarComunidade();
        } else if (opcao == 2) {
            listarComunidades();
        } else if (opcao == 3) {
            buscarComunidadePorCodigo();
        } else if (opcao == 4) {
            alterarComunidade();
        } else if (opcao == 5) {
            consultarMembros();
        } else if (opcao == 6) {
            consultarEventos();
        }
    } while (opcao != 0);
}
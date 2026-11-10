#include <stdio.h>
#include "estruturas.h"
#include "eventos.h"
#include "comunidades.h"
#include "jogadores.h"
#include "membros.h"
#include "utils.h"

Evento eventos[MAX_EVENTOS];
int totalEventos = 0;

// ------------------------------------------------------------------
// Consultas
// ------------------------------------------------------------------
int buscarEvento(int codigo) {
    int i;

    for (i = 0; i < totalEventos; i++) {
        if (eventos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int totalDeEventos(void) {
    return totalEventos;
}

int contarEventosAbertos(void) {
    int i;
    int abertos = 0;

    for (i = 0; i < totalEventos; i++) {
        if (eventos[i].status == ABERTO) {
            abertos++;
        }
    }
    return abertos;
}

int contarEventosDaComunidade(int codComunidade, int i) {
    int total = 0;

    for (; i < totalEventos; i++) {
        if (eventos[i].codComunidade == codComunidade) {
            total++;
        }
    }
    return total;
}

// ------------------------------------------------------------------
// Exibicao
// ------------------------------------------------------------------

void mostrarEvento(int i) {
    printf("\nCodigo: %d\n", eventos[i].codigo);
    printf("Nome: %s\n", eventos[i].nome);
    printf("Comunidade: ");
    mostrarNomeComunidade(eventos[i].codComunidade);
    printf("\n");

    if (eventos[i].tipo == PARTIDA) {
        printf("Tipo: Partida (%d rodadas)\n", eventos[i].extra.numeroRodadas);
    } else {
        printf("Tipo: Encontro (local: %s)\n", eventos[i].extra.local);
    }

    printf("Data: %02d/%02d/%d\n", eventos[i].dia, eventos[i].mes, eventos[i].ano);
    printf("Participantes: %d/%d\n", eventos[i].totalInscritos, eventos[i].limite);

    if (eventos[i].status == ABERTO) {
        printf("Situacao: Aberto\n");
    } else {
        printf("Situacao: Cancelado\n");
    }
}

void listarEventos(void) {
    int i;

    if (totalEventos == 0) {
        printf("Nenhum evento cadastrado.\n");
        return;
    }

    for (i = 0; i < totalEventos; i++) {
        mostrarEvento(i);
    }
}

void listarEventosDaComunidade(int codComunidade) {
    int i;
    int achou = 0;

    for (i = 0; i < totalEventos; i++) {
        if (eventos[i].codComunidade == codComunidade) {
            mostrarEvento(i);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Essa comunidade ainda nao tem eventos.\n");
    }
}

void listarParticipantesDoEvento(int codEvento) {
    int pos = buscarEvento(codEvento);
    int i;

    if (pos == -1) {
        printf("Evento nao encontrado.\n");
        return;
    }

    printf("Participantes de %s (%d/%d):\n", eventos[pos].nome,
           eventos[pos].totalInscritos, eventos[pos].limite);

    if (eventos[pos].totalInscritos == 0) {
        printf("Ainda nao ha participantes.\n");
        return;
    }

    for (i = 0; i < eventos[pos].totalInscritos; i++) {
        printf("- ");
        mostrarNomeJogador(eventos[pos].inscritos[i]);
        printf("\n");
    }
}

// ------------------------------------------------------------------
// Criar evento
// ------------------------------------------------------------------

int escolherComunidadeDoEvento(void) {
    int codigo;

    if (totalDeComunidades() == 0) {
        printf("Nenhuma comunidade cadastrada.\n");
        if (perguntarSimNao("Deseja criar uma comunidade agora?") == 0) {
            return 0;
        }
        criarComunidade();
        if (totalDeComunidades() == 0) {
            return 0;
        }
    }

    printf("\nComunidades:\n");
    listarComunidadesResumido();
    printf("Codigo da comunidade organizadora (0 = criar uma nova): ");
    codigo = lerInteiro();

    if (codigo == 0) {
        criarComunidade();
        printf("\nComunidades:\n");
        listarComunidadesResumido();
        printf("Codigo da comunidade organizadora: ");
        codigo = lerInteiro();
    }

    if (buscarComunidade(codigo) == -1) {
        printf("Comunidade nao encontrada.\n");
        return 0;
    }
    return codigo;
}

void criarEvento(void) {
    Evento novo;
    int codComunidade;

    if (totalEventos >= MAX_EVENTOS) {
        printf("Limite de eventos atingido.\n");
        return;
    }

    codComunidade = escolherComunidadeDoEvento();
    if (codComunidade == 0) {
        return;
    }

    printf("Nome do evento: ");
    lerTextoObrigatorio(novo.nome, TAM_TEXTO);

    printf("Tipo do evento (1 = Partida, 2 = Encontro): ");
    novo.tipo = lerNumeroEntre(1, 2);

    if (novo.tipo == PARTIDA) {
        printf("Numero de rodadas (1 a 20): ");
        novo.extra.numeroRodadas = lerNumeroEntre(1, 20);
    } else {
        printf("Local do encontro: ");
        lerTextoObrigatorio(novo.extra.local, TAM_TEXTO);
    }

    printf("Data do evento:\n");
    lerData(&novo.dia, &novo.mes, &novo.ano);

    printf("Limite de participantes (1 a %d): ", MAX_INSCRITOS);
    novo.limite = lerNumeroEntre(1, MAX_INSCRITOS);

    novo.codigo = totalEventos + 1;
    novo.codComunidade = codComunidade;
    novo.totalInscritos = 0;
    novo.status = ABERTO;

    eventos[totalEventos] = novo;
    totalEventos++;

    printf("Evento criado! Codigo: %d\n", novo.codigo);
}

// ------------------------------------------------------------------
// Demais operacoes
// ------------------------------------------------------------------

void buscarEventoPorCodigo(void) {
    int pos;

    printf("Codigo do evento: ");
    pos = buscarEvento(lerInteiro());

    if (pos == -1) {
        printf("Evento nao encontrado.\n");
        return;
    }
    mostrarEvento(pos);
}

int haEventos(void) {
    if (totalEventos > 0) {
        return 1;
    }
    printf("Nenhum evento cadastrado.\n");
    if (perguntarSimNao("Deseja criar um evento agora?") == 1) {
        criarEvento();
    }
    return 0;
}

void registrarParticipacao(void) {
    int e;
    int codJogador;
    int i;

    if (haEventos() == 0) {
        return;
    }

    printf("Codigo do evento: ");
    e = buscarEvento(lerInteiro());
    if (e == -1) {
        printf("Evento nao encontrado.\n");
        return;
    }
    if (eventos[e].status == CANCELADO) {
        printf("Esse evento foi cancelado.\n");
        return;
    }

    printf("Codigo do jogador: ");
    codJogador = lerInteiro();
    if (buscarJogador(codJogador) == -1) {
        printf("Jogador nao encontrado.\n");
        return;
    }
    if (ehMembro(codJogador, eventos[e].codComunidade) == 0) {
        printf("O jogador precisa ser membro da comunidade do evento.\n");
        return;
    }

    for (i = 0; i < eventos[e].totalInscritos; i++) {
        if (eventos[e].inscritos[i] == codJogador) {
            printf("Esse jogador ja esta inscrito no evento.\n");
            return;
        }
    }

    if (eventos[e].totalInscritos >= eventos[e].limite) {
        printf("O evento ja esta lotado.\n");
        return;
    }

    eventos[e].inscritos[eventos[e].totalInscritos] = codJogador;
    eventos[e].totalInscritos++;

    printf("Participacao registrada!\n");
}

void consultarParticipantes(void) {
    if (haEventos() == 0) {
        return;
    }

    printf("Codigo do evento: ");
    listarParticipantesDoEvento(lerInteiro());
}

void cancelarEvento(void) {
    int e;

    if (haEventos() == 0) {
        return;
    }

    printf("Codigo do evento: ");
    e = buscarEvento(lerInteiro());
    if (e == -1) {
        printf("Evento nao encontrado.\n");
        return;
    }
    if (eventos[e].status == CANCELADO) {
        printf("Esse evento ja estava cancelado.\n");
        return;
    }

    eventos[e].status = CANCELADO;
    printf("Evento cancelado.\n");
}

void menuEventos(void) {
    int opcao;

    do {
        printf("\n--- EVENTOS ---\n");
        printf("1 - Criar evento\n");
        printf("2 - Listar eventos\n");
        printf("3 - Buscar evento\n");
        printf("4 - Registrar participacao\n");
        printf("5 - Consultar participantes\n");
        printf("6 - Cancelar evento\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerNumeroEntre(0, 6);

        if (opcao == 1) {
            criarEvento();
        } else if (opcao == 2) {
            listarEventos();
        } else if (opcao == 3) {
            buscarEventoPorCodigo();
        } else if (opcao == 4) {
            registrarParticipacao();
        } else if (opcao == 5) {
            consultarParticipantes();
        } else if (opcao == 6) {
            cancelarEvento();
        }
    } while (opcao != 0);
}
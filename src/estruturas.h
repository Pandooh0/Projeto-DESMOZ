#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_JOGOS       30
#define MAX_JOGADORES   100
#define MAX_COMUNIDADES 10
#define MAX_EVENTOS     20
#define MAX_INSCRITOS   10
#define TAM_TEXTO       30
#define TAM_DESCRICAO   60
#define TAM_LINHA       100

typedef enum { ABERTO, CANCELADO } StatusEvento;
typedef enum { PARTIDA = 1, ENCONTRO = 2 } TipoEvento;

typedef union {
    int numeroRodadas;
    char local[TAM_TEXTO];
} DadoExtra;

typedef struct {
    int codigo;
    char nome[TAM_TEXTO];
    char genero[TAM_TEXTO];
    char plataforma[TAM_TEXTO];
} Jogo;

typedef struct {
    int codigo;
    char nome[TAM_TEXTO];
    char descricao[TAM_DESCRICAO];
    int codJogoPrincipal;
    int codResponsavel;
} Comunidade;

typedef struct {
    int codigo;
    char nome[TAM_TEXTO];
    int codComunidade;
    int dia, mes, ano;
    int limite;
    int totalInscritos;
    int inscritos[MAX_INSCRITOS];
    StatusEvento status;
    TipoEvento tipo;
    DadoExtra extra;
} Evento;

int dataValida(int dia, int mes, int ano);

#endif

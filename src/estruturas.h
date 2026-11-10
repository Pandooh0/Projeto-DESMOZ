/*
 * estruturas.h
 * Constantes e tipos usados pelos modulos jogos, comunidades e eventos.
 * Se voce ja tem um estruturas.h, acrescente apenas o que estiver faltando.
 */
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_JOGOS       30
#define MAX_COMUNIDADES 10
#define MAX_EVENTOS     20
#define MAX_INSCRITOS   10    // maximo de participantes por evento
#define TAM_TEXTO       30    // nomes, generos, plataformas, local
#define TAM_DESCRICAO   60
#define TAM_LINHA       100   // texto lido do teclado

typedef enum { ABERTO, CANCELADO } StatusEvento;
typedef enum { PARTIDA = 1, ENCONTRO = 2 } TipoEvento;

// UNION: os campos compartilham a mesma memoria.
// Partida usa numeroRodadas; Encontro usa local. So um deles vale por evento.
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
    int codResponsavel;      // codigo do jogador responsavel
} Comunidade;

typedef struct {
    int codigo;
    char nome[TAM_TEXTO];
    int codComunidade;
    int dia, mes, ano;
    int limite;                      // maximo de participantes
    int totalInscritos;
    int inscritos[MAX_INSCRITOS];    // codigos dos jogadores inscritos
    StatusEvento status;
    TipoEvento tipo;
    DadoExtra extra;
} Evento;

#endif
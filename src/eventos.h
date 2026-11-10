/*
 * eventos.h
 * Criacao de eventos e inscricao de participantes.
 */
#ifndef EVENTOS_H
#define EVENTOS_H

void menuEventos(void);
void criarEvento(void);

// Devolve a posicao do evento no vetor, ou -1 se nao existir
int  buscarEvento(int codigo);
int  totalDeEventos(void);
int  contarEventosAbertos(void);

// RECURSIVA: conta os eventos de uma comunidade (chame com i = 0)
int  contarEventosDaComunidade(int codComunidade, int i);

// Usadas por comunidades.c e relatorios.c
void listarEventosDaComunidade(int codComunidade);
void listarParticipantesDoEvento(int codEvento);

#endif
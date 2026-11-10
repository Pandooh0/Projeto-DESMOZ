/*
 * comunidades.h
 * Criacao e consulta de comunidades.
 */
#ifndef COMUNIDADES_H
#define COMUNIDADES_H

void menuComunidades(void);
void criarComunidade(void);
void listarComunidades(void);
void listarComunidadesResumido(void);      // so codigo e nome

// Devolve a posicao da comunidade no vetor, ou -1 se nao existir
int  buscarComunidade(int codigo);
int  totalDeComunidades(void);
// Mostra o nome da comunidade na tela (usado por outros modulos)
void mostrarNomeComunidade(int codigo);

#endif
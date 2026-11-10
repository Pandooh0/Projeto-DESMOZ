/*
 * jogos.h
 * Catalogo de jogos. Ja vem com os jogos mais famosos cadastrados.
 */
#ifndef JOGOS_H
#define JOGOS_H

void menuJogos(void);
void cadastrarJogo(void);
void listarJogos(void);

// Devolve a posicao do jogo no vetor, ou -1 se o codigo nao existir
int  buscarJogo(int codigo);
// Mostra o nome do jogo na tela (usado por outros modulos)
void mostrarNomeJogo(int codigo);

#endif
#ifndef JOGADORES_H
#define JOGADORES_H

#ifndef MAX_JOGADORES
#define MAX_JOGADORES 100
#endif

void menuJogadores(void);
void cadastrarJogador(void);
void listarJogadores(void);
int buscarJogador(int codigo);
int totalDeJogadores(void);
void mostrarNomeJogador(int codigo);

#endif

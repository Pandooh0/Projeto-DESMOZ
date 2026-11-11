#ifndef MEMBROS_H
#define MEMBROS_H

void menuMembros(void);
void vincularResponsavel(int codigoJogador, int codigoComunidade);
int ehMembro(int codigoJogador, int codigoComunidade);
int contarMembros(int codigoComunidade);
void listarMembrosDaComunidade(int codigoComunidade);

#endif

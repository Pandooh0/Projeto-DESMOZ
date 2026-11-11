/*
 * utils.h
 * Funcoes de leitura e de texto usadas por todos os modulos.
 */
#ifndef UTILS_H
#define UTILS_H

void lerTexto(char destino[], int tamanho);
void lerTextoObrigatorio(char destino[], int tamanho);

int  textoParaInteiro(char texto[], int *numero);
int  lerInteiro(void);
int  lerNumeroEntre(int min, int max);
int  perguntarSimNao(char pergunta[]);

int  diasNoMes(int mes, int ano);
void lerData(int *dia, int *mes, int *ano);

#endif

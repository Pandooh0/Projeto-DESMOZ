/*
 * utils.h
 * Funcoes de leitura e de texto usadas por todos os modulos.
 */
#ifndef UTILS_H
#define UTILS_H

int  temFimDeLinha(char texto[]);
void lerTexto(char destino[], int tamanho);
void lerTextoObrigatorio(char destino[], int tamanho);
int  textosIguais(char a[], char b[]);
void copiarTexto(char destino[], char origem[]);

int  textoParaInteiro(char texto[], int *numero);
int  lerInteiro(void);
int  lerNumeroEntre(int min, int max);
int  perguntarSimNao(char pergunta[]);

int  diasNoMes(int mes, int ano);
void lerData(int *dia, int *mes, int *ano);

#endif
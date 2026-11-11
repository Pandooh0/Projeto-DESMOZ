#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "utils.h"

int entradaAcabou = 0;

// Texto (strings sao vetores de char terminados por '\0')

void lerTexto(char destino[], int tamanho) {
    char linha[TAM_LINHA];
    size_t comprimento;

    if (tamanho <= 0) return;

    if (fgets(linha, TAM_LINHA, stdin) == NULL) {
        entradaAcabou = 1;
        destino[0] = '\0';
        return;
    }

    comprimento = strcspn(linha, "\n");
    if (comprimento >= (size_t)tamanho) comprimento = (size_t)tamanho - 1;
    memcpy(destino, linha, comprimento);
    destino[comprimento] = '\0';

    if (strchr(linha, '\n') == NULL) {
        while (fgets(linha, TAM_LINHA, stdin) != NULL && strchr(linha, '\n') == NULL) {
        }
    }
}

void lerTextoObrigatorio(char destino[], int tamanho) {
    lerTexto(destino, tamanho);
    while (destino[0] == '\0' && entradaAcabou == 0) {
        printf("Este campo nao pode ficar vazio. Digite novamente: ");
        lerTexto(destino, tamanho);
    }
}

// Numeros

int textoParaInteiro(char texto[], int *numero) {
    size_t tamanho = strlen(texto);

    if (tamanho == 0 || tamanho > 9 || strspn(texto, "0123456789") != tamanho)
        return 0;

    *numero = (int)strtol(texto, NULL, 10);
    return 1;
}

int lerInteiro(void) {
    char texto[TAM_LINHA];
    int numero = 0;

    lerTexto(texto, TAM_LINHA);
    while (textoParaInteiro(texto, &numero) == 0 && entradaAcabou == 0) {
        printf("Entrada invalida. Digite um numero: ");
        lerTexto(texto, TAM_LINHA);
    }
    return numero;
}

int lerNumeroEntre(int min, int max) {
    int numero = lerInteiro();

    while ((numero < min || numero > max) && entradaAcabou == 0) {
        printf("Digite um numero entre %d e %d: ", min, max);
        numero = lerInteiro();
    }
    return numero;
}

// Faz uma pergunta e devolve 1 (sim) ou 0 (nao)
int perguntarSimNao(char pergunta[]) {
    printf("%s (1 = sim, 0 = nao): ", pergunta);
    return lerNumeroEntre(0, 1);
}

// Datas

int diasNoMes(int mes, int ano) {
    static const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes < 1 || mes > 12 || ano < 1) {
        return 0;
    }

    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) {
        return 29;
    }
    return dias[mes - 1];
}

void lerData(int *dia, int *mes, int *ano) {
    int valida = 0;

    while (valida == 0 && entradaAcabou == 0) {
        printf("  Dia: ");
        *dia = lerNumeroEntre(1, 31);
        printf("  Mes: ");
        *mes = lerNumeroEntre(1, 12);
        printf("  Ano (2024 a 2100): ");
        *ano = lerNumeroEntre(2024, 2100);

        if (dataValida(*dia, *mes, *ano)) {
            valida = 1;
        } else {
            printf("Data invalida. Digite novamente.\n");
        }
    }
}

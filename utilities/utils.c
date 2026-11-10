#include <stdio.h>
#include "estruturas.h"
#include "utils.h"

int entradaAcabou = 0;

// ------------------------------------------------------------------
// Texto (strings sao vetores de char terminados por '\0')
// ------------------------------------------------------------------

int temFimDeLinha(char texto[]) {
    int i = 0;

    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            return 1;
        }
        i++;
    }
    return 0;
}

void lerTexto(char destino[], int tamanho) {
    char linha[TAM_LINHA];
    int i = 0;
    int copiados = 0;
    int fimDeLinha = 0;

    if (fgets(linha, TAM_LINHA, stdin) == NULL) {
        entradaAcabou = 1;
        destino[0] = '\0';
        return;
    }

    while (linha[i] != '\0') {
        if (linha[i] == '\n') {
            fimDeLinha = 1;
            break;
        }
        if (copiados < tamanho - 1) {
            destino[copiados] = linha[i];
            copiados++;
        }
        i++;
    }
    destino[copiados] = '\0';

    if (fimDeLinha == 0) {
        while (fgets(linha, TAM_LINHA, stdin) != NULL && temFimDeLinha(linha) == 0) {
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

int textosIguais(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    if (a[i] == b[i]) {    
        return 1;
    }
    return 0;
}

void copiarTexto(char destino[], char origem[]) {
    int i = 0;

    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

// ------------------------------------------------------------------
// Numeros
// ------------------------------------------------------------------

int textoParaInteiro(char texto[], int *numero) {
    int i = 0;
    int resultado = 0;

    if (texto[0] == '\0') {
        return 0;
    }
    while (texto[i] != '\0') {
        if (texto[i] < '0' || texto[i] > '9') {
            return 0;             
        }
        if (i >= 9) {
            return 0;            
        }
        resultado = resultado * 10 + (texto[i] - '0');
        i++;
    }
    *numero = resultado;
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

// ------------------------------------------------------------------
// Datas
// ------------------------------------------------------------------

int diasNoMes(int mes, int ano) {
    static const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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

        if (*dia <= diasNoMes(*mes, *ano)) {
            valida = 1;
        } else {
            printf("Data invalida: esse mes nao tem %d dias. Digite novamente.\n", *dia);
        }
    }
}
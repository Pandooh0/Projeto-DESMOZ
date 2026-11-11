#include "estruturas.h"
#include "utils.h"

int dataValida(int dia, int mes, int ano) {
    int totalDias;

    if (dia < 1 || mes < 1 || mes > 12 || ano < 1) {
        return 0;
    }

    totalDias = diasNoMes(mes, ano);
    return totalDias > 0 && dia <= totalDias;
}
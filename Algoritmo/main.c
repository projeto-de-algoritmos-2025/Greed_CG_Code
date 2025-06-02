#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

struct Atividade {
    char nome[50];
    int duracao;
    struct tm data;
    int deadline;
    int inicio;
    int fim;
    int atraso;
};

time_t lerData() {
    int dia, mes, ano;
    scanf("%d %d %d", &dia, &mes, &ano);

    struct tm data = {0};
    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;

    return mktime(&data);
}

int main() {
    struct Atividade atividades[MAX];
    int n;
    time_t inicioSemestre, fimSemestre;

    printf("Data de Inicio do Semestre:\n");
    inicioSemestre = lerData();

    printf("Data de Fim do Semestre:\n");
    fimSemestre = lerData();

    printf("Quantas atividades deseja cadastrar? ");
    scanf("%d", &n);

    return 0;
}

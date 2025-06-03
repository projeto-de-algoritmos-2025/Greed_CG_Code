// Minimize Lateness (Genilson Silva e Carlos Eduardo)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("  Digite a data (dd mm aaaa): ");
    scanf("%d %d %d", &dia, &mes, &ano);
    struct tm data = {0};
    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;
    return mktime(&data);
}

int diasEntre(time_t inicio, time_t fim) {
    double segundos = difftime(fim, inicio);
    return (int)(segundos / (60 * 60 * 24));
}

int comparar(const void *a, const void *b) {
    struct Atividade *x = (struct Atividade *)a;
    struct Atividade *y = (struct Atividade *)b;
    return x->deadline - y->deadline;
}

void formatarData(time_t t, char *buffer) {
    struct tm *data = localtime(&t);
    strftime(buffer, 20, "%d/%m/%Y", data);
}

int main() {
    struct Atividade atividades[MAX];
    int n, i;
    time_t inicioSemestre, fimSemestre;

    system("cls");
    printf("\n========================================================\n");
    printf("  AGENDADOR DE ATIVIDADES - Minimize Maximum Lateness\n");
    printf("========================================================\n");
    printf("\n  Defina o periodo do semestre:\n");
    printf("-----------------------------------------\n");
    printf("  Data de Inicio do Semestre:\n");
    inicioSemestre = lerData();
    printf("  Data de Fim do Semestre:\n");
    fimSemestre = lerData();

    printf("-----------------------------------------\n");
    printf("\n  Quantas atividades deseja cadastrar? ");
    scanf("%d", &n);
    getchar();

    system("cls");
    printf("\n==========================\n");
    printf("  CADASTRO DE ATIVIDADES               \n");
    printf("==========================\n");

    for (i = 0; i < n; i++) {
        printf("\n  Atividade %d:\n", i + 1);
        printf("  --------------------\n");
        printf("  Nome: ");
        fgets(atividades[i].nome, sizeof(atividades[i].nome), stdin);
        atividades[i].nome[strcspn(atividades[i].nome, "\n")] = '\0';
        printf("\n  Data da atividade (Deadline)\n");
        time_t data = lerData();
        atividades[i].data = *localtime(&data);
        printf("  Duracao (em dias): ");
        scanf("%d", &atividades[i].duracao);
        getchar();
        atividades[i].deadline = diasEntre(inicioSemestre, data);
    }

    system("cls");
    printf("\n=========================================\n");
    printf("  PROCESSANDO AGENDA (EDF)             \n");
    printf("=========================================\n");

    qsort(atividades, n, sizeof(struct Atividade), comparar);

    int tempoAtual = 0;

    for (i = 0; i < n; i++) {
        atividades[i].inicio = tempoAtual;
        atividades[i].fim = tempoAtual + atividades[i].duracao;
        atividades[i].atraso = (atividades[i].fim > atividades[i].deadline) ?
                               (atividades[i].fim - atividades[i].deadline) : 0;
        tempoAtual = atividades[i].fim;
    }

    system("cls");
    printf("\n=========================================\n");
    printf("  AGENDA FINAL - RESULTADOS            \n");
    printf("=========================================\n");

    printf("%-20s | %14s | %7s | %14s | %6s | %3s | %6s\n",
           "Atividade", "Data Original", "Duracao", "Deadline(dias)", "Inicio", "Fim", "Atraso");
    printf("------------------------------------------------------------------------------------\n");

    char buffer[20];

    for (i = 0; i < n; i++) {
        formatarData(mktime(&atividades[i].data), buffer);
        printf("%-20s | %14s | %7d | %14d | %6d | %3d | %6d\n",
            atividades[i].nome,
            buffer,
            atividades[i].duracao,
            atividades[i].deadline,
            atividades[i].inicio,
            atividades[i].fim,
            atividades[i].atraso);
    }

    printf("------------------------------------------------------------------------------------\n");
    printf("\n  Agendamento concluido com sucesso!\n");
    printf("=========================================\n");
    printf("\n  Pressione ENTER para sair...");
    getchar();
    getchar();

    return 0;
}

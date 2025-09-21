//manutencao.h

#ifndef MANUTENCAO_H
#define MANUTENCAO_H
#include "Veiculo.h"
#include "Servico.h"
#include "data.h"

typedef struct{
    Servico dados;
    char status[20];
}Manutencao;

typedef struct elemen{
    Manutencao dados;
    struct elemen *prox;
}Elemenu;

typedef Elemenu *Lista3;

Lista3 *criar_lista3();
int inserirFinalAgenda(Lista3 *lista3, Manutencao m);
void dataAtual(int *dia, int *mes, int *ano);
int compara_datas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2);
int ordenar(Lista3 *lista);
int Atualizar_status(Lista3 *lista3);
int listar_Prox(Lista3 *lista3);
int SalvarArquivoManu(Lista3 *lista, const char *manutencoes);
int CarregarManutencoes(Lista3 *lista, const char *manutencoes);
int ExcluirManutencoes(Lista3 *lista);


#endif
//Serviço.h
#ifndef SERVICO_H
#define SERVICO_H
#include "data.h"//puxa data.h para ser usada por mais arquivos, para nao criar uma dependencia

typedef struct{
    int id;
    char servico[30], obs[100],modelo[20], placa[20];
    Data dataManu;
    int kmAtual;
    int id_veiculo;
    Data proxManu;
}Servico;

typedef struct elemento2{
    Servico dados;
    struct elemento2 *prox;
}Elem2;

typedef Elem2* Lista2;

Lista2 *criar_listaServ();
int inserir_serv_comeco(Lista2 *lista2, Servico dados, int *idServ, Lista2 *historicoServ);
int Inserir_finalServ(Lista2 *lista, Servico dados);
int Listar_Servicos(Lista2 *lista);
Data proxData(Data atual, int meses);
int SalvarArquivosServico(Lista2 *lista, const char *servicos);
int CarregarArquivosServ(Lista2 *lista, const char *servicos, int *idServ);
int ExcluirServ(Lista2 *lista, int id);
int LimparServico(Lista2 *lista, int *idServ);
int LimparHistorico(Lista2 *lista);
int EditarServicos(Lista2 *lista);

#endif
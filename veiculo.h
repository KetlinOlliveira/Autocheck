//Veiculo.h
#ifndef VEICULO_H
#define VEICULO_H

typedef struct{
    int id_veiculo, anoFabricacao;
    char modelo[30], placa[20];
    int km;
}Veiculo; //Struct para veiculos

typedef struct elemento{
    Veiculo dados;
    struct elemento *prox;
}Elem;

typedef Elem* Lista;

Lista *criar_lista();
int CadastrarVeiculo(Lista *lista, Lista *historico, int *idCont);
int Inserir_comecoVeiculo(Lista *lista, Veiculo dados, int *idCont, Lista *historico);
int Inserir_final(Lista *lista, Veiculo dados);
int CarregarArquivosVeic(Lista *lista, const char *veiculos, int *idCont);
int Listar_veiculos(Lista *lista);
int Consulta_veic(Lista *lista);
int Excluir_Veic(Lista *lista, int id);
int Salvar_arquivos_Veiculos(Lista *lista,const char *veiculos);
Veiculo *buscarVeic(Lista *lista, int id);
int LimparVeic(Lista *lista, int *idCont);
int editar_veic(Lista *lista);
int ExcluirHistoricoVeic(Lista *lista);
int ordenarVeiculos(Lista *lista);


#endif
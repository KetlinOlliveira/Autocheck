//Veiculo.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veiculo.h"

Lista *criar_lista(){
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if(lista)
    *lista = NULL;
    return lista;
} //cria a lista para os veiculos

//faz o cadastro do Veiculo
int CadastrarVeiculo(Lista *lista, Lista *historico, int *idCont){
Veiculo dados;
    system("cls");
        printf("_________________________________\n");
        printf("Modelo do Veiculo: ");
         scanf(" %[^\n]s", dados.modelo);
        printf("Placa: ");
         scanf(" %[^\n]s", dados.placa);
        printf("Ano de Fabricacao: ");
         scanf("%d", &dados.anoFabricacao);
        printf("Km do Veiculo: ");
         scanf("%d", &dados.km);

        if(Inserir_comecoVeiculo(lista, dados, idCont, historico)){
            system("cls");
            printf("Veiculo Cadastrado com sucesso!\n");
        }else{
            system("cls");
            printf("Falha ao Cadastrar\n");
            return 0;
        }
    return 1;

}

//insere os veiculos no começo da lista e do Historico
int Inserir_comecoVeiculo(Lista *lista, Veiculo dados, int *idCont, Lista *historico){
    if(!lista) return 0;
    Elem *no = (Elem *)malloc(sizeof(Elem));
    Elem *no_historico = (Elem *)malloc(sizeof(Elem));
    if(!no || !no_historico) return 0;
    
    no->dados = dados;
  
    no->prox = *lista;
    *lista = no;

    no_historico->dados = dados;
    no_historico->prox = *historico;
    *historico = no_historico;
    no->dados.id_veiculo = no_historico->dados.id_veiculo = (*idCont)++;//Faz com que todos os veiculos tenham um ID unico
   
    return 1;
}

//Inserir no final na lista
int Inserir_final(Lista *lista, Veiculo dados){
    if(!lista) return 0;
    Elem *no =  (Elem *)malloc(sizeof(Elem));
    if(!no  )return 0;
    no->dados = dados;
   
    no->prox = NULL;

    if(*lista == NULL){
        *lista = no; 
    }else{
        Elem *aux = *lista;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    
    }

  return 1;
}
int ordenarVeiculos(Lista *lista){
    if(!lista) return 0;  
    int troca;
    Elem *atual, *prox;
    Veiculo temp;

    do{
    troca =0;     
    atual =*lista;      

        while(atual->prox != NULL){
        prox = atual->prox; 
            // Se o ID do veículo atual for maior que o do próximo, faz troca
            if(atual->dados.id_veiculo > prox->dados.id_veiculo){
                temp = atual->dados;
                atual->dados =prox->dados;
                prox->dados =temp;
                troca =1; 
            }
            atual =atual->prox;
        }
    }while(troca); //repete até que não tenha mais trocas
    return 1;
}

//Lista todos os veiculos cadastrados
int Listar_veiculos(Lista *lista){
    if(lista == NULL || *lista == NULL){
        printf("Cadastre ao menos um Veiculo antes!\n");
        return 0;
    }
    Elem *no = *lista;

    ordenarVeiculos(lista);
    system("cls");
    printf("_________________________________________\n");
    printf("         Veiculos Cadastrados\n");
    while(no != NULL){
        printf("Id unico: %d\n", no->dados.id_veiculo);
        printf("Modelo: %s | Placa: %s | Ano Fabricacao: %d | Km: %d\n\n", no->dados.modelo, no->dados.placa, no->dados.anoFabricacao, no->dados.km);
        no = no->prox;
    }
    printf("___________________________________________\n\n");
return 1;
}

//Consulta o Veiculo por ID
int Consulta_veic(Lista *lista){
    if(!lista){
        printf("Cadastre ao menos 1 Veiculo antes da consulta!\n");
        return 0;
    }
    int op;
    int encontrado = 0;
    system("cls");
    printf("Informe o Id buscado: \n");
     scanf("%d", &op);

    Elem *no = *lista;
    while(no != NULL){
        if(no->dados.id_veiculo == op){
            printf("Veiculo de ID %d encontrado:\n ", op);
            printf("Modelo: %s | Placa: %s | Ano Fabricacao: %d | Km: %d\n\n", no->dados.modelo, no->dados.placa, no->dados.anoFabricacao, no->dados.km);
            encontrado = 1;
        }
    no = no->prox;
    }
     if(encontrado == 0){
        printf("Nenhum Veiculo encontrado com o ID infomado\n");
        return 0;
     }
   return 1; 
}

//Exclui um Veiculo especifico por id
int Excluir_Veic(Lista *lista, int id){
    if(!lista){
        printf("Cadastre ao menos 1 Veiculo antes de Excluir!\n");
        return 0;
    }
    Elem *anterior = NULL;
    Elem *atual = *lista;

    while(atual != NULL && atual->dados.id_veiculo != id){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual == NULL)
        return 0;
    
    if(anterior == NULL)
        *lista = atual->prox;
    else
        anterior->prox = atual->prox;
    free(atual);
    return 1;
    
}
//Salva todos os arquivos
int Salvar_arquivos_Veiculos(Lista *lista, const char *veiculos){
    if(!lista){
        printf("Nao tem Dados para serem Salvos!\n");
        return 0;
    }
    FILE *arquivo = fopen(veiculos, "w");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    Elem *no = *lista;
    while(no != NULL){
        fprintf(arquivo, "%d;%s;%s;%d;%d\n", no->dados.id_veiculo, no->dados.modelo, no->dados.placa, no->dados.anoFabricacao, no->dados.km);
        no = no->prox;
    }

fclose(arquivo);

return 1;
}

//Carrega os Arquivos ao abrir o programa
int CarregarArquivosVeic(Lista *lista, const char *veiculos, int *idCont ){
if(lista == NULL){
    printf("Falha ao Carregar arquivos de Veiculo!\n");
    return 0;
}
FILE *arquivo = fopen(veiculos, "r");
int maiorId = 0;

char linha[200]; //define uma variavel char para ler linha por linha do arquivo
    while(fgets(linha, sizeof(linha), arquivo)!=NULL){
         Veiculo v; 

        if(sscanf(linha, "%d;%29[^;];%19[^;];%d;%d\n", &v.id_veiculo, v.modelo, v.placa, &v.anoFabricacao, &v.km)== 5){
            Inserir_final(lista, v);

            if(v.id_veiculo> maiorId){ //Verifica qual o maior ID
                maiorId = v.id_veiculo;
            }
    }
    
    }
*idCont = maiorId + 1; //Diz qual proximo ID esta disponivel 
fclose(arquivo);

return 1;
}
 //Faz a busca do Veiculo
Veiculo *buscarVeic(Lista *lista, int id){
    if(!lista) return NULL;

    Elem *no = *lista;
    while(no != NULL){
        if(no->dados.id_veiculo == id){
            return  &(no->dados);
        }
    no = no->prox;
    }
 return NULL;
}
//Limpa toda a lista
int LimparVeic(Lista *lista, int *idCont){
    if(*lista != NULL){
        Elem *aux;
        while((*lista) != NULL){
            aux = *lista;
            *lista = (*lista)->prox;
            free(aux);
        }
    }
        printf(" Limpos com sucesso!\n");
        *idCont = 1;
        return 1;
}

//Funcao para fazsr a edição de veiculos cadastrados
int editar_veic(Lista *lista){
    if(!lista){
        printf("Cadastre ao menos 1 veiculo!\n");
        return 0;
    }

    int idBusca;
    char escolha;
    Veiculo novo;
    printf("Informe o ID do Veiculo Buscado: ");
    scanf("%d", &idBusca);

    Veiculo *buscado;
     
    buscado = buscarVeic(lista, idBusca); //chama a função para pegar o veiculo por ID
    Elem *no = *lista;

    while(no != NULL){
        if(no->dados.id_veiculo == buscado->id_veiculo){
            printf("Veiculo encontrado:\n");
            printf("Modelo: %s | Placa: %s | Ano Fabricacao: %d | Km: %d\n\n", no->dados.modelo,
            no->dados.placa, no->dados.anoFabricacao, no->dados.km);

            printf("Deseja editar este Veiculo? (s/n)\n");
            scanf("%s", &escolha);

                if(escolha == 's' || escolha == 'S'){

                system("cls");
                printf("_________________________________\n");
                printf("Modificando veiculo %d\n", no->dados.id_veiculo);
                printf("Modelo do novo Veiculo: ");
                scanf(" %[^\n]s", novo.modelo );
                printf("Placa: ");
                scanf(" %[^\n]s", novo.placa);
                printf("Ano de Fabricacao: ");
                scanf("%d", &novo.anoFabricacao);
                printf("Km do Veiculo: ");
                scanf("%d", &novo.km);

                no->dados = novo;
                no->dados.id_veiculo = buscado->id_veiculo; //guarda o ID original e coloca no veiculo
                system("cls");
                printf("Veiculo Atualizado com Sucesso!\n");
                return 1;
                }else{
                    printf("Cancelando Edicao...\n");
                    return 0;
                }
        }
        no = no->prox;
    }
    printf("Nenhum veiculo encontrado!\n");
    return 1;
}
 //exclui todo o historico de Veiculos
int ExcluirHistoricoVeic(Lista *lista){
    if(*lista != NULL){
        Elem *aux;
        while((*lista) != NULL){
            aux = *lista;
            *lista = (*lista)->prox;
            free(aux);
        }
    }
        printf("Historicos Limpos com sucesso!\n");
        return 1;

}

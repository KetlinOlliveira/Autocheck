//Serviço.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Servico.h"
#include "Veiculo.h"
#include "Manutencao.h"


Lista2 *criar_listaServ(){ //cria a lista
    Lista2 *lista2 = (Lista2 *)malloc(sizeof(Lista2));
    if(lista2)
    *lista2 = NULL;
    return lista2;
}
   
int inserir_serv_comeco(Lista2 *lista2, Servico dados, int *idServ, Lista2 *historicoServ){
    if(!lista2|| !historicoServ) return 0;

    Elem2 *no = (Elem2 *)malloc(sizeof(Elem2));
    Elem2 *no2 = (Elem2 *)malloc(sizeof(Elem2));
    if(!no || !no2) return 0;

    no->dados = dados;
    no->prox = *lista2;
    *lista2 = no;

    no2->dados = dados;
    no2->prox = *historicoServ;
    *historicoServ = no2;
    no->dados.id = no2->dados.id = (*idServ)++;//da um ID unico para cada Servico cadastrado
       return 1;
}
int Inserir_finalServ(Lista2 *lista, Servico dados){
    if(!lista) return 0;

    Elem2 *no =  (Elem2 *)malloc(sizeof(Elem2));
    if(!no )return 0;

    no->dados = dados;
    no->prox = NULL;

    if(*lista == NULL){
        *lista = no;
    }else{
        Elem2 *aux = *lista;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
  return 1;
}
int Listar_Servicos(Lista2 *lista){//listas de forma simples
    if(lista == NULL || *lista == NULL){
        printf("Cadastre ao menos um Servico antes de Listar!\n");
        return 0;
    }
    Elem2 *no = *lista;
    while(no!=NULL){
        printf("                        Servico ID: %d\n",no->dados.id);
        printf("Tipo de Servico: %s\n\nData Realizada: %d/%d/%d\n", no->dados.servico, no->dados.dataManu.dia,no->dados.dataManu.mes, no->dados.dataManu.ano );
        printf("Veiculo: %d | %s | KM atual: %d\n", no->dados.id_veiculo, no->dados.modelo, no->dados.kmAtual);
        printf("Data Da proxima Revisao: %d/%d/%d\n", no->dados.proxManu.dia, no->dados.proxManu.mes, no->dados.proxManu.ano);
        printf("Observacoes: %s\n", no->dados.obs);
        
        printf("______________________________________________________________\n");

        no = no->prox;
    }
    return 1;
}

Data proxData(Data atual, int meses){
    Data nova = atual;
    nova.mes += meses;

    while(nova.mes >12){
        nova.mes -=12;
        nova.ano++;
    }

    int diasNoMes[] ={0,31, 28,31,30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(nova.dia > diasNoMes[nova.mes]){
        nova.dia = diasNoMes[nova.mes];
    }
    return nova;
}

//salva os arquivos 
int SalvarArquivosServico(Lista2 *lista, const char *servicos){
    if(!lista) return 0;

    FILE *arquivo = fopen(servicos, "w");
    if(!arquivo){
        printf("Falha ao abrir arquivo de Servicos\n");
        return 0;
    }
    Elem2 *no = *lista;
    while(no != NULL){
        fprintf(arquivo, "%d;%s;%s;%s;%d;%d;%d;%d;%d;%d;%d;%d\n", no->dados.id, no->dados.servico, no->dados.obs, no->dados.modelo,
        no->dados.dataManu.dia, no->dados.dataManu.mes, no->dados.dataManu.ano, no->dados.kmAtual, no->dados.id_veiculo, no->dados.proxManu.dia, 
        no->dados.proxManu.mes, no->dados.proxManu.ano);

          no = no->prox;
    }
  fclose(arquivo);
  return 1;
}

//Carrega os arquivos
int CarregarArquivosServ(Lista2 *lista, const char *servicos, int *idServ){
    if(lista == NULL){
        printf("Falha ao carregar arquivos de Servicos!\n");
        return 0;
    }
    int maiorID = 0;
    FILE *arquivo = fopen(servicos, "r");
    char linha[200];

    while(fgets(linha, sizeof(linha), arquivo)!= NULL){
        Servico s;
        
        if(sscanf(linha,"%d;%29[^;];%99[^;];%19[^;];%d;%d;%d;%d;%d;%d;%d;%d", &s.id, s.servico, s.obs, s.modelo, &s.dataManu.dia, &s.dataManu.mes,
        &s.dataManu.ano, &s.kmAtual, &s.id_veiculo, &s.proxManu.dia, &s.proxManu.mes, &s.proxManu.ano )==12){
            Inserir_finalServ(lista, s);

            if(s.id > maiorID){
                maiorID = s.id;
            }
        }
    }
    *idServ = maiorID +1;
fclose(arquivo);
return 1;
}

//exclui o servico pelo ID
int ExcluirServ(Lista2 *lista, int id){
    if(lista == NULL || *lista == NULL){
        printf("Cadastre ao menos um Servico!\n");
        return 0;
    }
    Elem2 *anterior = NULL;
    Elem2 *no = *lista;

    while(no != NULL && no->dados.id != id){
         anterior = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    if(anterior == NULL)
        *lista = no->prox;
    else
        anterior->prox = no->prox;
    free(no);
    return 1;
}
//limpa todos os servicos já registrados
int LimparServico(Lista2 *lista, int *idServ){
    if(*lista != NULL){
        Elem2 *aux;
        while((*lista) != NULL){
            aux = *lista;
            *lista = (*lista)->prox;
            free(aux);
        }
    }
    *idServ = 1;
    return 1;
}

//Limpa o historico de Servicos
int LimparHistorico(Lista2 *lista){
       if(*lista != NULL){
        Elem2 *aux;
        while((*lista) != NULL){
            aux = *lista;
            *lista = (*lista)->prox;
            free(aux);
        }
    }
    return 1;
}
//Faz a busca por um serviço com o ID, e retorna o endereço de memoria desse Servico
Servico *buscarServ(Lista2 *lista, int id){
    if(!lista) return NULL;

    Elem2 *no = *lista;
    while(no != NULL){
        if(no->dados.id == id){
            return &(no->dados);
        }
    no = no->prox;
    }
 return NULL;
}

int EditarServicos(Lista2 *lista){
    if(!lista){
        printf("Cadastre ao menos 1 Servico!\n");
        return 0;
    }
Servico *buscado; 
Servico novo; 
char escolha; 
int idBuscado, opServico; 
int intervalo;
int idVeic;
int idSalvo;

char modelosalvo[20], placasalvo[20];

    printf("Informe o ID do Servico Buscado: ");
    scanf("%d", &idBuscado);

    buscado = buscarServ(lista, idBuscado); 

    Elem2 *no = *lista;
    while(no!= NULL){
        if(no->dados.id == buscado->id){
            printf("Servico encontrado: \n");
            printf("Tipo de Servico: %s\n\nData Realizada: %d/%d/%d\n", no->dados.servico, 
            no->dados.dataManu.dia,no->dados.dataManu.mes, no->dados.dataManu.ano );
            printf("Veiculo: %d | %s | KM atual: %d\n", no->dados.id_veiculo, no->dados.modelo, no->dados.kmAtual);

            printf("Deseja Editar esse Servico?(s/n)\n");
            scanf("%s", &escolha);

            if(escolha == 's' || escolha == 'S'){
                strcpy(modelosalvo, no->dados.modelo);
                strcpy(placasalvo, no->dados.placa);
                idVeic = no->dados.id_veiculo;
                idSalvo = no->dados.id;

                system("cls");
                printf("Editando Servico: \n\n");
                  printf("____________________________________________________________________________\n");
                    printf("Servicos: \n1 - Manutencao Preventiva\n(Troca de oleo, Verificar Freios e Pneus, Revisao Sistema Eletrico, etc...)\n\n2 - Reparos \n(Substituicao de Pecas, Pintura)\n\n3 - Servicos Especializados \n(Estetica Automotiva e Diagnosticos de Problemas\n\n");
                    printf("_____________________________________________________________________________\n");
                    printf("Selecione o tipo de Manutencao: ");
                    scanf("%d", &opServico);

                        if(opServico == 1){
                            strcpy(novo.servico, "Manutencao Preventiva");
                            }else if(opServico == 2){
                            strcpy(novo.servico, "Reparos");
                            }else if(opServico == 3){
                            strcpy(novo.servico, "Especializados");
                            }else{
                                printf("Valor invalido!\n");
                                return 0;
                            }
                        
                        printf("Informe a Data Da Realizacao da Manutencao(dd/mm/aa): ");
                        scanf("%d %d %d", &novo.dataManu.dia, &novo.dataManu.mes, &novo.dataManu.ano);

                        printf("KM atual: ");
                        scanf("%d", &novo.kmAtual);

                        printf("Intervalo de Manutenao(meses): ");
                        scanf("%d", &intervalo);

                        printf("Observacoes: ");
                        scanf("  %[^\n]99", novo.obs);    
                        
                       novo.proxManu = proxData(novo.dataManu, intervalo); 

                       
                        no->dados = novo;
                        no->dados.id = idSalvo;
                        strcpy(no->dados.modelo, modelosalvo);
                        strcpy(no->dados.placa, placasalvo);
                        no->dados.id_veiculo = idVeic;
                
                       system("cls");
                       printf("Edicao Concluida com sucesso!\n");
                       return 1;
            }else{
                printf("Cancelando Edicao...\n");
                return 0;
            }
        }
         no = no->prox;
    }
printf("Erro ao Editar o Servico!\n");
return 1;
}
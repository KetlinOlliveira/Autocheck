//Manutencao.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veiculo.h"
#include "Servico.h"
#include "Manutencao.h"
#include "time.h" //Biblioteca para usar funções que usam o horario atual do computador

//cria a lista de manutenções
Lista3 *criar_lista3(){
    Lista3 *lista3 = (Lista3 *)malloc(sizeof(Lista3));
    if(lista3)
    *lista3 = NULL;
    return lista3;
}

int inserirFinalAgenda(Lista3 *lista3, Manutencao m){
    if(!lista3) return 0;

    Elemenu *no = (Elemenu *)malloc(sizeof(Elemenu));
    if(!no) return 0;

    no->dados = m;
    strcpy(no->dados.status, "A vencer"); //Ja copia automaticamente "a Vencer" em todas as manutencoes que são cadastradas
    no->prox = NULL;

    if(*lista3 == NULL){
        *lista3 = no;
    }else{
        Elemenu *aux = *lista3;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
return 1;
}

void dataAtual(int *dia, int *mes, int *ano){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    *dia = tm.tm_mday; 
    *mes = tm.tm_mon +1;
    *ano = tm.tm_year + 1900;
}
int compara_datas(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2){

    if(ano1 != ano2)
    return ano1 - ano2;
    if(mes1 != mes2)
    return mes1 - mes2;
    
    return dia1 - dia2;
}

int ordenar(Lista3 *lista){
    if(!lista) return 0;
    int troca; 
    Elemenu *atual, *prox;
    Manutencao temp;

    do{
        troca = 0;
        atual = *lista;


        while(atual->prox != NULL){
            prox = atual->prox;
            
            
            if(compara_datas(atual->dados.dados.proxManu.dia, atual->dados.dados.proxManu.mes,
                             atual->dados.dados.proxManu.ano, prox->dados.dados.proxManu.dia, prox->dados.dados.proxManu.mes,
                             prox->dados.dados.proxManu.ano)>0){
           
                temp = atual->dados;
                atual->dados = prox->dados;
                prox->dados = temp;
      
                troca = 1;
            }
            atual = atual->prox;
        }

    }while(troca);
    return 1; 
}


int Atualizar_status(Lista3 *lista3){
    if(!lista3) return 0;

    int diaAtual, mesAtual, anoAtual;
    dataAtual(&diaAtual, &mesAtual, &anoAtual);

    Elemenu *no= *lista3;

    while(no != NULL){
        if(compara_datas(no->dados.dados.proxManu.dia, no->dados.dados.proxManu.mes, no->dados.dados.proxManu.ano, diaAtual, mesAtual, anoAtual) <0){
            strcpy(no->dados.status, "VENCIDA");
        }else{
            strcpy(no->dados.status, "A VENCER");
        }
        no = no->prox;
    }
return 1;
}
//Lista as proximas manutenções
int listar_Prox(Lista3 *lista3){
    if(lista3 == NULL || *lista3 == NULL){
        printf("Cadastre ao menos uma Manutencao!\n");
        return 0;
    }
    Atualizar_status(lista3); //chama a função p atualizar o status
    ordenar(lista3); //ordena elas por data antes de listar
    Elemenu *no = *lista3;
    system("cls");
    printf("___________________________________________\n");
    printf("         Proximas Manutencoes\n");
    while(no!= NULL){
        printf("Modelo do Veiculo: %s  | Data Ultima Realizacao: %d/%d/%d\n",no->dados.dados.modelo, no->dados.dados.dataManu.dia,no->dados.dados.dataManu.mes,no->dados.dados.dataManu.ano);
        printf("Previsao para proxima manutencao: %d/%d/%d\n", no->dados.dados.proxManu.dia, no->dados.dados.proxManu.mes,  no->dados.dados.proxManu.ano );
        printf("Status: %s\n\n", no->dados.status );
        no = no->prox;
    }
return 1;
}

//Salva os arquivos
int SalvarArquivoManu(Lista3 *lista, const char *manutencoes){
    if(!lista) return 0;

    FILE *arquivo = fopen(manutencoes, "w");

    if(!arquivo){
        printf("Falha ao abrir arquivos de Manutencoes!\n");
        return 0;
    }

    Elemenu *no = *lista;
    while(no!= NULL){

        fprintf(arquivo,"%s;%s;%s;%d;%d;%d;%d;%d;%d;%d;%d;%s\n", no->dados.dados.servico, no->dados.dados.obs, no->dados.dados.modelo,
        no->dados.dados.dataManu.dia, no->dados.dados.dataManu.mes, no->dados.dados.dataManu.ano, no->dados.dados.kmAtual, no->dados.dados.id_veiculo, no->dados.dados.proxManu.dia, 
        no->dados.dados.proxManu.mes, no->dados.dados.proxManu.ano, no->dados.status);

        no = no->prox;
    }
    fclose(arquivo);
    return 1;

}
int CarregarManutencoes(Lista3 *lista, const char *manutencoes){
    if(lista == NULL) return 0;

    FILE *arquivo = fopen(manutencoes, "r");
    char linha[100];

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        Manutencao m;
        if(sscanf(linha,"%29[^;];%99[^;];%19[^;];%d;%d;%d;%d;%d;%d;%d;%d;%19[^\n]", m.dados.servico, m.dados.obs, m.dados.modelo,
        &m.dados.dataManu.dia, &m.dados.dataManu.mes, &m.dados.dataManu.ano, &m.dados.kmAtual, &m.dados.id_veiculo, &m.dados.proxManu.dia, 
        &m.dados.proxManu.mes, &m.dados.proxManu.ano, m.status )== 12){
            inserirFinalAgenda(lista, m); //Carrega as manutencoes e ja insere elas na lista original de manutencoes
        }
    }
fclose(arquivo);
return 1;
}
//Limpa todas as manutencoes
int ExcluirManutencoes(Lista3 *lista){
    if(!lista) return 0;
    Elemenu *aux;
    while(*lista != NULL){
        aux = *lista;
        *lista = (*lista)->prox;
        free(aux);
       }
return 1;
}


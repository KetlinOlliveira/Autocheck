//Main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "Manutencao.h"
#include "Veiculo.h"
#include "Servico.h"
int main(void){

int idCont =1;
int idServ =1;

Lista *listaOriginalVeiculos = criar_lista();
Lista2 *listaOriginalServicos = criar_listaServ();
Lista *historicoVeiculos = criar_lista();
Lista2 *historicoServicos = criar_listaServ();
Lista3 *agenda= criar_lista3();

//Carregando os arquivos
CarregarArquivosVeic(listaOriginalVeiculos, "veiculos.txt", &idCont);
CarregarArquivosServ(listaOriginalServicos, "servicos.txt", &idServ);
CarregarManutencoes(agenda, "manutencoes.txt");
CarregarArquivosVeic(historicoVeiculos, "historicoVeic.txt", &idCont);
CarregarArquivosServ(historicoServicos, "historicoServ.txt", &idServ);
 Atualizar_status(agenda);

Servico dadosS; //Variavel para armazenas dados de serviços
Manutencao m; //Variavel para armazenas dados de Manutençao
int veiculoBusca;
Veiculo *buscado; //Ponteiro do tipo Veiculo para armazenas o Veiculo buscado na chamada da função "buscarVeic"
int intervalo;//intervalo de meses da manutençao
int op, op2, op3,op4,op5; //variaveis de opceos dos switchs
int idbuscadoServ;
int id;

    do{
        printf("______________________________________\n");
        printf("           Menu Manutencao\n\n");
        printf(" 1 - Veiculos\n");
        printf(" 2 - Servicos\n");
        printf(" 3 - Historico\n");
        printf(" 4 - Agenda de Servicos\n");
        printf(" 5 - Excluir Todas as Listas\n");
        printf(" 0 - Encerrar\n");
        printf("________________________________________\nR: ");
        scanf("%d", &op);
        switch(op){
            case 1:
            system("cls");
                printf("_____________________________________\n");
                printf("         Menu Veiculos\n");
                printf(" 1 - Cadastrar novo Veiculo\n");
                printf(" 2 - Listagem de Veiculos Cadastrados\n");
                printf(" 3 - Fazer consulta por ID\n");
                printf(" 4 - Excluir Veiculo\n");
                printf(" 5 - Editar\n");
                printf(" 0 - Retornar\n");
                printf("_____________________________________\nR: ");
                scanf("%d", &op2);
                
                switch(op2){
                    case 1:
                    CadastrarVeiculo(listaOriginalVeiculos, historicoVeiculos, &idCont);
                    break;
                    case 2:
                    Listar_veiculos(listaOriginalVeiculos);
                    break;
                    case 3:
                    Consulta_veic(listaOriginalVeiculos);
                    break;
                    case 4:
                    system("cls");
                    printf("Informe o ID do Veiculo que deseja excluir: ");
                    scanf("%d", &id);

                    if(Excluir_Veic(listaOriginalVeiculos, id)){
                        printf("Veiculo excluido com sucesso!\n");
                    }else{
                        printf("Falha ao excluir Veiculo!\n");
                    }
                    break;
                    case 5:
                    editar_veic(listaOriginalVeiculos);
                    break;
                    case 0:
                    system("cls");
                    printf("Retornando...\n");
                    break;
                    default:
                    system("cls");
                    printf("Valor invalido\n");
                }
            break;
            case 2:
            system("cls");
                printf("______________________________________\n");
                printf("           Menu Servicos\n");
                printf(" 1 - Registrar novo Servico\n");
                printf(" 2 - Listagem de Cadastros\n");
                printf(" 3 - Excluir\n");
                printf(" 4 - Editar\n");
                printf(" 5 - Retornar\n");
                printf("__________________________________________\nR: ");
                scanf("%d", &op3);

                switch(op3){
                    case 1:
                     system("cls");
                    printf("____________________________________________________________________________\n");
                    printf("Servicos: \n1 - Manutencao Preventiva\n(Troca de oleo, Verificar Freios e Pneus, Revisao Sistema Eletrico, etc...)\n\n2 - Reparos \n(Substituicao de Pecas, Pintura)\n\n3 - Servicos Especializados \n(Estetica Automotiva e Diagnosticos de Problemas\n\n4 - Cancelar Cadastro\n \n");
                    printf("_____________________________________________________________________________\n");
                    printf("Selecione o tipo de Manutencao: ");
                    scanf("%d", &op4);

                        if(op4 == 1){
                            strcpy(dadosS.servico, "Manutencao Preventiva");//Nomeia o tipo de Serviço que o usuario deseja
                            }
                            if(op4 == 2){
                            strcpy(dadosS.servico, "Reparos");
                            }
                              if(op4 == 3){
                            strcpy(dadosS.servico, "Especializados");
                            }
                                if(op4 == 4){
                                system("cls");
                                printf("Retornando ao menu...\n");
                                return 0;
                            }
                        printf("Informe o id do Veiculo: ");
                        scanf(" %d", &veiculoBusca);
                      
                     buscado = buscarVeic(listaOriginalVeiculos, veiculoBusca);
                        
                        if(buscado != NULL){
                          dadosS.id_veiculo = buscado->id_veiculo;
                          strcpy(dadosS.modelo, buscado->modelo);
                          strcpy(dadosS.placa, buscado->placa);

                          printf("Veiculo encontrado: %s | ID: %d\n", buscado->modelo, buscado->id_veiculo);
                         }else{
                             system("cls");
                             printf("Veiculo nao encontrado!\n");
                            break;
                        }
                        printf("Informe a Data Da Realizacao da Manutencao(dd/mm/aa): ");
                        scanf("%d %d %d", &dadosS.dataManu.dia, &dadosS.dataManu.mes, &dadosS.dataManu.ano);
                        printf("KM atual: ");
                        scanf("%d", &dadosS.kmAtual);
                        printf("Intervalo de Manutenao(meses): ");
                        scanf("%d", &intervalo);
                        printf("Observacoes: ");
                        scanf("  %[^\n]99", dadosS.obs);    
                        
                       dadosS.proxManu = proxData(dadosS.dataManu, intervalo); 

                     m.dados = dadosS;
                  
                     inserirFinalAgenda(agenda, m);//insere os dados na agenda
                     ordenar(agenda);//ordena os mesmos
                    
                     //insere o servico na lista
                    if(inserir_serv_comeco(listaOriginalServicos, dadosS, &idServ, historicoServicos)){ 
                        system("cls");
                        printf("Servico Cadastrado e Agenda Atualizada com Sucesso!\n");
                    }else
                        printf("Ops, Falha ao Cadastrar Servico!\n");
                    
                    break;
                    case 2://listar servicos
                    Listar_Servicos(listaOriginalServicos);
                    break;
                    case 3://exclui por id
                    system("cls");
                    printf("Informe o ID do Servico que deseja excluir: ");
                    scanf("%d", &idbuscadoServ);
                     ExcluirServ(listaOriginalServicos, idbuscadoServ);
                    break;
                    case 4://editar
                    EditarServicos(listaOriginalServicos);
                    break;
                    case 5:
                    system("cls");
                    printf("Retornando...\n");
                    break;
                    default:
                    system("cls");
                    printf("Valor invalido!\n");
                }
            break;
            case 3:
            system("cls");
            printf("_______________________________________\n");
            printf("            Historico\n\n");
            printf(" 1 - Historico de Veiculos\n");
            printf(" 2 - Historico de Servicos\n");
            printf(" 3 - Excluir Todos\n");
            printf(" 4 - Retornar\n");
            scanf("%d", &op5);

                switch(op5){
                    case 1://Lista o historico de todos os veiculos cadastrados
                    Listar_veiculos(historicoVeiculos);
                    break;
                    case 2:// faz o mesmo com os servicos
                    Listar_Servicos(historicoServicos);
                    break;
                    case 3://exclui ambos
                    LimparHistorico(historicoServicos);
                    ExcluirHistoricoVeic(historicoVeiculos);
                    break;
                    case 4:
                    system("cls");
                    printf("Retornando...\n");
                    break;
                    default:
                    printf("Valor invalido!\n");
                }
            break;
            case 4:
            system("cls");
            listar_Prox(agenda);
            break;
            case 5: //limpa todas as listas e reinicia os ids
            idCont = LimparVeic(listaOriginalVeiculos, &idCont);
            idServ = LimparServico(listaOriginalServicos, &idServ);
            ExcluirManutencoes(agenda);
            break;
            case 0:
            printf("Encerrando programa... \n");
            break;
            default:
            printf("Valor invalido, tente outro numero...\n");
        }
    }while(op != 0);
    
    //salva todos os arquivos antes de fechar e da um free
    Salvar_arquivos_Veiculos(listaOriginalVeiculos, "veiculos.txt");
    SalvarArquivosServico(listaOriginalServicos, "servicos.txt");
    Salvar_arquivos_Veiculos(historicoVeiculos, "historicoVeic.txt");
    SalvarArquivosServico(historicoServicos, "historicoserv.txt");
    SalvarArquivoManu(agenda, "manutencoes.txt");

    //limpa todas as listas
    free(listaOriginalServicos);
    free(listaOriginalServicos);
    free(historicoServicos);
    free(historicoVeiculos);
    free(agenda);

    return 0;
}
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "funcoesEestruturas.h"

void ver_estoque(void);
void inserir_estoque(void);

void ver_lanche(void);
void add_lanche(void);

void cardapio(void);
void carrinho(void);

void fluxo_caixa(void);

void cadastrar_func(void);
void ver_func(void);

void menu_adm(void);
void menu_cliente(void);
void menu_principal(void);


int selecao = 0, cont = 0;
char nome[30];
FILE *arq;


void ver_estoque(void)
    {
        system("cls"); // Limpando o terminal
        float somaestoque = 0.0;

        arq = fopen("estoque.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo estoque");
                Sleep(3000);
                menu_adm();
            }
        fread(&estoque, sizeof(Estoque), tam_estoque(), arq);
        fclose(arq);

        printf("\t\tESTOQUE");
        printf(" \n -----------------------------------------------------------");
        printf("\nValor total do estoque: ");
        for(cont=0; cont<tam_estoque(); cont++)
            {
                somaestoque = somaestoque + estoque[cont].valor_total;
            }
        printf("%.2f\n\n", somaestoque);
        printf("\n%d", tam_estoque());
        for(cont=0; cont<tam_estoque(); cont++)//Mostrando o estoque
            {
                Sleep(500);
                printf(" \n ID do item: %d ",  estoque[cont].id); //Mostrando o ID
                printf(" \n Nome do item: %s ", estoque[cont].nome); //Mostrando o  NOME
                printf(" \n QTDE/PESO do item: %.3f %s", estoque[cont].peso, estoque[cont].medida); //Mostrando o PESO
                printf(" \n Valor por %s: %.2f ",estoque[cont].medida, estoque[cont].valor_peso); //Mostrando o VALOR POR PESO/UNI
                printf(" \n Valor total: %.2f ", estoque[cont].valor_total); //Mostrando o VALOR TOTAL
                printf(" \n Data e Hora de entrada: %d/%d/%d - ",  estoque[cont].dia,  estoque[cont].mes, estoque[cont].ano); //Mostrando A DATA
                printf("%d:%d:%d", estoque[cont].hora, estoque[cont].min, estoque[cont].seg);
                printf(" \n ------------------------------------------------------------");
            }

        do
            {
                printf("\n\nAdicionar produto ao estoque[1]\nVoltar ao menu[2]\n\nOpcão: ");
                scanf("%d", &selecao);
            }while(selecao != 1 && selecao != 2);

        if(selecao == 1)
            {
                inserir_estoque();
            }
        if(selecao == 2)
            {
                menu_adm();
            }
    }
void inserir_estoque(void)
    {
            system("cls"); //Limpando o terminal

            int b;
            FILE *arquivo;

            //variável do tipo time_t para armazenar o tempo em segundos
            time_t segundos;
            //obtendo o tempo em segundos
            time(&segundos);
            //para converter de segundos para o tempo local
            data_hora_atual = localtime(&segundos);

            arq = fopen("estoque.txt", "a");
            if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo estoque");
                Sleep(3000);
                menu_adm();
            }
            arquivo = fopen("estoque2.txt", "a");
            if(!arquivo)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo estoque dois");
                Sleep(3000);
                menu_adm();
            }

            printf(" \n ID do item: ");
            scanf("%d", &b);

            while(comparador_estoque(b)>=0)//Se o ID digitado pertence a outro produto entra em looping até digitar um id válido
                {
                    printf("\nEste Id já está em uso.");
                    Sleep(1000);
                    system("cls"); //Limpando o terminal
                    printf(" \n ID do item: ");
                    fflush(stdin);
                    scanf("%d", &b);
                }
            estoque[1+tam_estoque()].id = b;
            printf(" \n Nome do item: ");
            fflush(stdin);
            gets(estoque[1+tam_estoque()].nome);
            printf(" \n Tipo de medida [Kg][L][Uni]: ");
            scanf("%s", &estoque[1+tam_estoque()].medida);// Inserindo o Tipo de medida
            printf(" \n QTDE/PESO do item: ");
            scanf("%f", &estoque[1+tam_estoque()].peso);// Inserindo a quantidade
            printf(" \n Valor por %s: ", estoque[1+tam_estoque()].medida);
            scanf("%f", &estoque[1+tam_estoque()].valor_peso);// Inserindo o valor por unidade ou kg
            estoque[1+tam_estoque()].valor_total = estoque[1+tam_estoque()].valor_peso * estoque[1+tam_estoque()].peso;// Inserindo o valor total
            estoque[1+tam_estoque()].dia = data_hora_atual->tm_mday;  // Inserindo o Dia
            estoque[1+tam_estoque()].mes = data_hora_atual->tm_mon+1; // Inserindo o mes
            estoque[1+tam_estoque()].ano = data_hora_atual->tm_year+1900;// Inserindo o ano
            estoque[1+tam_estoque()].hora = data_hora_atual->tm_hour; // Inserindo a hora
            estoque[1+tam_estoque()].min = data_hora_atual->tm_min; // Inserindo o min
            estoque[1+tam_estoque()].seg = data_hora_atual->tm_sec; // Inserindo o sec
            printf(" \n ------------------------------------------------------------------------\n");
            fwrite(&estoque[1+tam_estoque()], sizeof(Estoque), 1, arq);//Salvando os dados no arquivo
            fwrite(&estoque[1+tam_estoque()], sizeof(Estoque), 1, arquivo);
            printf("\nItem adicionado com sucesso!!\nVoltando para o estoque.");
            Sleep(3000);
            fclose(arq);
            fclose(arquivo);
            ver_estoque();
        }
void ver_lanche(void)
    {
        system("cls");
        int a, d, x = 0;
        float somaitem;
        setlocale(LC_ALL,"portuguese");

        arq = fopen("ficha_lanche.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo Ficha_lanche");
                Sleep(3000);
                menu_adm();
            }
        fread(&lanche, sizeof(Lanche),  tam_ficha_lanche(), arq);
        fclose(arq);

        arq = fopen("insumos_lanches.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo insumos_lanches");
                Sleep(3000);
                menu_adm();
            }
        fread(&insumo, sizeof(Itens),  tam_insumos(), arq);
        fclose(arq);

        printf("\n\tFICHA TÉCNICA");
        printf("\n--------------------------------------------\n");
        for(cont = 0; cont<tam_ficha_lanche(); cont++) //Imprimindo os lanches
            {
                somaitem = 0.0;
                printf("\n\tNome do lanche: %s", lanche[cont].nome_lanche);
                printf("\n\tId do lanche: %d", lanche[cont].id_lanche);
                printf("\n\tValor do lanche: %.2f\n", lanche[cont].valor_lanche);
                d = x;
                for(a = x; a<lanche[cont].insumo_qtde+d; a++) //Imprimindo os insumos que compoe os lanches
                    {
                        printf("\n\tId do item: %d", insumo[a].id_item);
                        printf("\n\tNome do item: %s",insumo[a].nome_item);
                        printf("\n\tQuantidade/Peso do item: %.3f %s", insumo[a].peso, insumo[a].medida);
                        printf("\n\tValor do item: %.2f\n", insumo[a].valor);
                        somaitem = somaitem + insumo[a].valor;
                        x++;
                    }
                printf("\n\t\tTOTAL: %.2f", somaitem);
                printf("\n--------------------------------------------\n");
            }

        do
            {
                printf("\n\nAdicionar Lanche[1]\nVoltar ao menu[2]\n\nOpcão: ");
                scanf("%d", &selecao);
            } while(selecao != 1 && selecao != 2);
        if(selecao == 1)
            {
                add_lanche();
            }
        if(selecao == 2)
            {
                menu_adm();
            }
    }
void add_lanche(void)
    {
        system("cls");
        int id_escolhido, x, a, tamanho;
        setlocale(LC_ALL,"portuguese");

        inicializador_lanche();

        arq = fopen("ficha_lanche.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo ficha_lanche");
                Sleep(3000);
                menu_adm();
            }
        fread(&lanche, sizeof(Lanche),  tam_ficha_lanche(), arq);
        fclose(arq);

        tamanho = tam_ficha_lanche();

        printf("\nTela add lanche");
        printf(" \n ------------------------------------------------------\n");

        for(cont = 0; cont<1; cont++)
            {
                printf("\nNome do lanche:  ");
                fflush(stdin);
                gets(lanche[cont + tamanho].nome_lanche);

                lanche[cont + tamanho].posicao = tamanho;

                printf("\nId do lanche: ");
                fflush(stdin);
                scanf("%d", &lanche[cont+ tamanho].id_lanche);


                printf("\nValor do lanche: ");
                fflush(stdin);
                scanf("%f", &lanche[cont+ tamanho].valor_lanche);

                printf("\nItens para o lanche: ");
                fflush(stdin);
                scanf("%d", &lanche[cont+ tamanho].insumo_qtde);

                system("cls");
                arq = fopen("estoque.txt", "r");
                fread(&estoque, sizeof(Estoque), tam_estoque(), arq);

                //Mostrando o estoque
                printf("\t\tItens disponiveis no estoque");
                printf(" \n -----------------------------------------------------------\n");
                for(x=0; x<tam_estoque(); x++) //
                    {
                        printf(" \n ID do item: %d ",  estoque[x].id);
                        printf(" \n Nome do item: %s ", estoque[x].nome);
                        printf(" \n Data de entrada: %d/%d/%d ",  estoque[x].dia,  estoque[x].mes, estoque[x].ano);
                        printf(" \n ------------------------------------------------------------");
                    }
                fclose(arq);
                for(a = 0; a<lanche[cont+ tamanho].insumo_qtde; a++)
                    {

                        printf("\nId do %dº Item: ", a+1);
                        fflush(stdin);
                        scanf("%d", &id_escolhido);
                        while(comparador_estoque(id_escolhido) == -1)
                                {
                                    printf("\nEste Id não existe!!");
                                    Sleep(2000);
                                    printf("\nId do %dº Item: ", a+1);
                                    fflush(stdin);
                                    scanf("%d", &id_escolhido);
                                }

                        insumo[a].posicao = tamanho;

                        insumo[a].id_item = id_escolhido;
                        id_escolhido = comparador_estoque(id_escolhido);
                        strcpy(insumo[a].nome_item,estoque[id_escolhido].nome);
                        strcpy(insumo[a].medida,estoque[id_escolhido].medida);
                        printf("Quantidade de %s necessário: ",insumo[a].medida);
                        scanf("%f%*c", &insumo[a].peso);
                        if(strcmp("kg",insumo[a].medida) == 0)
                            {
                                insumo[a].valor = insumo[a].peso * estoque[id_escolhido].valor_peso;
                            }
                        else
                            {
                                insumo[a].valor = estoque[id_escolhido].valor_peso;
                            }
                        arq = fopen("insumos_lanches.txt", "a");
                        fwrite(&insumo[a], sizeof(Itens),  1, arq);
                        fclose(arq);
                    }
            }

        arq = fopen("ficha_lanche.txt", "w");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo ficha_lanche");
                Sleep(3000);
                menu_adm();
            }
        for(x = 0; x < tamanho + 1; x++)
            {
                fwrite(&lanche[x], sizeof(Lanche),  1, arq);
            }

        fclose(arq);
        printf("\nItem adicionado com sucesso!!\nVoltando para o estoque.");
        Sleep(3000);
        ver_lanche();
    }

void cardapio(void)
    {
            system("cls");
            int a, d, x;

            setlocale(LC_ALL,"portuguese");

            inicializador_insumo();
            inicializador_lanche();
            arq = fopen("ficha_lanche.txt", "r");
            if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo ficha_lanche");
                Sleep(3000);
                menu_principal();
            }
            fread(&lanche, sizeof(Lanche),  tam_ficha_lanche(), arq);
            fclose(arq);


            arq = fopen("insumos_lanches.txt", "r");
            if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo insumos_lanches");
                Sleep(3000);
                menu_principal();
            }
            fread(&insumo, sizeof(Itens),  tam_insumos(), arq);
            fclose(arq);

            printf("\n\tCARDÁPIO");
            printf("\n--------------------------------------------\n");

            x = 0;
            for(cont = 0; cont<tam_ficha_lanche(); cont++)
                {
                    printf("\n\t%s..............%.2f", lanche[cont].nome_lanche, lanche[cont].valor_lanche);
                    printf("\n\tId do lanche: %d\n", lanche[cont].id_lanche);
                    d = x;
                    printf("\t");
                    for(a = x; a<lanche[cont].insumo_qtde + d; a++)
                        {
                            printf("%s",insumo[a].nome_item);
                            if(a+1 == lanche[cont].insumo_qtde + d){printf(".");}
                            else{printf(", ");}
                            x++;
                        }
                    printf("\n--------------------------------------------\n");
                }
            printf("\n\nId do lanche escolhido[-1 MENU]: ");
            scanf("%d", &selecao);
            if(selecao == -1){menu_principal();}
            cont = comparador_lanche(selecao);//CHECANDO SE O LANCHE ESTÁ NO CARDÁPIO

            while(cont == -1) // Se não tiver entra em looping
                {
                    printf("Lanche não existe");
                    printf("\n\nId do lanche escolhido: ");
                    scanf("%d", &selecao);
                    cont = comparador_lanche(selecao);
                }

            printf("\n\nLanche adicionado ao carrinho.");


            arq = fopen("carrinho_um.txt", "a");
            if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo carrinho_um");
                Sleep(3000);
                menu_principal();
            }
            for(a=0; a<tam_insumos(); a++) // Adicionando o lanche no carrinho
                {
                    if(a == lanche[cont].posicao)
                        {
                            fprintf(arq, " %d %d %d %f %s", lanche[cont].id_lanche, lanche[cont].insumo_qtde,lanche[cont].posicao,lanche[cont].valor_lanche, lanche[cont].nome_lanche);
                        }
                }
            fclose(arq);

            arq = fopen("carrinho_dois.txt", "a");
            if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo carrinho_dois");
                Sleep(3000);
                menu_principal();
            }
             for(a=0; a<tam_insumos(); a++) // Adicionando insumos no carrinho
                {
                    if(lanche[cont].posicao == insumo[a].posicao)
                    {
                          fprintf(arq, " %d %f %f %d", insumo[a].id_item, insumo[a].valor, insumo[a].peso, insumo[a].posicao);
                    }
                }
             fclose(arq);
            printf("\n\nVer carrinho[1]  Adicionar mais lanche[2]");
            do
                {
                    printf("\nopcao: ");
                    scanf("%d", &selecao);
                }while(selecao == 0 || selecao > 2);
            if(selecao == 1)
                {
                    carrinho();
                }
            if(selecao == 2)
                {
                    cardapio();
                }

    }
void carrinho(void)
    {
        system("cls");

        int id, posicao, a, indice, tamanho, tamanhoestoque;
        float peso, valor, totalvalor = 0.0;

        FILE *arquivo;
        //variável do tipo time_t para armazenar o tempo em segundos
        time_t segundos;
        //obtendo o tempo em segundos
        time(&segundos);
        //para converter de segundos para o tempo local
        //utilizamos a função localtime
        data_hora_atual = localtime(&segundos);


        inicializador_insumo();
        inicializador_lanche();

        tamanhoestoque = tam_estoque();

        arq = fopen("carrinho_um.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo carrinho_um");
                Sleep(3000);
                menu_principal();
            }

        printf("\n\tCARRINHO");
        printf("\n------------------------------------\n");
        for(cont=0; cont<tam_carrinholl(); cont++)
            {
                fscanf(arq, " %d %d %d %f %s", &lanche[cont].id_lanche, &lanche[cont].insumo_qtde, &lanche[cont].posicao,&lanche[cont].valor_lanche,&lanche[cont].nome_lanche);
                printf("\n\tid: %d", lanche[cont].id_lanche);
                printf("\n\t%s.............%.2f\n", lanche[cont].nome_lanche, lanche[cont].valor_lanche);
                totalvalor = totalvalor + lanche[cont].valor_lanche;
            }
        printf("\n------------------------------------\n");
        fclose(arq);
        printf("\n\t\t\tTOTAL: %.2f", totalvalor);
        printf("\n------------------------------------\n");
        printf("\nFinalizar pedido [1]   Remover lanche [2]   Cardápio [3]");
        do
            {
                printf("\nOpcao: ");
                scanf("%d", &selecao);
            }while(selecao <=0 || selecao > 3);
                if(selecao == 1)
                    {
                        inicializador_estoque();
                        arq = fopen("estoque.txt", "r");
                        fread(&estoque,sizeof(Estoque), tam_estoque(), arq);
                        fclose(arq);
                        Data tempo;
                        tempo.dia = data_hora_atual->tm_mday;
                        tempo.mes = data_hora_atual->tm_mon;
                        tempo.ano = data_hora_atual->tm_year+1900;
                        tempo.hora = data_hora_atual->tm_hour;
                        tempo.min = data_hora_atual->tm_min;
                        tempo.seg = data_hora_atual->tm_sec;
                        arquivo = fopen("venda_lanche.txt", "a");
                        for(cont=0; cont<tam_carrinholl(); cont++)
                            {
                                fprintf(arquivo, "\n%s %s %d %f %d %d %d %d %d %d %d", nome,lanche[cont].nome_lanche,lanche[cont].id_lanche,lanche[cont].valor_lanche,lanche[cont].posicao,
                                        tempo.dia,tempo.mes,tempo.ano,tempo.hora,tempo.min,tempo.seg);

                            }
                        fclose(arquivo);

                        arq = fopen("carrinho_dois.txt", "r");
                        if(!arq)
                            {
                                printf("\n\n\t\tERRO ao abrir o arquivo carrinho_dois");
                                Sleep(3000);
                                menu_adm();
                            }
                        for(cont=0; cont<tam_carrinho(); cont++)
                            {
                                fscanf(arq, " %d %f %f %d", &id, &valor, &peso, &posicao);
                                indice = comparador_estoque(id);
                                estoque[indice].peso = estoque[indice].peso - peso;
                                estoque[indice].valor_total = estoque[indice].peso * estoque[indice].valor_peso;
                                arquivo = fopen("estoque.txt", "w");
                                fwrite(&estoque, sizeof(Estoque), tamanhoestoque, arquivo);
                                fclose(arquivo);

                            }
                        fclose(arq);

                        arq = fopen("carrinho_dois.txt", "w");
                        fclose(arq); //Limpando o carrinho

                        arq = fopen("carrinho_um.txt", "w");
                        fclose(arq); //Limpando o carrinho

                        menu_cliente();
                    }

                if(selecao == 2)
                    {
                        printf("\nId do lanche: ");
                        scanf("%d", &selecao);

                        posicao = comparador_lanche(selecao);

                        tamanho = tam_carrinholl();
                        inicializador_lanche();
                        arq = fopen("carrinho_um.txt", "r");
                        if(!arq)
                            {
                                printf("\n\n\t\tERRO ao abrir o arquivo carrinho_um");
                                Sleep(3000);
                                menu_principal();
                            }
                        for(cont=0; cont<tamanho; cont++)
                            {
                                fscanf(arq, " %d %d %d %f %s", &lanche[cont].id_lanche, &lanche[cont].insumo_qtde, &lanche[cont].posicao,&lanche[cont].valor_lanche,&lanche[cont].nome_lanche);
                            }
                        fclose(arq);

                        arq = fopen("carrinho_um.txt", "w");
                        if(!arq)
                            {
                                printf("\n\n\t\tERRO ao abrir o arquivo carrinho_um");
                                Sleep(3000);
                                menu_principal();
                            }
                        for(cont=0; cont<tamanho; cont++)
                            {

                                if(lanche[a].id_lanche != selecao)
                                    {
                                        fprintf(arq, " %d %d %d %f %s", lanche[cont].id_lanche, lanche[cont].insumo_qtde,lanche[cont].posicao,lanche[cont].valor_lanche, lanche[cont].nome_lanche);
                                    }

                            }
                        fclose(arq);

                        tamanho = tam_carrinho();
                        arquivo = fopen("carrinho_dois.txt", "r");
                        for(cont=0; cont<tamanho; cont++)
                            {
                                fscanf(arq, " %d %f %f %d", insumo[cont].id_item, insumo[cont].valor, insumo[cont].peso, insumo[cont].posicao);
                            }
                        fclose(arq);

                        arquivo = fopen("carrinho_dois.txt", "w");
                        for(cont=0; cont<tamanho; cont++)
                            {
                                if(insumo[a].posicao != posicao)
                                    {
                                        fprintf(arq, " %d %f %f %d", insumo[cont].id_item, insumo[cont].valor, insumo[cont].peso, insumo[cont].posicao);
                                    }
                            }
                        fclose(arq);

                        printf("\nItem removido com sucesso!");

                        Sleep(2000);
                        carrinho();
                    }

                if(selecao == 3)
                    {
                        cardapio();
                    }

    }
void fluxo_caixa(void)
    {
        system("cls");
        float valortotalum = 0.0,valortotaldois = 0.0;

        inicializador_lanche();

        arq = fopen("venda_lanche.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo venda_lanche");
                Sleep(3000);
                menu_adm();
            }
        printf("\n\t\t\tFluxo de caixa");
        printf("\n--------------------------------------------------------------------------------------------------");
        Data tempo[100];
        printf("\nENTRADA");
        for(cont=0; cont<tam_venda(); cont++)
            {
                fscanf(arq, "\n%s %s %d %f %d %d %d %d %d %d %d", &nome,&lanche[cont].nome_lanche,&lanche[cont].id_lanche,&lanche[cont].valor_lanche,&lanche[cont].posicao,
                        &tempo[cont].dia,&tempo[cont].mes,&tempo[cont].ano,&tempo[cont].hora,&tempo[cont].min,&tempo[cont].seg);
                valortotalum = valortotalum + lanche[cont].valor_lanche;
                printf("\nCliente: %s | Valor: %.2f | Item: %s | ID: %d | Data da venda: %d/%d/%d - %d:%d:%d", nome, lanche[cont].valor_lanche,lanche[cont].nome_lanche,lanche[cont].id_lanche,
                        tempo[cont].dia,tempo[cont].mes,tempo[cont].ano,tempo[cont].hora,tempo[cont].min,tempo[cont].seg);
            }
     //   for(cont=0; cont<tam_venda(); cont++)
      //      {
      //          printf("\nCliente: %s | Valor: %.2f | Item: %s | ID: %d | Data da venda: %d/%d/%d - %d:%d:%d", nome, lanche[cont].valor_lanche,lanche[cont].nome_lanche,lanche[cont].id_lanche,
      //                  tempo[cont].dia,tempo[cont].mes,tempo[cont].ano,tempo[cont].hora,tempo[cont].min,tempo[cont].seg);
      //      }
        printf("\nTOTAL: %.2f", valortotalum);
        fclose(arq);
        printf("\n\n--------------------------------------------------------------------------------------------------");

        printf("\n\nSAÍDA");
        printf("\nCompra de Insumos");
        arq = fopen("estoque2.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo estoque2");
                Sleep(3000);
                menu_adm();
            }
        selecao = tam_estoque();
        fread(&estoque, sizeof(Estoque), selecao, arq);
        fclose(arq);
        for(cont=0; cont<selecao; cont++)
            {
                printf("\nValor: %.2f |", estoque[cont].valor_total);
                printf(" item: %s |", estoque[cont].nome);
                printf(" ID: %d |",  estoque[cont].id);
                printf(" QTDE/PESO do item: %.3f %s|", estoque[cont].peso, estoque[cont].medida);
                printf(" Data da compra: %d/%d/%d - ",  estoque[cont].dia,  estoque[cont].mes, estoque[cont].ano);
                printf("%d:%d:%d", estoque[cont].hora, estoque[cont].min, estoque[cont].seg);
                valortotaldois = valortotaldois + estoque[cont].valor_total;
            }
        printf("\nSalários");
        arq = fopen("cadastroFuncionarios.txt", "r");
        if(!arq)
            {
                printf("\n\n\t\tERRO ao abrir o arquivo cadastroFuncionarios");
                Sleep(3000);
                menu_adm();
            }
        arq = fopen("cadastroFuncionarios.txt", "r");
        fread(&funcionario, sizeof(cadastroFuncionario), tam_funcionario(), arq);
        fclose(arq);
        for(cont=0; cont<tam_funcionario(); cont++)
            {
                printf("\nSalário: %.2f | Nome: %s | Cargo: %s ", funcionario[cont].salario, funcionario[cont].nome, funcionario[cont].funcao);
                valortotaldois = valortotaldois + funcionario[cont].salario;
            }
        printf("\nTOTAL: %.2f", valortotaldois);
        printf("\n--------------------------------------------------------------------------------------------------");
        printf("\nSALDO FINAL: %.2f", valortotalum - valortotaldois);
        printf("\n\nVoltar menu[1]");
        do
            {
                printf("\nopcao: ");
                scanf("%d", &selecao);
            }while(selecao != 1);
        if(selecao == 1)
            {
                menu_adm();
            }

    }

void ver_func(void)
    {
    system("cls");
    arq = fopen("cadastroFuncionarios.txt", "r");
    fread(&funcionario, sizeof(cadastroFuncionario), tam_funcionario(), arq);
    fclose(arq);
    printf("\n\t\tFUNCIONÁRIOS");
    printf("\n---------------------------------------------------------\n");
    for (cont = 0;cont < tam_funcionario(); cont++) {

            printf("\n\tID: %d \n", funcionario[cont].id);
            printf("\tNome: %s \n", funcionario[cont].nome);
            printf("\tEmail: %s \n", funcionario[cont].email);
            printf("\tTelefone: %s \n", funcionario[cont].telefone);
            printf("\tFunção: %s \n", funcionario[cont].funcao);
            printf("---------------------------------------------------------\n");
        }
    printf("\n\t1. Cadastrar funcionário\n\t2. Voltar");
    scanf("%d", &selecao);
    if(selecao == 1){cadastrar_func();}
    else{menu_adm();}
    }

void cadastrar_func(void)
    {
        system("cls");
        arq = fopen("cadastroFuncionarios.txt", "a");
        printf(" \n ID do Funcionario: ");
        scanf("%d", &funcionario[1+tam_funcionario()].id);
        printf(" \n Nome do Funcionario: ");
        scanf("%s", &funcionario[1+tam_funcionario()].nome);
        printf(" \n Email do Funcionario: ");
        scanf("%s", &funcionario[1+tam_funcionario()].email);
        printf(" \n Telefone do Funcionario: ");
        scanf("%s", &funcionario[1+tam_funcionario()].telefone);
        printf(" \n Senha do Funcionario: ");
        scanf("%s", &funcionario[1+tam_funcionario()].senha);
        printf(" \n Função do Funcionario: ");
        scanf("%s", &funcionario[1+tam_funcionario()].funcao);
        printf(" \n Salario do Funcionario: ");
        scanf("%f", &funcionario[1+tam_funcionario()].salario);
        printf(" \n Nivel do Funcionario (1 Para Atendente, 2 Para Gerencia): ");
        scanf("%d", &funcionario[1+tam_funcionario()].nivel);

        fwrite(&funcionario[1+tam_funcionario()], sizeof(cadastroFuncionario), 1, arq);
        fclose(arq);

        printf(" \n Usuário %s cadastrado com sucesso! Voltando para o Menu.", funcionario[1+tam_funcionario()].nome);
        Sleep(3000);
        ver_func();
    }
void menu_adm(void)
    {
        system("cls");
        setlocale(LC_ALL,"portuguese");
        selecao = sizeof(Itens);
        printf("\tMENU ADMINISTRATIVO");
        printf("\n------------------------------------\n");
        printf("\n\t1. Estoque\n\t2. Ficha Técnica\n\t3. Fluxo de caixa\n\t4. Ver funcionários\n\t5. Sair\n");
        printf("\n------------------------------------\n");
        do
            {
                printf("\n\tOpção: ");
                scanf("%d", &selecao);
            } while(selecao <= 0 || selecao > 5);

        switch (selecao)
            {
            case 1:
                ver_estoque();
            case 2:
                ver_lanche();
            case 3:
                fluxo_caixa();
            case 4:
                ver_func();
            case 5:
               menu_principal();
            }

    }
void menu_cliente(void)
    {
        system("cls");
        setlocale(LC_ALL,"portuguese");
        printf("\tMENU");
        printf("\n------------------------------------\n");
        printf("\n\t1. Cardápio\n\t2. Carrinho\n\t3. Sair\n");
        printf("\n------------------------------------\n");
        do
            {
                printf("\n\tOpção: ");
                scanf("%d", &selecao);
            }while( selecao <= 0 || selecao > 3);
        switch (selecao)
            {
            case 1:
                cardapio();
            case 2:
                carrinho();
            case 3:
                menu_principal();
            }

    }

void menu_principal(void)
    {
        system("cls");
        int id;
        char senha[15];
        printf("\n\n\t\tLOGIN");
        printf("\n------------------------------------------------\n");

        printf("\n\t1. Funcionário \n\t2. Cliente");
        printf("\n\tOpção: ");
        scanf("%d", &selecao);
        if(selecao == 1)
            {
                arq = fopen("cadastroFuncionarios.txt", "a");
                if(!arq)
                    {
                        printf("\n\tERRO NO ARQUIVO FUNCIONARIOS.TXT");
                        Sleep(3000);
                        menu_principal();
                    }
                fread(funcionario, sizeof(cadastroFuncionario),1,arq);
                fclose(arq);
                do
                    {
                        system("cls");
                        printf("\n\n\t\tLOGIN FUNCIONÁRIO");
                        printf("\n------------------------------------------------\n");
                        printf("\n\tInforme seu ID: ");
                        fflush(stdin);
                        scanf("%d", &id);
                        if(comparador_func(id) == -1){printf("\n\tUsuário não encontrado");Sleep(3000);}
                    }while (comparador_func(id) == -1);

               do
                    {
                        printf("\n\tInforme a senha: ");
                        fflush(stdin);
                        scanf("%s", senha);
                        if(strcmp(funcionario[comparador_func(id)].senha, senha) != 0){
                                printf("\n\tSenha incorreta!!");
                                Sleep(3000);
                                }
                    }while (strcmp(funcionario[comparador_func(id)].senha, senha) != 0);
                menu_adm();
            }
        else{
            system("cls");
            printf("\n\n\t\tLOGIN CLIENTE");
            printf("\n------------------------------------------------\n");
            printf("\n\tInforme seu nome: ");
            scanf("%s", nome);
            printf("\n\n\tSeja bem vindo %s!!\n\t Estamos direcionando você ao cardápio.", nome);
            Sleep(3000);
            menu_cliente();
        }
    }

int main()
{
    setlocale(LC_ALL,"portuguese");
    menu_principal();

}


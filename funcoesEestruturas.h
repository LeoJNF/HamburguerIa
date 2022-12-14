#ifndef __FUNCOESEESTRUTURAS_H_
#define __FUNCOESEESTRUTURAS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

typedef struct{
    int dia, mes, ano, hora, min, seg;
}Data;

typedef struct
{
    int id;
    char nome[150];
    char email[100];
    char telefone[19];
    char senha[15];
    char funcao[20];
    float salario;
    int nivel;
} cadastroFuncionario;
cadastroFuncionario funcionario[100];

typedef struct{
    int id, dia, mes, ano, hora, min, seg;
    char nome[30], medida[5];
    float peso, valor_total, valor_peso;
}Estoque;
Estoque estoque[100];

typedef struct{
    int id_item, posicao;
    char nome_item[15], medida[5];
    float peso,valor;
}Itens;
Itens insumo[100];

typedef struct{
    int id_lanche, insumo_qtde, posicao;
    char nome_lanche[15];
    float valor_lanche;
}Lanche;
Lanche lanche[100];

struct tm *data_hora_atual;

int tam_funcionario(void) //retorna a quantidade de elementos que o arquivo funcionarios.txt possuí
    {
    FILE *arq;
    arq = fopen("cadastroFuncionarios.txt", "r");
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / 328;
    fclose(arq);
    }

int tam_venda(void) //retorna a quantidade de elementos que o arquivo vendas_lanches.txt possuí
    {
    FILE *arq;
    arq = fopen("venda_lanche.txt", "r");
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / 42;
    fclose(arq);
    }

int tam_ficha_lanche(void) //retorna a quantidade de elementos que o arquivo ficha_lanche.txt possuí
    {
    FILE *arq;
    arq = fopen("ficha_lanche.txt", "r");
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / 32;
    fclose(arq);
    }

int tam_insumos(void) //retorna a quantidade de elementos que o arquivo insumos_lanches.txt possuí
    {
    FILE *arq;
    arq = fopen("insumos_lanches.txt", "r");
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / 36;
    fclose(arq);
    }

int tam_estoque(void) //retorna a quantidade de elementos que o arquivo estoque.txt possuí
    {
    FILE *arq;
    arq = fopen("estoque.txt", "r");
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / 76;
    fclose(arq);
    }

int tam_carrinholl(void) //retorna a quantidade de elementos que o arquivo carrinho_um.txt possuí
    {
    FILE *arq;
    arq = fopen("carrinho_um.txt", "r");
    fseek(arq, 0, SEEK_END);
    return ftell(arq) / 24;
    fclose(arq);
    }
int tam_carrinho(void) //retorna a quantidade de elementos que o arquivo carrinho_dois.txt possuí
    {
    FILE *arq;
    arq = fopen("carrinho_dois.txt", "r");
    fseek(arq, 0,SEEK_END);
    return ftell(arq) / 22;
    fclose(arq);
    }
int comparador_func(int a)// Tem o valor de entrada um ID e compara com IDs, no arquivo cadastroFuncionarios.txt, se o id existe
    {                         // Se já estiver em uso retorna o indice/posição do ID, senão retorna -1.
    int selecao, i, x;
    FILE *arq;
    arq = fopen("cadastroFuncionarios.txt", "r");
    fread(funcionario, sizeof(cadastroFuncionario),1,arq);
    selecao = tam_funcionario();
    fclose(arq);
    for(i=0; i<selecao; i++)
        {
            if(funcionario[i].id== a)
                {
                    x = i;
                    break;
                }
            else
                {
                    x = -1;
                }
            }
            return x;
        }
int comparador_lanche(int a)// Tem o valor de entrada um ID e compara com IDs, no arquivo ficha_lanche.txt, se já está em uso
    {                         // Se já estiver em uso retorna o indice/posição do ID, senão retorna -1.
    int selecao, i, x;
    FILE *arq;
    arq = fopen("ficha_lanche.txt", "r");
    fread(&lanche, sizeof(Lanche),  tam_ficha_lanche(), arq);
    selecao = tam_ficha_lanche();
    fclose(arq);
    for(i=0; i<selecao; i++)
        {
            if(lanche[i].id_lanche == a)
                {
                    x = i;
                    break;
                }
            else
                {
                    x = -1;
                }
            }
            return x;
        }
int comparador_estoque(int a) // Tem o valor de entrada um ID e compara com IDs, no arquivo estoque.txt, se já está em uso
    {                         // Se já estiver em uso retorna o indice/posição do ID, senão retorna -1.
    int selecao, i, x;
    FILE *arq;
    arq = fopen("estoque.txt", "r");
    selecao = tam_estoque();
    fread(&estoque, sizeof(Estoque), selecao, arq);
    fclose(arq);
    for(i=-1; i<selecao; i++)
        {
            if(estoque[i].id == a)
                {
                    x = i;
                    break;
                }
            else
                {
                    x = -1;
                }
            }
            return x;

        }



void inicializador_insumo(void)//Incicializa a estrutura Itens, atribuindo valores Null ou 0;
    {
        int i;
        for(i=0; i<tam_insumos(); i++)
            {
                insumo[i].id_item = 0;
                insumo[i].posicao = 0;
                strcpy(insumo[i].nome_item, "NULL");
                strcpy(insumo[i].medida, "NULL");
                insumo[i].valor = 0.0;
                insumo[i].peso = 0.0;
            }
    }

void inicializador_lanche(void)//Incicializa a estrutura Lanche, atribuindo valores Null ou 0;
    {
        int i;
        for(i=0; i<tam_ficha_lanche(); i++)
            {
                lanche[i].id_lanche = 0;
                lanche[i].insumo_qtde = 0;
                lanche[i].posicao = 0;
                strcpy(lanche[i].nome_lanche, "NULL");
                lanche[i].valor_lanche = 0.0;
            }
    }

void inicializador_estoque(void)//Incicializa a estrutura estoque, atribuindo valores Null ou 0;
    {
        int i;
        for(i=0; i<tam_estoque(); i++)
            {
                estoque[i].id = 0;
                strcpy(estoque[i].nome, "NULL");
                estoque[i].peso = 0.0;
                strcpy(estoque[i].medida, "NULL");
                estoque[i].valor_peso = 0.0;
                estoque[i].valor_total = 0.0;
                estoque[i].dia = 0;
                estoque[i].mes = 0;
                estoque[i].ano = 0;
                estoque[i].hora = 0;
                estoque[i].min = 0;
                estoque[i].seg = 0;
            }
    }


#endif // FUNCOESEESTRUTURAS_H_INCLUDED

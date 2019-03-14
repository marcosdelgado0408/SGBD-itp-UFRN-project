#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgbd.h"

int criarTabela(){

    FILE *keys;
    FILE *dados;
    FILE *todos_nomes_tabela = fopen("tabelas/nomes_tabelas.txt", "a");

    int voltar = 0;
    int quant_colunas, i, j;
    int quant_linhas = 0;
    char option;
    char *nome_tabela = (char *)malloc(20 * sizeof(char));
    char *nome_coluna = (char *)malloc(20 * sizeof(char));
    char *nome_chave_primaria = (char *)malloc(20 * sizeof(char));
    char *colocar_em_nome_tabela = (char *)malloc(20 * sizeof(char));
    char s[20];
    char tipo_elemento;
    char conversor;
    char key[40] = {"tabelas/keys_"};

    strcpy(nome_tabela, "tabelas/");

    do{
        printf("Deseja criar uma tabela?(s/n): ");
        scanf(" %c", &option);
        conversor = toupper(option);
    }while(conversor != 'S' && conversor != 'N');
    printf("\n");

    if (option == 's'){

        do{
            FILE *arquivo_lista = fopen("tabelas/nomes_tabelas.txt", "r");
            voltar = 0;
            printf("Digite o nome da tabela: ");
            scanf("%s", colocar_em_nome_tabela); //escanear o nome da tabela
            printf("\n");

            while (fscanf(arquivo_lista, "%s", s) != EOF){            
                if(strcmp(s,colocar_em_nome_tabela) == 0){                                                
                    printf("A tabela '%s' já existe\n", colocar_em_nome_tabela);
                    voltar = 1;                  //Checa se a tabela já existe
                    fclose(arquivo_lista);
                }else{
                    continue;
                }
            }
        }while(voltar == 1);

        strcat(key, colocar_em_nome_tabela);

        fprintf(todos_nomes_tabela, "%s\n", colocar_em_nome_tabela); //vai botar o nome da tabela nas listas de nomes de tabelas
        
        strcat(nome_tabela, colocar_em_nome_tabela); // vai ficar: tabelas/"nome da tabela"

        strcat(nome_tabela, ".txt"); // vai ficar: tabelas/"nome da tabela".txt

        dados = fopen(nome_tabela, "w"); //criar arquivo de tabela: tabelas/"nome da tabela".txt
        

        if (dados == NULL){
            printf("ERRO NA ABERTURA DO ARQUIVO %s\n", nome_tabela);
            return -1;
        }

        strcat(key, ".txt");
        keys = fopen(key, "w");

        if (keys == NULL){
            printf("ERRO NA ABERTURA DO ARQUIVO %s", key);
        }

        printf("Digite a quantidade de colunas da tabela: ");
        scanf("%i", &quant_colunas); //escanear a quantidade de colunas
        printf("\n");

        printf("Digite o nome da coluna para ser a chave primária: ");
        scanf("%s", nome_chave_primaria); //escanear chave primara
        printf("\n");

        fprintf(dados, "%i\n", quant_linhas);        //printar a quantidade de linhas no .txt
        fprintf(dados, "%i\n", quant_colunas);       //printar a quant de colunas no .txt
        fprintf(dados, "%s\n", nome_chave_primaria); //vai printar o nome da chave primaria no .txt

        for (i = 0; i < quant_colunas; i++){
            printf("Digite o nome da coluna %i da tabela: ", i + 1);
            scanf("%s", nome_coluna); //escanear o nome de uma coluna
            printf("\n");
            fprintf(dados, "%s\n", nome_coluna);

            do{
                printf("Digite o tipo (Float->F/Int->I/Char->C/Double->D/String->S) da coluna %i da tabela: ", i + 1);
                scanf(" %c", &tipo_elemento);   //escaneia o tipo da coluna e verifica se o tipo é compatível
                conversor = toupper(tipo_elemento);
            }while(conversor != 'F' && conversor != 'D' && conversor != 'C' && conversor != 'I' && conversor != 'S');
            printf("\n");
            fprintf(dados, "%c\n", conversor);
        }

    }else{
        printf("OK, não será criada uma tabela\n");
        return 1;
    }

    free(nome_tabela);
    free(nome_coluna);
    free(nome_chave_primaria);
    free(colocar_em_nome_tabela);

    fclose(keys);
    fclose(dados);
    fclose(todos_nomes_tabela);
    return 0;
}
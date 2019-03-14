#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "sgbd.h"

int excluirTabela()
{
    FILE *temp_lista = fopen("tabelas/temp_lista.txt", "w");
    char nada[50];
    char option, conversor;
    char linha[100];
    char nome_tabela[100];
    char dir_meta[100] = {"tabelas/"};
    char dir_tabela[100] = {"tabelas_preenchidas/"};
    char dir_keys[100] = {"tabelas/keys_"};


    do{
        printf("Deseja excluir uma tabela?(s/n): ");
        scanf(" %c", &option);
        conversor = toupper(option);
    }while(conversor != 'S' && conversor != 'N');
    printf("\n");

    
    if (option == 's' || option == 'S')
    {
        
        printf("Tabela a ser excluida >> ");
        scanf("%s", nome_tabela);
        strcat(dir_meta, nome_tabela);
        strcat(dir_meta, ".txt");

        strcat(dir_tabela, nome_tabela);
        strcat(dir_tabela, ".txt");
        
        FILE *meta = fopen(dir_meta, "r");
        if (!meta)
        {
            printf("A tabela '%s' não existe\n", nome_tabela);
            return 0;
        }
        FILE *tabelas = fopen("tabelas/nomes_tabelas.txt", "r");
        if (!tabelas)
        {
            printf("A tabela 'nomes_tabelas.txt' não existe\n");
            return 0;
        }
        
        while (fscanf(tabelas, "%s", linha) != EOF)
        {
            if (strcmp(nome_tabela, linha) == 0)
            {
                fprintf(temp_lista, "", nada);
            }
            else
            {
                fprintf(temp_lista, "%s\n", linha);
            }
        }

        strcat(dir_keys, nome_tabela);
        strcat(dir_keys, ".txt");

        remove(dir_meta);
        remove(dir_keys);
        remove(dir_tabela);

        fclose(tabelas);
        fclose(meta);
        fclose(temp_lista);

        /* copiar tudo do arquivo temporário e jogar para o arquivo original*/

        FILE *copiar_lista = fopen("tabelas/temp_lista.txt", "r");
        FILE *lista = fopen("tabelas/nomes_tabelas.txt", "w");

        char str[50];

        while (fscanf(copiar_lista, "%s", str) != EOF)
        {
            fprintf(lista, "%s\n", str);
        }

        fclose(copiar_lista);
        fclose(lista);

        remove("tabelas/temp_lista.txt");
    }
    else
    {
        return 0;
    }
    return 0;
}
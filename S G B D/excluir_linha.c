#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"
#include "sgbd.h"
#define MAX 256

int excluirLinha()
{

    char option, conversor;

    do{
        printf("Deseja criar uma linha?(s/n): ");
        scanf(" %c", &option);
        conversor = toupper(option);
    }while(conversor != 'S' && conversor != 'N');
    printf("\n");

    if (option == 's')
    {

        char abrir_tabela[50];
        char diretorio_tabelas_preenchidas[50];
        char abrir_chaves[50];

        strcpy(diretorio_tabelas_preenchidas, "tabelas_preenchidas/");
        strcpy(abrir_chaves, "tabelas/keys_");

        printf("Digite o nome da tabela: ");
        scanf("%s", abrir_tabela);

        strcat(diretorio_tabelas_preenchidas, abrir_tabela);
        strcat(abrir_chaves, abrir_tabela);

        strcat(abrir_chaves, ".txt");
        strcat(diretorio_tabelas_preenchidas, ".txt");

        FILE *tabela = fopen(diretorio_tabelas_preenchidas, "r");
        printf("\n");

        if (tabela == NULL)
        {
            printf("ERRO NA ABERTURA DO ARQUIVO DA TABELA PREENCHIDA\n");
            return -1;
        }

        FILE *temp = fopen("tabelas_preenchidas/temporario.txt", "w");

        FILE *temp_keys = fopen("tabelas_preenchidas/temporario_keys.txt", "w");

        FILE *chaves = fopen(abrir_chaves, "r");
        if (abrir_chaves == NULL)
        {
            printf("ERRO NA ABERTURA DO ARQUIVO %s", abrir_chaves);
            return -1;
        }

        char str[MAX];
        char chave[50];
        char scan_chave[20];
        char nada[20];
        char nada2[20];

        printf("Chave primária: ");
        scanf("%s", chave);

        fgets(nada2, 100, tabela);

        fprintf(temp, "\n");

        while (!feof(tabela))
        { // vai pegar a primeira chave primaria e a linha desejada p apagar

            fscanf(chaves, "%s", scan_chave); // vai pegar a chave primaria da tabela de chaves

            fgets(str, MAX, tabela); // vai pegar a linha da tabela

            if (strcmp(chave, scan_chave) == 0)
            { // essa é a condição de pular a string
                fprintf(temp, "", str);
                fprintf(temp_keys, "", nada);
            }
            else
            {
                fprintf(temp, "%s", str); // vai imprimir a palavra
                fprintf(temp_keys, "%s\n", scan_chave);
            }
        }

        fclose(tabela);
        fclose(temp);
        fclose(temp_keys);
        fclose(chaves);

        char linha[50];
        char linha_key[50];
        char abrir_key[60];

        FILE *tabela2 = fopen(diretorio_tabelas_preenchidas, "w");
        FILE *temp2 = fopen("tabelas_preenchidas/temporario.txt", "r");
        FILE *temp2_keys = fopen("tabelas_preenchidas/temporario_keys.txt", "r");

        strcpy(abrir_key, "tabelas/keys_");

        strcat(abrir_key, abrir_tabela);

        strcat(abrir_key, ".txt");

        FILE *chaves2 = fopen(abrir_key, "w");

        while (fgets(linha, MAX, temp2) != NULL)
        { // igual na hora de imprimir -> so que dessa vez no arquivo das linhas
            fprintf(tabela2, "%s", linha);
        }

        while (fgets(linha_key, MAX, temp2_keys) != NULL)
        {
            fprintf(chaves2, "%s", linha_key);
        }

        remove("tabelas_preenchidas/temporario.txt");
        remove("tabelas_preenchidas/temporario_keys.txt");

        fclose(tabela2);
        fclose(temp2);
        fclose(temp2_keys);
        fclose(chaves2);
    }
    else
    {
        printf("OK, não será apagada uma linha\n");
        return 0;
    }
    return 0;
}
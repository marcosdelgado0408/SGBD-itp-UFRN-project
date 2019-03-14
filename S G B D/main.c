#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgbd.h"

void printLogo();

int main()
{
    char option;
    printLogo();
    do
    {
        printf("SGBD (h para ajuda) >> ");
        scanf(" %s", &option);
        while (option != '1' && option != '2' && option != '3' && option != '4' && option != '5' && option != '6' && option != '7' && option != '8' && option != '0' && option != 'h')
        {
            printf("\nCOMANDO INVÁLIDO\n");
            printf("SGBD (h para ajuda) >> ");
            scanf(" %s", &option);
        }
        printf("\n");

        switch (option)
        {
        case '0':
            return 0;

        case '1':
            criarTabela();
            printf("\n");
            break;

        case '2':
            listarTabelas();
            printf("\n");
            break;

        case '3':
            criarLinha();
            printf("\n");
            break;

        case '4':
            imprimirTabela();
            printf("\n");
            break;

        case '5':
            pesquisarValor();
            printf("\n");
            break;

        case '6':
            excluirLinha();
            printf("\n");
            break;

        case '7':
            excluirTabela();
            printf("\n");
            break;
        
        case '8':
            mudarColuna();
            printf("\n");
            break;

        case 'h':
            printf(" 1 - Criar tabela\n");
            printf(" 2 - Listar todas tabelas\n");
            printf(" 3 - Criar uma nova linha\n");
            printf(" 4 - Listar todos os dados da tabela\n");
            printf(" 5 - Pesquisar valor em uma tabela\n");
            printf(" 6 - Apagar linha em uma tabela\n");
            printf(" 7 - Apagar uma tabela\n");
            printf(" 8 - Mudar nome de coluna\n");
            printf(" 0 - Sair do sistema\n\n");
            break;
                }
    } while (1);
    return 0;
}

void printLogo()
{
    printf(" _______  _______  _______  ______              ___   _______  _______ \n");
    printf("|       ||       ||  _    ||      |            |   | |       ||       |\n");
    printf("|  _____||    ___|| |_|   ||  _    |   ____    |   | |_     _||    _  |\n");
    printf("| |_____ |   | __ |       || | |   |  |____|   |   |   |   |  |   |_| |\n");
    printf("|_____  ||   ||  ||  _   | | |_|   |           |   |   |   |  |    ___|\n");
    printf(" _____| ||   |_| || |_|   ||       |           |   |   |   |  |   |    \n");
    printf("|_______||_______||_______||______|            |___|   |___|  |___|    \n\n");
}
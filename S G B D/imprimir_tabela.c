#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgbd.h"

int imprimirTabela()
{

	char *abrir_em_tabela_preenchida = (char *)malloc(60 * sizeof(char));
	char *abrir_em_tabelas = (char *)malloc(60 * sizeof(char));
	char *aux = (char *)malloc(60 * sizeof(char));
	char nada[50];

	strcpy(abrir_em_tabela_preenchida, "tabelas_preenchidas/");
	strcpy(abrir_em_tabelas, "tabelas/");

	printf("Digite a tabela que gostaria de mostrar:  ");
	scanf("%s", aux);

	printf("\n");

	strcat(abrir_em_tabela_preenchida, aux);
	strcat(abrir_em_tabelas, aux); //td isso para abrir no diretorio que eu quero

	strcat(abrir_em_tabela_preenchida, ".txt");
	strcat(abrir_em_tabelas, ".txt");

	//-----------------------------------------------------------------------------

	FILE *abrir_tabela = fopen(abrir_em_tabela_preenchida, "r"); // vai abrir tabelas_preenchidas/"nome da tabela".txt
	if (abrir_tabela == NULL)
	{
		printf("ERRO NA ABERTURA DO ARQUIVO >>%s<<\nAinda não existem valores na tabela!!!\nADICIONE UMA LINHA PRIMEIRO\n", abrir_em_tabela_preenchida);
		return -1;
	}

	FILE *abrir_nome_colunas = fopen(abrir_em_tabelas, "r"); // vai abrir tabelas/"nome da tabela".txt
	if (abrir_nome_colunas == NULL)
	{
		printf("ERRO NA ABERTURA DO ARQUIVO >>%s<<", abrir_em_tabelas);
		return -1;
	}

	int num_colunas;
	int lixo;
	int i;
	char *nome_coluna = (char *)malloc(20 * sizeof(char));
	char *dados = (char *)malloc(300 * sizeof(char));
	char nada2[50];

	fscanf(abrir_nome_colunas, "%i", &lixo); // vai pular o primiero numero do arquivo -> num linhas

	fscanf(abrir_nome_colunas, "%i", &num_colunas);

	fscanf(abrir_nome_colunas, "%s", nome_coluna); // vai pegar a coluna da chave primaria pra imprimir
	printf("%-25s", nome_coluna);				   // vai imprimir a coluna da chave primária

	for (i = 0; i < num_colunas; i++)
	{
		fscanf(abrir_nome_colunas, "%s", nome_coluna);
		printf("%-25s", nome_coluna);
		fscanf(abrir_nome_colunas, "%s", nada2);
	}

	printf("\n");

	fgets(nada, 100, abrir_tabela); // vai pular a linha em branco do arquivo

	while (fgets(dados, BUFSIZ, abrir_tabela) != NULL)
	{
		printf("%s", dados);
	}

	printf("\n");

	free(abrir_em_tabela_preenchida);
	free(aux);
	free(abrir_em_tabelas);
	free(dados);
	free(nome_coluna);

	fclose(abrir_tabela);
	fclose(abrir_nome_colunas);

	return 0;
}
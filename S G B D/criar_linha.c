#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgbd.h"

typedef struct tabela
{
	int num_int;
	char string[50];
	float num_float;
	double num_double;
	char caractere;
} Tabela;

int criarLinha()
{
	char option, conversor;
	int check, ctrl;

	do
	{
		printf("Deseja criar uma nova linha?(s/n): ");
		scanf(" %c", &option);
		conversor = toupper(option);
	} while (conversor != 'S' && conversor != 'N');
	printf("\n");

	if (option == 's')
	{

		char *nome_tabela1 = (char *)malloc(50 * sizeof(char));
		char *nome_tabela_preenchida1 = (char *)malloc(50 * sizeof(char));
		char *aux = (char *)malloc(50 * sizeof(char));
		char key[40] = {"tabelas/keys_"};

		strcpy(nome_tabela1, "tabelas/");
		strcpy(nome_tabela_preenchida1, "tabelas_preenchidas/");

		printf("Digite o nome da tabela: ");
		scanf("%s", aux);

		printf("\n");

		strcat(nome_tabela1, aux);
		strcat(nome_tabela_preenchida1, aux);
		strcat(key, aux);

		strcat(nome_tabela1, ".txt");
		strcat(nome_tabela_preenchida1, ".txt");
		strcat(key, ".txt");

		//------------------------------------------------------------------------------

		FILE *keys = fopen(key, "r+");
		if (keys == NULL)
		{
			printf("ERRO na abertura do arquivo %s\n", key);
			return -1;
		}

		FILE *dados_tabela_criada = fopen(nome_tabela1, "r");
		if (dados_tabela_criada == NULL)
		{
			printf("ERRO NA ABERTURA DO ARQUIVO\n");
			return -1;
		}

		FILE *tabela_preenchida = fopen(nome_tabela_preenchida1, "a");
		if (tabela_preenchida == NULL)
		{
			printf("ERRO NA ABERTURA DO ARQUIVO\n");
			return -1;
		}

		int quant_linhas = 0;
		int quant_colunas = 0;
		int i, j;

		char *nome_chave_primaria = (char *)malloc(20 * sizeof(char));

		int *vetor_chaves_primarias = (int *)malloc(20 * sizeof(int));

		fscanf(dados_tabela_criada, "%i", &quant_linhas); //pegar a quant de linhas

		fscanf(dados_tabela_criada, "%i", &quant_colunas); // pegar a quant de colunas

		quant_colunas++; //por causa da coluna da chave primária

		fscanf(dados_tabela_criada, "%s", nome_chave_primaria); //pegar nome da chave primaria

		Tabela tabela[quant_colunas];

		char *nome_coluna = (char *)malloc(20 * sizeof(char));
		char tipo_coluna;

		char chave[50];
		int voltar = 1;

		printf("NOVA LINHA:\n");

		//CHAVE PRIMARIA

		fprintf(tabela_preenchida, "\n");

		while (voltar == 1)
		{
			printf("Digite o que gostaria de botar em >>%s<<: ", nome_chave_primaria); //bota ai porque é somente um id por linha
			scanf("%s", tabela[0].string);
			voltar = 0;
			for (i = 0; i < strlen(tabela[0].string); i++)
			{
				if (!isdigit(tabela[0].string[i]))
				{ // se n for numero
					printf("ERRO -> o valor deve ser inteiro\n\n");
					voltar = 1;
					break;
				}
			}
		}
		voltar = 1;

		while (!feof(keys))
		{
			fscanf(keys, "%s", chave);
			while (strcmp(chave, tabela[0].string) == 0)
			{
				printf("chave primária ja existe!\nDigite novemente o que gostaria de botar em >>%s<<:  ", nome_chave_primaria);
				scanf("%s", tabela[0].string);
			}
		}

		printf("\n");
		fprintf(keys, "%s\n", tabela[0].string);
		fprintf(tabela_preenchida, "%-25s", tabela[0].string); // imprimir valor chave primaria

		for (i = 1; i < quant_colunas; i++)
		{

			fscanf(dados_tabela_criada, "%s", nome_coluna);

			fscanf(dados_tabela_criada, " %c", &tipo_coluna);

			//VALORES COLUNAS

			if (tipo_coluna == 'I')
			{
				while (voltar == 1)
				{
					printf("Digite o que gostaria de botar em >>%s<<: ", nome_coluna); //bota ai porque é somente um id por linha
					scanf("%s", tabela[i].string);
					printf("\n");
					voltar = 0;
					for (j = 0; j < strlen(tabela[i].string); j++)
					{
						if (!isdigit(tabela[i].string[j]))
						{ // se n for numero
							printf("ERRO -> o valor deve ser inteiro\n\n");
							voltar = 1;
							break;
						}
					}
				}
				voltar = 1;

				fprintf(tabela_preenchida, "%-25s", tabela[i].string);
			}

			else if (tipo_coluna == 'F')
			{
				ctrl = 0;
				while (voltar == 1)
				{
					printf("Digite o que gostaria de botar em >>%s<<: ", nome_coluna);
					scanf("%s", tabela[i].string);
					printf("\n");
					voltar = 0;
					for (j = 0; j < strlen(tabela[i].string); j++)
					{
						if (isdigit(tabela[i].string[j]) == 0)
						{
							continue;
						}
						else
						{
							if (ispunct(tabela[i].string[j]) != 0)
							{
								ctrl++;
								break;
							}
						}
					}
					if (ctrl > 0 && ctrl < 2)
					{
						printf("ERRO -> o valor deve ser float\n\n");
						voltar = 1;
					}
				}
				voltar = 1;

				fprintf(tabela_preenchida, "%-25s", tabela[i].string);
			}

			else if (tipo_coluna == 'D')
			{
				while (voltar == 1)
				{
					printf("Digite o que gostaria de botar em >>%s<<: ", nome_coluna);
					scanf("%s", tabela[i].string);
					printf("\n");
					voltar = 0;
					for (j = 0; j < strlen(tabela[i].string); j++)
					{
						if (isdigit(tabela[i].string[j]) == 0)
						{
							continue;
						}
						else
						{
							if (ispunct(tabela[i].string[j]) != 0)
							{
								ctrl++;
								break;
							}
						}
					}
					if (ctrl > 0 && ctrl < 2)
					{
						printf("ERRO -> o valor deve ser double\n\n");
						voltar = 1;
					}
				}
				voltar = 1;

				fprintf(tabela_preenchida, "%-25s", tabela[i].string);
			}

			else if (tipo_coluna == 'C')
			{
				while (voltar == 1)
				{
					printf("Digite o que gostaria de botar em >>%s<<: ", nome_coluna);
					scanf("%s",  tabela[i].string);
					printf("\n");
					voltar = 0;
					if (strlen(tabela[i].string) > 1)
					{
						printf("ERRO -> o valor deve ser char\n\n");
						voltar = 1;
					}
					else
					{
						continue;
					}
				}
				voltar = 1;

				fprintf(tabela_preenchida, "%-25s", tabela[i].string);
			}

			else if (tipo_coluna == 'S')
			{
				printf("Digite o que gostaria de botar em >>%s<<: ", nome_coluna);
				scanf("%s", tabela[i].string);
				printf("\n");
				fprintf(tabela_preenchida, "%-25s", tabela[i].string);
			}
		}

		free(nome_tabela1);
		free(nome_tabela_preenchida1);
		free(aux);
		free(nome_chave_primaria);
		free(nome_coluna);
		free(vetor_chaves_primarias);

		fclose(keys);
		fclose(dados_tabela_criada);
		fclose(tabela_preenchida);
	}
	else
	{
		printf("OK, não será criada uma linha.\n");
		return 0;
	}

	return 0;
}
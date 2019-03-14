#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgbd.h"
#define MAX 300

int pesquisarValor()
{
	char option, conversor;

    do{
        printf("Gostaria de pesquisar valor em uma tabela(s/n): ");
        scanf(" %c", &option);
        conversor = toupper(option);
    }while(conversor != 'S' && conversor != 'N');
	printf("\n");

	if (option == 's'){

		char *nome_tabela = (char *)malloc(50 * sizeof(char));
		char *dir_meta = (char *)malloc(50 * sizeof(char));
		char *chave_primaria = (char *)malloc(50 * sizeof(char));
		char *nome_coluna = (char *)malloc(50 * sizeof(char));
		char *dir_tabela = (char *)malloc(50 * sizeof(char));
		char *receber_valor = (char *)malloc(50 * sizeof(char));
		char *scan_valor = (char *)malloc(50 * sizeof(char));
		char *tipo_coluna = (char *)malloc(50 * sizeof(char));
		char usar_tipo;
		char op;
		int i;
		int receber_coluna;
		int quant_colunas;
		char dado_coluna_indesejada[MAX];
		char nada[MAX];
		char nada2[MAX];
		char nada3[MAX];
		char nada4[MAX];
		char linha[MAX];
		char linha_temp[MAX];
		int lixo;
		int chartoint;
		int receber_valor_pra_int;
		float chartofloat;
		float receber_valor_pra_float;

		strcpy(dir_meta, "tabelas/");

		strcpy(dir_tabela, "tabelas_preenchidas/");

		printf("Informe o nome da tabela onde será realizada a pesquisa: ");
		scanf("%s", nome_tabela);
		printf("\n");

		strcat(dir_meta, nome_tabela);
		strcat(dir_meta, ".txt");

		strcat(dir_tabela, nome_tabela);
		strcat(dir_tabela, ".txt");

		FILE *metadados = fopen(dir_meta, "r");
		if (metadados == NULL){
			printf("ERRO NA ABERTURA DO ARQUIVO %s\n", dir_meta);
			return -1;
		}

		FILE *tabela = fopen(dir_tabela, "r");
		if (tabela == NULL){
			printf("ERRO NA ABERTURA DO ARQUIVO %s\n", dir_tabela);
			return -1;
		}
		//-------------------------------------------------------------------------------
		FILE *temp = fopen("temporario.txt", "w");
		if (temp == NULL){
			printf("ERRO NA ABERTURA DO ARQUIVO temporario.txt\n");
			return -1;
		}

		while (fgets(linha, MAX, tabela) != NULL){
			fprintf(temp, "%s", linha);
		}

		fclose(temp);

		// copiei o arquivo da tabela para um arquivo temporario para ler-lo

		fseek(tabela, 0, SEEK_SET);

		//-------------------------------------------------------------------------------
		FILE *read_temp = fopen("temporario.txt", "r");
		if (read_temp == NULL){
			printf("ERRO NA ABERTURA DO ARQUIVO temporario.txt\n");
			return -1;
		}

		fscanf(metadados, "%i", &lixo); // pular a quant de linhas

		fscanf(metadados, "%i", &quant_colunas); // escanear quantidade de colunas

		fscanf(metadados, "%s", chave_primaria); // escanear chave primaria

		printf("COLUNAS EXISTENTES:\n");

		printf("1:%s  ", chave_primaria);

		tipo_coluna[0] = 'I'; // tipo da chave primaria

		for(i=1;i<quant_colunas+1;i++){
			fscanf(metadados, "%s", nome_coluna);
			fscanf(metadados, " %c", &tipo_coluna[i]);

			printf("%i:%s  ", i + 1, nome_coluna);
		}
		printf("\n\n");

		printf("Selecione o numero da coluna que gotaria de pesquisar o valor:  ");
		scanf("%i", &receber_coluna); // vai receber o numero que será a posição da coluna
		printf("\n");

		usar_tipo = tipo_coluna[receber_coluna - 1]; // vai pegar o tipo da coluna que a pessoa digitou

		printf("Digite um valor para pesquisar: ");
		scanf("%s", receber_valor);

		printf("\n");
		printf(" 1 - valores maior que o valor informado\n");
		printf(" 2 - valores maior ou igual que o valor informado\n");
		printf(" 3 - valores igual o valor informado\n");
		printf(" 4 - valores menor que o valor informado\n");
		printf(" 5 - valores menor ou igual que o valor informado\n");
		printf(" 6 - valores próximo ao valor informado\n");
		printf("\n");

		printf("Digite uma opção: ");
		scanf(" %c", &op);
		printf("\n");

		//-----------------------------------------------------------------------------------------------------
		fseek(metadados, 0, SEEK_SET);

		fscanf(metadados, "%i", &lixo); // pular a quant de linhas

		fscanf(metadados, "%i", &quant_colunas); // escanear quantidade de colunas

		fscanf(metadados, "%s", chave_primaria); // escanear chave primaria

		printf("%-25s", chave_primaria);

		for(i=1;i<quant_colunas+1;i++){
			fscanf(metadados, "%s", nome_coluna);
			fscanf(metadados, " %c", &tipo_coluna[i]);
			printf("%-25s", nome_coluna);
		}
		printf("\n");

		//-----------------------------------------------------------------------------------------------------

		fgets(nada4, MAX, read_temp);
		fgets(nada3, MAX, tabela);

		if (op == '1'){
			while (!feof(tabela) && !feof(read_temp)){

				for (i = 0; i < receber_coluna - 1; i++){ // vai ser -1 por causa que eu quero acessar a coluna do numero desejado, e não pular ela
					fscanf(tabela, "%s", dado_coluna_indesejada); // vai pular as colunas indesejadas
				}

				fscanf(tabela, "%s", scan_valor); // vai escanear o valor da coluna desejada//botei um \n e du certo

				//------------------------------------------------------------------------------------------
				if (usar_tipo == 'I'){
					chartoint = atoi(scan_valor);				 // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_int = atoi(receber_valor); // transformar o valor recebido em inteiro
					if (chartoint > receber_valor_pra_int){
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'F')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em float
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em float
					if (chartofloat > receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'D')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em inteiro
					if (chartofloat > receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'C')
				{
					if (receber_valor[0] > scan_valor[0])
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'S')
				{
					if (strcmp(receber_valor, scan_valor) > 0)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				fgets(nada4, MAX, tabela); // pegar o resto da linha na hr de escanear a tabela original
			}
		}

		else if (op == '2')
		{

			while (!feof(tabela) && !feof(read_temp))
			{

				for (i = 0; i < receber_coluna - 1; i++)
				{												  // vai ser -1 por causa que eu quero acessar a coluna do numero desejado, e não pular ela
					fscanf(tabela, "%s", dado_coluna_indesejada); // vai pular as colunas indesejadas
				}

				fscanf(tabela, "%s", scan_valor); // vai escanear o valor da coluna desejada//botei um \n e du certo

				//------------------------------------------------------------------------------------------
				if (usar_tipo == 'I')
				{
					chartoint = atoi(scan_valor);				 // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_int = atoi(receber_valor); // transformar o valor recebido em inteiro
					if (chartoint >= receber_valor_pra_int)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'F')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em float
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em float
					if (chartofloat >= receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'D')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em inteiro
					if (chartofloat >= receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'C')
				{
					if (receber_valor[0] >= scan_valor[0])
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'S')
				{
					if (strcmp(receber_valor, scan_valor) >= 0)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				fgets(nada4, MAX, tabela); // pegar o resto da linha na hr de escanear a tabela original
			}
		}

		else if (op == '3')
		{

			while (!feof(tabela) && !feof(read_temp))
			{

				for (i = 0; i < receber_coluna - 1; i++)
				{												  // vai ser -1 por causa que eu quero acessar a coluna do numero desejado, e não pular ela
					fscanf(tabela, "%s", dado_coluna_indesejada); // vai pular as colunas indesejadas
				}

				fscanf(tabela, "%s", scan_valor); // vai escanear o valor da coluna desejada//botei um \n e du certo

				//------------------------------------------------------------------------------------------
				if (usar_tipo == 'I')
				{
					chartoint = atoi(scan_valor);				 // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_int = atoi(receber_valor); // transformar o valor recebido em inteiro
					if (chartoint == receber_valor_pra_int)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'F')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em float
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em float
					if (chartofloat == receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'D')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em inteiro
					if (chartofloat == receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'C')
				{
					if (receber_valor[0] == scan_valor[0])
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'S')
				{
					if (strcmp(receber_valor, scan_valor) == 0)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				fgets(nada4, MAX, tabela); // pegar o resto da linha na hr de escanear a tabela original
			}
		}

		else if (op == '4')
		{

			while (!feof(tabela) && !feof(read_temp))
			{

				for (i = 0; i < receber_coluna - 1; i++)
				{												  // vai ser -1 por causa que eu quero acessar a coluna do numero desejado, e não pular ela
					fscanf(tabela, "%s", dado_coluna_indesejada); // vai pular as colunas indesejadas
				}

				fscanf(tabela, "%s", scan_valor); // vai escanear o valor da coluna desejada//botei um \n e du certo

				//------------------------------------------------------------------------------------------
				if (usar_tipo == 'I')
				{
					chartoint = atoi(scan_valor);				 // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_int = atoi(receber_valor); // transformar o valor recebido em inteiro
					if (chartoint < receber_valor_pra_int)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'F')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em float
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em float
					if (chartofloat < receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'D')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em inteiro
					if (chartofloat < receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'C')
				{
					if (receber_valor[0] < scan_valor[0])
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'S')
				{
					if (strcmp(receber_valor, scan_valor) < 0)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				fgets(nada4, MAX, tabela); // pegar o resto da linha na hr de escanear a tabela original
			}
		}

		else if (op == '5')
		{
			while (!feof(tabela) && !feof(read_temp))
			{

				for (i = 0; i < receber_coluna - 1; i++)
				{												  // vai ser -1 por causa que eu quero acessar a coluna do numero desejado, e não pular ela
					fscanf(tabela, "%s", dado_coluna_indesejada); // vai pular as colunas indesejadas
				}

				fscanf(tabela, "%s", scan_valor); // vai escanear o valor da coluna desejada//botei um \n e du certo

				//------------------------------------------------------------------------------------------
				if (usar_tipo == 'I')
				{
					chartoint = atoi(scan_valor);				 // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_int = atoi(receber_valor); // transformar o valor recebido em inteiro
					if (chartoint <= receber_valor_pra_int)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'F')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em float
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em float
					if (chartofloat <= receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'D')
				{
					chartofloat = atof(scan_valor);				   // transformar o valor escaneado da tabela em inteiro
					receber_valor_pra_float = atof(receber_valor); // transformar o valor recebido em inteiro
					if (chartofloat <= receber_valor_pra_float)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'C')
				{
					if (receber_valor[0] <= scan_valor[0])
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				else if (usar_tipo == 'S')
				{
					if (strcmp(receber_valor, scan_valor) <= 0)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				fgets(nada4, MAX, tabela); // pegar o resto da linha na hr de escanear a tabela original
			}
		}

		else if (op == '6')
		{
			while (!feof(tabela) && !feof(read_temp))
			{

				for (i = 0; i < receber_coluna - 1; i++)
				{												  // vai ser -1 por causa que eu quero acessar a coluna do numero desejado, e não pular ela
					fscanf(tabela, "%s", dado_coluna_indesejada); // vai pular as colunas indesejadas
				}

				fscanf(tabela, "%s", scan_valor); // vai escanear o valor da coluna desejada
				//------------------------------------------------------------------------------------------
				if (usar_tipo == 'I')
				{
					printf("Essa função funciona somente para o tipo 'string' -> 'S'\n");
					return -1;
				}
				else if (usar_tipo == 'F')
				{
					printf("Essa função funciona somente para o tipo 'string' -> 'S'\n");
					return -1;
				}
				else if (usar_tipo == 'D')
				{
					printf("Essa função funciona somente para o tipo 'string' -> 'S'\n");
					return -1;
				}
				else if (usar_tipo == 'C')
				{
					printf("Essa função funciona somente para o tipo 'string' -> 'S'\n");
					return -1;
				}
				else if (usar_tipo == 'S')
				{
					if (strstr(scan_valor, receber_valor) != NULL)
					{
						fgets(linha_temp, MAX, read_temp);
						printf("%s", linha_temp);
					}
					else
					{
						fgets(linha_temp, MAX, read_temp); // vai pular a linha que n quero imprimir
					}
				}

				fgets(nada4, MAX, tabela); // pegar o resto da linha na hr de escanear a tabela original
			}
		}

		remove("temporario.txt");

		free(nome_tabela);
		free(dir_meta);
		free(chave_primaria);
		free(nome_coluna);
		free(dir_tabela);
		free(receber_valor);
		free(scan_valor);
		free(tipo_coluna);
		fclose(metadados);
		fclose(tabela);
		fclose(read_temp);
	}

	return 0;
}

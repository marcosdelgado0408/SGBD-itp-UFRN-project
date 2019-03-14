#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgbd.h"


int mudarColuna(){

    char nome_tabela[50];
    char linha[100];
    char nomecol[100];
    char chaveprimaria[60];
    int i;
    int ncoluna;
    char tipo[50];

    char dir_tabela[250];

    printf("Digite a tabela para mudar a coluna: ");
    scanf("%s",nome_tabela);

    strcpy(dir_tabela,"tabelas/");

    strcat(dir_tabela,nome_tabela);

    strcat(dir_tabela,".txt");

    FILE *tabela = fopen(dir_tabela,"r");
    if(tabela == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO %s\n",dir_tabela);
        return -1;
    }
//-------------------------------------------------------------------------------------------

fscanf(tabela,"%s",linha);//linha

fscanf(tabela,"%i",&ncoluna);//num colunas

fscanf(tabela,"%s",chaveprimaria);

printf("colunas disponiveis:\n");
printf("%s ",chaveprimaria);


for(i=0;i<ncoluna;i++){
    fscanf(tabela,"%s",nomecol);
    printf("%s ",nomecol);

    fscanf(tabela,"%s",tipo);

}
printf("\n");




fseek(tabela, 0, SEEK_SET);//ponteiro que esta escaneando a tabela vai retornar ao incio
//---------------------------------------------------------------------



    FILE *temp = fopen("temp.txt","w");
    if (tabela == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO temp.txt\n");
        return -1;
    }


    char *str = (char*) malloc(60 * sizeof(char));
    char *nome_coluna = (char*) malloc(60 * sizeof(char));
    char *novo_nome = (char*) malloc(60 * sizeof(char));

    printf("Digite a coluna que gostaria de mudar seu nome: ");
    scanf("%s",nome_coluna);
    printf("\n");

    printf("Digite o novo nome da coluna: ");
    scanf("%s",novo_nome);
    printf("\n");

    while(fscanf(tabela,"%s",str) != EOF){
        if(strcmp(str,nome_coluna) == 0){//se o nome da tabela for igual ao nome que voce botou, ele subustituirá imprimindo o nome que voce botou
            fprintf(temp,"%s\n",novo_nome);
        }
        else{
            fprintf(temp,"%s\n",str);
        }
    }


    fclose(tabela);
    fclose(temp);

//---------------------------------------------------------------------------------------

    char *escanear = (char*) malloc(60 * sizeof(char));

    char *printar = (char*) malloc(60 * sizeof(char));


    FILE *temp2 = fopen("temp.txt", "r");
    if (temp2 == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO temp.txt\n");
        return -1;
    }

    FILE *tabela2 = fopen(dir_tabela, "w");
    if (tabela == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO %s\n", dir_tabela);
        return -1;
    }

    while (fscanf(temp2,"%s", escanear) != EOF){//estou escaneando os nomes das tabelas no arquivo temporario e colocando no arquivo original
        fprintf(tabela2,"%s\n",escanear);
    }


    fclose(temp2);
    fclose(tabela2);


    free(nome_coluna);
    free(str);
    free(novo_nome);

    free(escanear);
    free(printar);

    remove("temp.txt");

    return 0;
}

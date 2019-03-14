#include <stdio.h>
#include <stdlib.h>
#include "sgbd.h"

int listarTabelas(){
    FILE *arquivo_lista = fopen("tabelas/nomes_tabelas.txt", "r");

    if (arquivo_lista == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO nome_tabelas.txt");
        return -1;
    }

    char *s = (char *)malloc(20 * sizeof(char));

    while (fscanf(arquivo_lista, "%s", s) != EOF){
        printf("%s\n", s);
    }

    free(s);
    fclose(arquivo_lista);
    return 0;
}
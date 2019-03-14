principal: main.c criar_tabela.o listar_tabelas.o criar_linha.o imprimir_tabela.o pesquisar_valor.o excluir_linha.o excluir_tabela.o mudar_coluna.o
	gcc -o sgbd main.c criar_tabela.o listar_tabelas.o criar_linha.o imprimir_tabela.o pesquisar_valor.o excluir_linha.o excluir_tabela.o mudar_coluna.o

make: criar_tabela.c listar_tabelas.c criar_linha.c imprimir_tabela.c pesquisar_valor.c excluir_linha.c excluir_tabela.c mudar_coluna.c
	gcc -c criar_tabela.c listar_tabelas.c criar_linha.c imprimir_tabela.c pesquisar_valor.c excluir_linha.c excluir_tabela.c mudar_coluna.c -o -Wall

clean:
	rm -rf *.o sgbd

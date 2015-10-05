/* ----------------------------------------------------------------------------
 * print_argc_argv.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 25/03/2015
 * Local: Brasília, BRASIL
 * E-mail: contato@jairjunior.eng.br
 * Webpage: www.jairjunior.eng.br
 * Youtube: www.youtube.com/intterror
 *
 * Criado sob licença pública.
 * A utilização, distribuição e modificação deste código é livre desde que
 * citada a fonte e seu criador.
 *
 * Descrição:
 * Este programa deve ser chamado na linha de comando junto com um texto
 * qualquer. Ex:
 * $ ./argc_argv Hello World!
 * 
 * O programa irá imprimir na tela o número de argumentos recebidos em argc e
 * as strings contidas em argv (incluindo o próprio nome do programa que é
 * sempre o primeiro argumento).
 * --------------------------------------------------------------------------*/

#include<stdio.h>	//lib para usar fprintf()


int main(int argc, char *argv[]){
  int i;

	// Imprime a quantidade de argumentos recebidos
	fprintf(stdout, "Quantidade de argumentos recebidos: %d\n", argc);

	// Imprime o nome do programa e os argumentos recebidos
	fprintf(stdout, "Nome do executavel = %s\n", argv[0]);

	for(i = 1; i < argc; i++)
		fprintf(stdout, "Argumento %d = %s\n", i, argv[i]);

	// Finaliza execução
	return 0;

}

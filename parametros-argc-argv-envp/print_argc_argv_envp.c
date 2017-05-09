/* ----------------------------------------------------------------------------
 * print_argc_argv_envp.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 25/03/2015
 * Local: Brasília, BRASIL
 * E-mail: contato@jairjunior.eng.br
 * Webpage: www.jairjunior.eng.br
 *
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
 * Este programa recebe argumentos de linha de comando em *argv[] bem como as
 * variáveis de ambiente do sistema e imprime todo esse conjunto de informações
 * na tela do terminal.
 * --------------------------------------------------------------------------*/

#include<stdio.h>	//lib para usar fprintf()


int main(int argc, char *argv[], char **envp){
  int i;

	// Imprime a quantidade de argumentos recebidos
	fprintf(stdout, "Quantidade de argumentos recebidos: %d\n", argc);

	// Imprime o nome do programa e os argumentos recebidos
	fprintf(stdout, "Nome do executavel = %s\n", argv[0]);

	for(i = 1; i < argc; i++)
		fprintf(stdout, "Argumento %d = %s\n", i, argv[i]);

	// Imprime o conteúdo das variáveis de ambiente
	i = 0;
	while( *envp != NULL){
		i++;
		fprintf(stdout, "Variavel de ambiente %d = %s\n", i, *(envp) );
		envp++;
	}

	// Finaliza execução
	return 0;

}

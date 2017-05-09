/* -----------------------------------------------------------------------------
 * execv_script1.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 05/10/2015
 * Local: Brasília, BRASIL
 * E-mail: contato@jairjunior.eng.br
 * Webpage: www.jairjunior.eng.br
 *
 *
 * Criado sob licença pública.
 * A distribuição, replicação e modificação deste código é livre desde que
 * citada a fonte e seu criador.
 *
 *
 * Descrição:
 * Este programa tem por objetivo demonstrar a funcionalidade da chamada de
 * sistema execv() em conjunto com a chamada fork().
 * Neste exemplo, o processo principal criará um novo processo através da
 * chamada fork() e substituirá sua imagem pela de um script executável (bash).
 *
 * É preciso atribuir permissão de executável ao script antes de rodar este
 * programa. Para isso, use o comando "$ chmod +x nome_do_script.sh"
 *
 * Notar que o uso da função execv() requer o caminho completo do programa a
 * ser executado e a lista de argumentos deve ser passada em forma de um vetor
 * de strings do tipo char*.
 * ---------------------------------------------------------------------------*/

#include <stdio.h>			//lib para usar fprintf() e perror()
#include <stdlib.h>			//lib para usar getenv()
#include <unistd.h>			//lib para usar fork() e exec()
#include <sys/types.h>		//lib para usar tipo pid_t
#include <sys/wait.h>		//lib para usar wait()


int main(int argc, char *argv[]){
  pid_t child_pid;
  int status;
  char *args[4];


	/* Preenche o vetor de argumentos a ser enviado */
	args[0] = "print_terminal";	//nome do script a ser executado
	args[1] = "Hello ";
	args[2] = "world!";
	args[3] = (char *) 0;		//equivalente a (char *) NULL


	/* Cria processo filho */
	child_pid = fork();

	if( child_pid == 0 ){

		/* Código do processo filho */
		/* Executa o script fazendo-o substituir a imagem do processo atual */
		execv("./print_terminal.sh", args);
		perror("execv");
		exit(EXIT_FAILURE);

	}
	else if( child_pid < 0 ){

		/* Se houver erro ao criar processo filho */
		perror("fork");
		exit(EXIT_FAILURE);

	}
	else{

		/* Código do processo pai continua aqui */
		/* Aguarda processo filho terminar e recebe status */
		wait(& status);

		/* Verifica se o processo filho terminou de forma anormal */
		if( !WIFEXITED(status) )
			fprintf(stdout, "Script não executado.\n\n");

	}

	return 0;

}

/* -----------------------------------------------------------------------------
 * execl_imagem.c
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
 * sistema execl() em conjunto com a chamada fork().
 * Neste exemplo, o processo principal criará um novo processo através da
 * chamada fork() e substituirá sua imagem pela de um executável já existente
 * no disco chamado "imagem" que deve estar no mesmo diretório.
 * ---------------------------------------------------------------------------*/

#include <stdio.h>			//lib para usar fprintf() e perror()
#include <stdlib.h>			//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include <unistd.h>			//lib para usar fork() e exec()
#include <sys/types.h>		//lib para usar tipo pid_t
#include <sys/wait.h>		//lib para usar wait()


int main(int argc, char *argv[]){
  pid_t child_pid;
  int status;


	/* Cria processo filho */
	child_pid = fork();


	if( child_pid == 0 ){

		/* Código do processo filho */
		/* Substitui imediatamente a sua imagem pela do binário "imagem" */
		/* Passa os valores 21 e 73 para que o novo programa faça uma soma */
		execl("./imagem","imagem","21","73", (char *) NULL);
		perror("execl");
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
			fprintf(stdout, "Comando não executado.\n\n");

	}

	return 0;

}

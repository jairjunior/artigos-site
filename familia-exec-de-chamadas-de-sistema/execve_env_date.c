/* -----------------------------------------------------------------------------
 * execve_env_date.c
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
 * Este programa irá invocar uam nova instância do interpretador /bin/sh com os
 * parâmetros "-c env; date". Desta forma, os programas "env" e "date" serão
 * executados em uma nova instância do shell.
 *
 * Na chamada exeve() será passada uma série de novas variáveis de ambiente 
 * para o novo programa, o qual será influenciado por este novo ambiente.
 *
 * Antes de executar este programa, execute diretamente no terminal os comandos 
 * "env" e "date", então rode este programa e compare as saídas. Observe também
 * se o Shell adiciona novas variáveis de ambiente mesmo você não tendo setado.
 * ---------------------------------------------------------------------------*/

#include <stdio.h>			//lib para usar fprintf() e perror()
#include <stdlib.h>			//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include <unistd.h>			//lib para usar fork()
#include <sys/types.h>		//lib para usar tipo pid_t
#include <sys/wait.h>		//lib para usar wait()


int main(int argc, char *argv[]){
  pid_t child_pid;
  int status;
  char *args[] = { "/bin/sh", "-c", "env; date", NULL }; 		//vetor para *argv[]
  char *env_vars[] = {	"PATH=/bin:/usr/bin",					//vetor para *envp[]
  						"USER=eu",
  						"HOME=/opt",
  						"LOGNAME=jiraya",
  						"TZ=UTC0",								//time zone
  						NULL };


	/* Cria processo filho */
	child_pid = fork();

	if( child_pid == 0 ){

		/* Código do processo filho */
		/* Invoca o programa /bin/sh com os parâmetros "-c env; date" */
		/* E passa o novo ambiente sob o qual este programa irá rodar. */
		execve(args[0], args, env_vars);
		perror("execve");
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

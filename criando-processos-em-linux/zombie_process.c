/* -----------------------------------------------------------------------------
 * zombie_process.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 25/03/2015
 * Local: Brasília, BRASIL
 * E-mail: j.junior89@hotmail.com
 * Webpage: www.jairjunior.eng.br
 *
 * Criado sob licença pública.
 * A distribuição, replicação e modificação deste código é livre desde que
 * citada a fonte e seu criador.
 *
 * Descrição:
 * Este programa cria um processo filho que termina sua execução imediatamente.
 * Enquanto isso, o processo pai entra em modo sleep por 60 segundos. Como o 
 * processo filho termina antes do processo pai, ele se torna um processo 
 * zombie.
 * 
 * Para observar a atuação destes dois processos deve-se abrir outros 
 * dois terminais a parte. Em um deve-se digitar o seguinte comando:
 * $ watch -n 1 'ps -o pid,uname,comm -C zombie_process'
 * 
 * E no outro terminal deve-se digitar o seguinte comando:
 * $ top
 * 
 * O primeiro comando irá monitorar o processo zombie_process e seus filhos e
 * atualizar a cada 1 segundo. O segundo comando irá mostrar uma lista completa
 * de todos os processos mais o número de processos zumbis existentes (canto 
 * superior direito).
 * Primeiramente, execute os dois comandos e, depois, em um terceiro terminal,
 * execute este programa. Observe que imediatamente constará 1 processo zumbi. 
 * No outro terminal irá aparecer dois comandos zombie_process, um sendo o pai
 * e o outro o filho que terá a sua frente a tag <defunct>, indicando que ele é
 * um zumbi. Após os 60 segundos se passarem, ambos os processos somem e não
 * existirá mais processo zumbi.
 * ---------------------------------------------------------------------------*/

#include<stdio.h>			//lib para usar fprintf() e perror()
#include<stdlib.h>			//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include<unistd.h>			//lib para usar fork() e getpid()
#include<sys/types.h>		//lib para usar tipo pid_t

int main(int argc, char *argv[]){
  pid_t child_pid;


	/* Cria processo filho */
	child_pid = fork();
	if( child_pid == 0 ){

		/* Processo filho. Finaliza imediatamente */
		_exit(EXIT_SUCCESS);

	}
	else if( child_pid < 0 ){

		/* Se houve erro ao criar processo filho */
		perror("fork");
		exit(EXIT_FAILURE);

	}
	else{

		/* Processo pai. Aguarda 60 segundos */
		fprintf(stdout, "Processo pai. PID: %d. \n", (int)getpid() );
		fprintf(stdout, "Processo filho criado. PID: %d. \n", (int)child_pid );
		sleep(60);

	}

	return 0;

}

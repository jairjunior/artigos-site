/* ----------------------------------------------------------------------------
 * wait_all.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 13/04/2015
 * Local: Brasília, BRASIL
 * E-mail: contato@jairjunior.eng.br
 * Webpage: www.jairjunior.eng.br
 *
 *
 * Criado sob licença pública.
 * A distribuição, replicação e modificação deste código é livre desde que
 * citada a fonte e seu criador.
 *
 * Descrição:
 * Este programa tem por objetivo demonstrar uma forma de aguardar todos os
 * processos filhos finalizarem. O processo pai cria 5 processos filhos que
 * ficarão inativos por tempos diferentes e depois encerrarão. O processo pai
 * ficará monitorando o término dos filhos até que não haja mais filhos vivos.
 * --------------------------------------------------------------------------*/

#include<stdio.h>			//lib para usar fprintf() e perror()
#include<stdlib.h>			//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include<unistd.h>			//lib para usar fork() e getpid()
#include<sys/types.h>		//lib para usar tipo pid_t
#include<errno.h>			//para ter acesso à variável externa errno

int main(int argc, char *argv[]){
  int i, status;
  char *string;
  pid_t child_pid, pid;
  

	fprintf(stdout, "Este é o processo pai. PID: %d.\n", (int)getpid() );

	/* Cria 5 processos filhos */
	for(i = 0; i < 5; i++){
		child_pid = fork();
		if(child_pid == 0){
			sleep((i+1)*5);
			_exit(EXIT_SUCCESS);
		}
		else if(child_pid < 0){
			sprintf(string, "fork %d", i);
			perror(string);
			exit(EXIT_FAILURE);
		}
		else{
			fprintf(stdout, "Processo filho %d. PID: %d\n", (i+1), (int)child_pid);
		}
	}
	
	/* Aguarda todos os processos filhos terminarem */
	/* Ficará neste laço até retornar um valor menor do que zero */
	/* Este valor (-1) simboliza que ocorreu um erro e será testado adiante*/
	while( (pid = wait(&status)) > 0){
		if( WIFEXITED(status) )
			fprintf(stdout, "Status de saida do filho %d: %d.\n", (int)pid, WEXITSTATUS(status) );
		else
			fprintf(stdout, "Processo filho %d terminou de forma anormal.\n", (int)pid );
	}

	/* Testa o que ocasionou a saída do laço while */
	/* A variável errno armazenará o código do erro da função wait() */
	if( errno == ECHILD )
		fprintf(stdout, "Todos os processos filhos terminaram.\n");
	else
		perror("wait");
	
	return 0;

}

/* -----------------------------------------------------------------------------
 * execlp_ls.c
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
 * sistema execlp() em conjunto com a chamada fork().
 * 
 * Neste exemplo, o processo principal criará um novo processo através da
 * chamada fork() e substituirá sua imagem pela do processo ls que já está
 * compilado no sistema e disponível na pasta /bin. A pasta /bin, por sua vez
 * já está adicionada à variável de ambiente PATH. Para conferir isto, digite
 * no seu terminal o seguinte comando:
 * $ echo $PATH
 * As pastas inclusas estão separadas por dois pontos (:).
 *
 * Você pode testar este código chamando outros processos como, por exemplo,
 * o processo mkdir, cat, find e outros.
 *
 * Lembrando que o uso da função execlp() exige que os argumentos para a nova
 * imagem do processo sejam listados como argumentos da função, separados por
 * vírgula e terminando sempre com (char *) NULL.
 * ---------------------------------------------------------------------------*/

#include <stdio.h>			//lib para usar fprintf() e perror()
#include <stdlib.h>			//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include <unistd.h>			//lib para usar fork()
#include <sys/types.h>		//lib para usar tipo pid_t
#include <sys/wait.h>		//lib para usar wait()


int main(int argc, char *argv[]){
  pid_t child_pid;
  int status;


	/* Cria processo filho */
	child_pid = fork();


	if( child_pid == 0 ){

		/* Código do processo filho */
		/* Substitui imediatamente a sua imagem pela do programa ls */
		execlp("ls","ls","-l","-a", (char *) NULL);
		perror("execlp");
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

		/* Verifica se o processo filho terminou corretamente */
		if( WIFEXITED(status) )
			fprintf(stdout, "\nComando executado com sucesso.\n\n" );
		else
			fprintf(stdout, "\nComando não executado.\n\n");

	}

	return 0;

}

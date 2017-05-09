/* ----------------------------------------------------------------------------
 * exemplo1_mutex.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 19/03/2016
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
 * Este programa cria cinco threads POSIX similares que executam um trabalho
 * utilizando a mesma variável global "counter". Diferentemente do exemplo1.c,
 * agora há um sincronismo entre as threads utilizando mutex. O mutex neste
 * exemplo é utilizado para proteger a variável global (compartilhada) e
 * enquanto uma thread estiver trabalhando com essa variável, o mutex irá 
 * garantir acesso exclusivo ao conteúdo dela, evitando o acesso e modificações
 * de outras threads.
 * 
 * Lembre-se que para compilar este programa pelo terminal, é necessário
 * adicionar a flag -lpthread
 * --------------------------------------------------------------------------*/

#include<stdlib.h>		//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include<stdio.h>		//lib para usar fprintf() e printf()
#include<string.h>		//lib para utilizar strerror()
#include<pthread.h>		//lib para trabalhar com threads POSIX e mutex
#include<sys/types.h>	//lib para usar tipo pthread_t e pthread_mutex_t
 
/* Protótipo de Funções */
void *threadFunction(void *p);
 
/* Variáveis Globais */
int counter;
pthread_mutex_t lock;
 
/****************************************************
 * Função principal (thread principal)
 ****************************************************/
int main(){
 pthread_t thread_id[5];
 int i, ret;
 
 	// Zera contador
 	counter = 0;

 	// Inicia mutex
 	if( pthread_mutex_init(&lock, NULL) != 0){
 		fprintf(stderr, "Erro ao criar mutex.\n");
 		exit(EXIT_FAILURE);
 	}

	// Cria cinco threads que executarão a mesma função
	for(i=0; i<5; ++i){
		ret = pthread_create(&thread_id[i], NULL, threadFunction, NULL);
		if(ret != 0){
			fprintf(stderr, "Erro thread %d. Código %d: %s\n", (i+1), ret, strerror(ret));
			exit(EXIT_FAILURE);
		}
	}
	
	// Aguarda o fim das threads
	for(i=0; i<5; ++i)
		pthread_join(thread_id[i], NULL);
		
	// Destrói o mutex
	pthread_mutex_destroy(&lock);
 
	return 0;
}
 
/****************************************************
 * Função que será executada por todas as threads
 ****************************************************/
void *threadFunction(void *p){
 unsigned long i = 0;
 
	// Trava o mutex
 	pthread_mutex_lock(&lock);
 	
 	// Incrementa contador
	counter++;
 
	printf("Trabalho %d iniciado.\n", counter);
	
	// Faz uma contagem representando um trabalho qualquer
	for(i=0; i<0xFFFFFFF; ++i);
	
	printf("Trabalho %d finalizado.\n", counter);
	
	// Libera o mutex
	pthread_mutex_unlock(&lock);
	
	pthread_exit(NULL);
}

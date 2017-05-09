/* ----------------------------------------------------------------------------
 * producer_consumer.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 20/08/2016
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
 * Este programa 
 * --------------------------------------------------------------------------*/

#include <stdio.h>			//lib para usar função printf()
#include <stdlib.h>			//lib para usar macros EXIT_SUCCESS e EXIT_FAILURE
#include <pthread.h>		//lib para trabalhar com threads e mutex
#include <unistd.h>			//lib para usar função sleep()
#include <sys/types.h>		//lib para usar tipo pid_t
 
#define BUFFER_SIZE 5
 
/* Protótipo de Funções */
void *producerThread(void *p);
void *consumerThread(void *p);
 
/* Estrutura de dados para o Buffer */
typedef struct {
    int buf[BUFFER_SIZE]; 			// buffer
    size_t length; 					// número de itens no buffer
    pthread_mutex_t mutex;		// mutex para sincronizar threads
    pthread_cond_t can_produce;	// sinal que permite produção
    pthread_cond_t can_consume;	// sinal que permite consumo
} buffer_t;
 
/***********************************************************************
 * Função principal (thread principal)
 **********************************************************************/
int main(int argc, char *argv[]) {
  pthread_t producer, consumer;
  buffer_t buffer = {
    .length = 0,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .can_produce = PTHREAD_COND_INITIALIZER,
    .can_consume = PTHREAD_COND_INITIALIZER
  };
 
    // Cria as duas threads, consumidor e produtor
    pthread_create(&producer, NULL, producerThread, (void*)&buffer);
    pthread_create(&consumer, NULL, consumerThread, (void*)&buffer);
 
    // Thread principal vai esperar eternamente
    // As threads não têm fim, ficam num loop infinito
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
 
    return 0;
}
 
/***********************************************************************
 * Thread do Produtor - Produz números aleatórios e os coloca no buffer
 **********************************************************************/
void *producerThread(void *p) {
    buffer_t *buffer = (buffer_t*)p;
 
    while(1) {
#ifdef UNDERFLOW
        // Causa um atraso no produtor fazendo com que o consumidor
        // retire mais rapidamente os dados do buffer. Mesmo assim,
        // não haverá problemas, pois o consumidor irá esperar.
        sleep(rand() % 3);
#endif
        // Trava o mutex
        pthread_mutex_lock(&buffer->mutex);
 
        // Se o buffer estiver cheio
        if(buffer->length == BUFFER_SIZE) { // full
            // Espera até que algum dado do buffer seja consumido
            // Aqui a thread fica travada na variável condicional
            // aguardando um sinal do consumidor.
            pthread_cond_wait(&buffer->can_produce, &buffer->mutex);
        }
 
        // Gera um número aleatório para colocar no buffer (0 a 100)
        int t = rand() % 1000 + 1;
        printf("Produzido: %d\n", t);
 
        // Coloca dado no buffer e incrementa a variável de controle
        buffer->buf[buffer->length] = t;
        buffer->length++;
 
        // Sinaliza que novos dados podem ser consumidos
        pthread_cond_signal(&buffer->can_consume);
        // Libera o mutex
        pthread_mutex_unlock(&buffer->mutex);
    }
    // Este ponto nunca é alcançado...
    return NULL;
}
 
/***********************************************************************
 * Thread do Consumidor - Retira itens do buffer
 **********************************************************************/
void *consumerThread(void *p) {
    buffer_t *buffer = (buffer_t*)p;
 
    while(1) {
#ifdef OVERFLOW
        // Causa um atraso no consumidor, fazendo com que o buffer
        // fique cheio. Isso mostrará que, mesmo na atual condição,
        // não ocorrerá overflow do buffer, pois o produtor irá
        // esperar
        sleep(rand() % 3);
#endif
        // Trava o mutex
        pthread_mutex_lock(&buffer->mutex);
 
        // Se o buffer estiver vazio
        if(buffer->length == 0) { // empty
            // Espera até que algum dado seja colocado no buffer
            // Aqui a thread fica travada na variável condicional
            // aguardando um sinal do produtor.
            pthread_cond_wait(&buffer->can_consume, &buffer->mutex);
        }
 
        // Pega dado do buffer e o imprime na tela
        buffer->length--;
        printf("Consumido: %d\n", buffer->buf[buffer->length]);
 
        // Sinaliza que um dado foi removido do buffer
        pthread_cond_signal(&buffer->can_produce);
        // Libera o mutex
        pthread_mutex_unlock(&buffer->mutex);
    }
    // Este ponto nunca é alcançado...
    return NULL;
}

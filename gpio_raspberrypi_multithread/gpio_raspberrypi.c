/* ----------------------------------------------------------------------------
 * gpio_raspberrypi.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 01/07/2016
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
 * Este programa controla 4 LEDs através de 4 botões (push buttons) que estão
 * ligados em pinos do GPIO do Raspberry Pi. Cada botão está associado a um
 * LED respectivo. Cada LED permanece acesso enquanto o botão está pressionado.
 * A solução utiliza threads e mutex, sendo criada uma thread para cada LED e
 * para cada botão. O mutex fica responsável por proteger o acesso à área de 
 * memória compartilhada: a variável led_state que armazena o estado de cada
 * botão/LED.
 * 
 * Lembre-se que para compilar este programa pelo terminal, é necessário
 * adicionar as flags -lpthread e -lbcm2835
 * --------------------------------------------------------------------------*/

#include <stdlib.h>		//lib para usar exit()
#include <stdio.h>		//lib para usar fprintf()
#include <string.h>		//lib para usar strerror()
#include <pthread.h>	//lib para usar threads
#include <unistd.h>		//lib para acessar a API POSIX
#include <bcm2835.h>	//lib para controle do GPIO do Raspberry Pi
#include <sys/types.h>	//lib para usar tipo pthread_t, uint8_t, etc

/* Protótipo de Funções */
void *controlLED(void *p);
void *inputRead(void *p);

/* Variáveis Globais */
pthread_mutex_t lock;		//variável de mutex para proteger led_state[]
int led_state[4];			//variável que armazena o estado de cada botão/LED

//led_pins[] designa os pinos do GPIO onde serão ligados os LEDs (saídas)
//sw_pins[] designa os pinos do GPIO onde serão ligados os botões (entradas)
uint8_t led_pins[4]={RPI_GPIO_P1_11, RPI_GPIO_P1_12, RPI_V2_GPIO_P1_13, RPI_GPIO_P1_15},
		sw_pins[4]={RPI_GPIO_P1_16, RPI_GPIO_P1_18, RPI_GPIO_P1_22, RPI_V2_GPIO_P1_29};

/***************************************************************
 * Função principal (thread principal)
 **************************************************************/
int main(int argc, char **argv){
 pthread_t threads_led[4], threads_sw[4];
 int i, ret, num[4]={1,2,3,4};

	// Inicializa mutex
	if( pthread_mutex_init(&lock, NULL) != 0 ){
		fprintf(stderr, "Erro ao inicializar mutex.\n");
		exit(EXIT_FAILURE);
	}
	// Iniciliza biblioteca bcm2835
	if( !bcm2835_init() ){
		fprintf(stderr, "Erro ao inicializar biblioteca bcm2835.\n");
		exit(EXIT_FAILURE);
	}
	
	// Seleciona pinos de saída para LEDs
	for(i=0; i<4; i++)
		bcm2835_gpio_fsel(led_pins[i], BCM2835_GPIO_FSEL_OUTP);	
	// Seleciona pinos de entrada para push buttons
	// Desabilita resistores de pull up/down nesses pinos
	for(i=0; i<4; i++){
		bcm2835_gpio_fsel(sw_pins[i], BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_fsel(sw_pins[i], BCM2835_GPIO_PUD_OFF);
	}
	
	// Laço para criar 8 threads
	for(i=0; i<4; i++){
		// Cria thread para ligar/desligar LEDs
		// Repassa um número correspondente (1, 2, 3 ou 4)
		ret = pthread_create(&threads_led[i], NULL, controlLED, &num[i]);
		if(ret != 0){
			fprintf(stderr, "Erro thread LED %d. Código %d: %s\n", (i+1), ret, strerror(ret));
			exit(EXIT_FAILURE);
		}
		// Cria thread para ler estado dos botões
		// Repassa um número correspondente (1, 2, 3 ou 4)
		ret = pthread_create(&threads_sw[i], NULL, inputRead, &num[i]);
		if(ret != 0){
			fprintf(stderr, "Erro thread SW %d. Código %d: %s\n", (i+1), ret, strerror(ret));
			exit(EXIT_FAILURE);
		}
	}
	// Aguarda as threads terminarem
	for(i=0; i<4; i++){
		pthread_join(threads_led[i], NULL);
		pthread_join(threads_sw[i], NULL);
	}
	// Finaliza biblioteca bcm2835
	bcm2835_close();
	//Destrói o mutex
	pthread_mutex_destroy(&lock);
	
	return 0;
}

/***************************************************************
 * Função responsável por controlar os LEDs
 **************************************************************/
void *controlLED(void *p){
	// Faz o cast do ponteiro para voltar a ser um inteiro
	int *num = (int *)p;
	
	//Loop infinito 
	while(1){
		// Trava o mutex antes de acessar variável led_state
		pthread_mutex_lock(&lock);
		
		// Atualiza estado do LED - liga ou desliga
		if( led_state[*num-1] )
			bcm2835_gpio_write(led_pins[*num-1], HIGH);
		else
			bcm2835_gpio_write(led_pins[*num-1], LOW);
		
		// Libera o mutex
		pthread_mutex_unlock(&lock);
		
		// Pequeno delay
		bcm2835_delay(50);
	}
	pthread_exit(NULL);
}

/***************************************************************
 * Função responsável pela leitura dos botões
 **************************************************************/
void *inputRead(void *p){
	// Faz o cast do ponteiro para voltar a ser um inteiro
	int *num = (int *)p;
	
	//Loop infinito 
	while(1){
		// Trava o mutex antes de acessar variável led_state
		pthread_mutex_lock(&lock);
		
		led_state[*num-1] = bcm2835_gpio_lev(sw_pins[*num-1]);
		
		// Libera o mutex
		pthread_mutex_unlock(&lock);
		
		// Pequeno delay
		bcm2835_delay(50);
	}
	pthread_exit(NULL);
}

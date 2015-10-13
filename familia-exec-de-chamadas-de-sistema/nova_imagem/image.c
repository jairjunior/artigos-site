/* -----------------------------------------------------------------------------
 * image.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 05/10/2015
 * Local: Brasília, BRASIL
 * E-mail: j.junior89@hotmail.com
 * Webpage: www.jairjunior.eng.br
 *
 * Criado sob licença pública.
 * A distribuição, replicação e modificação deste código é livre desde que
 * citada a fonte e seu criador.
 *
 *
 * Descrição:
 * Este programa servirá como nova imagem para o processo criado pela chamada
 * fork() no processo pai. Ela será carregada por uma das funções exec().
 *
 * Este exemplo tem como intuito mostrar que um processo pode ter sua imagem
 * totalmente substituida por uma imagem existente no disco. Isso possibilita
 * manter todo o código do novo processo em outro arquivo, ajudando assim na
 * organização do projeto.
 * ---------------------------------------------------------------------------*/

#include <stdio.h>			//lib para usar printf()
#include <stdlib.h>			//lib para usar atoi()


int main(int argc, char *argv[]){
  int a, b;


	/* Testa se a quantidade de argumentos em argc é válida. */
	if( argc != 3 ){
		fprintf(stderr, "Quantidade de argumentos inválida. ");
		fprintf(stderr, "Necessita de dois numeros.\n\n");
		return -1;
	}

	/* Converte argumentos para inteiro e mostra resultado */
	a = atoi( argv[1] );
	b = atoi( argv[2] );
	printf("A soma é igual a %d.\n\n", (a+b));

	return 0;

}
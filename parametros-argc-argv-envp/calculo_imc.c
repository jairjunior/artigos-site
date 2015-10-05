/* ----------------------------------------------------------------------------
 * calculo_imc.c
 *
 * Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
 * Data: 25/03/2015
 * Local: Brasília, BRASIL
 * E-mail: contato@jairjunior.eng.br
 * Webpage: www.jairjunior.eng.br
 * Youtube: www.youtube.com/intterror
 *
 * Criado sob licença pública.
 * A utilização, distribuição e modificação deste código é livre desde que
 * citada a fonte e seu criador.
 *
 * Descrição:
 * Este programa deve ser chamado na linha de comando do terminal repassando
 * o caminho para um arquivo de saída, sua idade, seu peso e sua altura:
 * $ ./calculo_imc /home/user/documentos/saida.txt 25 82.4 1.8
 * Deve ser utilizado ponto para separar as casas decimais.
 * O programa irá calcular o IMC do individuo e dizer se ele está abaixo, acima
 * ou no peso correto, imprimindo o resultado no arquivo de saída.
 * --------------------------------------------------------------------------*/

#include<stdio.h>	//lib para usar fprintf() e perror()
#include<stdlib.h>	//lib para usar atoi() e atof()


int main(int argc, char *argv[]){
  int idade;
  float peso, altura, imc;
  FILE *arq_saida;

	// Testa se a quantidade de argumentos em argc é válida.
	if( argc != 5 ){
		fprintf(stderr, "Quantidade de argumentos invalida. ");
		fprintf(stderr, "Necessita /path/saida.txt, idade, peso e altura.\n");
		return -1;
	}
	
	// Abre arquivo para escrita e testa se obteve êxito
	arq_saida = fopen( argv[1], "w" );
	if( arq_saida == NULL ){
		fprintf(stderr, "Erro ao abrir arquivo de saida.\n");
		perror("fopen");
		return -1;
	}
	else{
		fprintf(stdout, "Arquivo de saida criado com sucesso.\n");
	
		// Faz a conversão das strings para inteiro e float
		idade = atoi( argv[2] );
		peso = (float)atof( argv[3] );
		altura = (float)atof( argv[4] );
			
		// Calcula o IMC
		imc = peso/(altura*altura);
		
		// Testa o valor do IMC calculado e imprime resultado na tela
		if( imc < 18.5 ){
			fprintf(arq_saida, "Sua idade: %d \t Seu IMC: %.2f\n", idade, imc);
			fprintf(arq_saida, "Voce esta abaixo do peso. Coma mais!\n");
		}
		else if( (imc >= 18.5) && (imc < 25) ){
			fprintf(arq_saida, "Sua idade: %d \t Seu IMC: %.2f\n", idade, imc);
			fprintf(arq_saida, "Seu peso esta normal. Parabens!\n");
		}
		else{
			fprintf(arq_saida, "Sua idade: %d \t Seu IMC: %.2f\n", idade, imc);
			fprintf(arq_saida, "Voce esta acima do peso. Tranque a boca!\n");
		}

		// Fecha o arquivo
		fclose( arq_saida );
		
	}
	
	// Finaliza execução
	return 0;

}

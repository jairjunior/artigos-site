#!/bin/bash

# -----------------------------------------------------------------------------
# print_file.sh
#
# Criador: Jair Dias de Oliveira Junior, Engenheiro Eletrônico
# Data: 05/10/2015
# Local: Brasília, BRASIL
# E-mail: j.junior89@hotmail.com
# Webpage: www.jairjunior.eng.br
#
# Criado sob licença pública.
# A distribuição, replicação e modificação deste código é livre desde que
# citada a fonte e seu criador.
#
#
# Descrição:
# Este é um Shell Script básico que recebe em seus parâmetros o nome de uma
# pasta e de um arquivo de texto (.txt). Caso a pasta ainda não exista, o 
# script irá criá-la primeiro junto com um arquivo de texto. Caso a pasta já
# exista e o arquivo não, somente o arquivo será criado.
#
# A pasta sempre será criada no diretório $HOME e o arquivo dentro dela.
#
# Em seguida, o script entra na pasta e escreve uma nova linha no arquivo. Note 
# que se a pasta e o arquivo existem, somente a nova linha será adicionada.
# -----------------------------------------------------------------------------


# Carrega variáveis com nome do diretório e do arquivo
dir=$HOME/pasta
arq=$dir/$2

# Testa se o diretório já existe
# Se não existir, cria o diretório e um arquivo em branco
if [ ! -d $dir  ]; then
	mkdir $dir
	echo "Nova pasta criada -> $dir"
	touch $arq
	echo "Novo arquivo criado -> $arq"

# Caso a pasta já exista, testa se o arquivo já existe
# Se não existir, cria um novo arquivo .txt em branco
elif [ ! -f $arq ]; then
	touch $arq
	echo "Novo arquivo criado -> $arq"
fi

# Insere uma nova linha de texto no arquivo e finaliza
echo "Esta é uma nova linha de texto" >> $arq
echo "Nova linha inserida no arquivo $arq"
echo ""
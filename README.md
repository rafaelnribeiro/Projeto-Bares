# Projeto-Bares
*Avaliador de Expressões Aritméticas Simples*

###Descrição

Realiza a análize de expressões aritméticas envolvendo números (entre -32.767 e 32.767),
operadores binários **('+', '-', '*', '/', '%', '^')** e parênteses.

Obs.: Este programa não trata o operador '-' unário.


###Desenvolvedores

* Igor Barbosa Nogueira – igornogueir@gmail.com

* Rafael do Nascimento Ribeiro – rafaelnribeiro@outlook.com


###Compilação e Execução
Para compilar execute o comando:
g++ -Wall -std=c++11 -I include/ bares.cpp -o bin/bares

Para executar o programa use:
./bares 'endereço do arquivo de entrada'

###Dificuldades

* Para implementar os sistesmas para identificação de cada erro, tivemos que modificar bastante o código, o qual não ficou com uma aparência muito boa.

* Não conseguimos encontrar um solução para os casos com o operador '-' (menos) unário.

###Agradecimentos

* Ao professor Selan Rodrigues dos Santos por nos passar o projeto do trabalho.

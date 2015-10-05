#include <StackLL.h>
#include <QueueLL.h>

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

std::string digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::string valOperators = {'(', ')', '^', '*', '/', '%', '-', '+'};

std::string invOperators = {'=', '>', '<', '.'};

enum SimbolType {OPERATOR, OPERAND};

struct token
{
	std::string info;
	SimbolType type;
	bool isValid;
	int position;
};

//Calcula uma expressão posfixa
int calcPosfix(QueueLL<token> exps)
{
	StackLL<int> stack; //Pilha de inteiros
	token simb; //Token atual
	int op1, op2, result;

	while(!exps.empty())
	{
		simb = exps.remove(); //Remove um token da fila

		//Se for um operando
		if(simb.type == OPERAND)
		{
			int n = stoi(simb.info);
			//Adiciona o valor à pilha
			stack.push(n);
		}
		//Se for um operador
		else
		{
			//Retira os dois ultimos valores da pilha
			op2 = stack.pop();
			op1 = stack.pop();

			char c = simb.info[0];

			//Realiza a operação baseada no operador
			switch(c)
			{
				case '+':
					result = op1 + op2;
					break;

				case '-':
					result = op1 - op2;
					break;
					
				case '*':
					result = op1 * op2;
					break;
					
				case '/':
					if(op2 == 0)
					{
						std::cout << "Erro coluna " << simb.position << ": Divisão por zero!" << std::endl;
						return 0;
					}
					result = op1 / op2;
					break;
					
				case '%':
					result = op1 % op2;
					break;
					
				case '^':
					result = op1 ^ op2;
					break;
			}
			//Adiciona o resulatado à pilha
			stack.push(result);
		}
	}
	result = stack.pop();
	return result;
}

//Cria uma fila de tokens
void stringToInfix(std::string str, QueueLL<token> & exps)
{
	unsigned int i = 0;
	//Lê a string
	while(i < str.size())
	{
		//Se for um dígito
		if(digits.find(str[i]) != std::string::npos)
		{
			std::string num;
			int ini = i;// Posição do primeiro dígito

			//Concatena todos os digitos que estão juntos
			while(digits.find(str[i]) != std::string::npos)
			{
				num.push_back(str[i]);
				++i;
			}

			//Adiciona o número a um token
			token tmp;
			tmp.info = num;
			tmp.type = OPERAND;
			tmp.isValid = true;
			tmp.position = ini;

			//Adiciona o token à fila
			exps.insert(tmp);
		}

		//Se não for um caractere nulo e não chegou o final da string
		if(!isspace(str[i]) && str[i] != '\0')
		{
			std::string s(1,str[i]);

			token tmp;
			tmp.info = s;
			tmp.position = i;

			//Se for um operador válido
			if(valOperators.find(str[i]) != std::string::npos)
			{
				tmp.type = OPERATOR;
				tmp.isValid = true;
			}
			//Se for um operador inválido
			else if(invOperators.find(str[i]) != std::string::npos)
			{
				tmp.type = OPERATOR;
				tmp.isValid = false;
			}
			//Caso contrário, é um operando inválido
			else
			{
				tmp.type = OPERAND;
				tmp.isValid = false;
			}
			//Adiciona o token à fila
			exps.insert(tmp);
		}
		++i;
	}
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		std::cout << "Erro de sintaxe!" << std::endl;
		std::cout << "Use: bares <arquivo_de_leitura>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string myFile = argv[1];
	std::cout << "Tentando abrir o arquivo [ " << myFile << " ]" << std::endl;
	std::ifstream myStream(myFile);

	if(!myStream)
	{
		std::cout << "Falha na abertura do arquivo";
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "Arquivo aberto com sucesso" << std::endl;
	}

	std::string expression;

	while(!myStream.eof())
	{
		QueueLL<token> exps;

		getline(myStream, expression);
	
		stringToInfix(expression, exps);

		while(!exps.empty())
		{
			token tmp = exps.remove();
			std::cout << "{ " << tmp.info << ", " << tmp.type << ", " << tmp.position << ", " << tmp.isValid << "} ";
		}
		std::cout << std::endl;
	}

	return 0;
}

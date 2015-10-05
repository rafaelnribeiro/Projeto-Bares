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


void stringToInfix(std::string str, QueueLL<token> & exps)
{
	unsigned int i = 0;
	while(i < str.size())
	{
		if(digits.find(str[i]) != std::string::npos)
		{
			std::string num;
			int ini = i;

			while(digits.find(str[i]) != std::string::npos)
			{
				num.push_back(str[i]);
				++i;
			}

			token tmp;
			tmp.info = num;
			tmp.type = OPERAND;
			tmp.isValid = true;
			tmp.position = ini;
			exps.insert(tmp);
		}

		if(!isspace(str[i]) && str[i] != '\0')
		{
			std::string s(1,str[i]);

			token tmp;
			tmp.info = s;
			tmp.position = i;

			if(valOperators.find(str[i]) != std::string::npos)
			{
				tmp.type = OPERATOR;
				tmp.isValid = true;
			}
			else if(invOperators.find(str[i]) != std::string::npos)
			{
				tmp.type = OPERATOR;
				tmp.isValid = false;
			}
			else
			{
				tmp.type = OPERAND;
				tmp.isValid = false;
			}
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

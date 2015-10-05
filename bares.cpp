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



bool token(std::string str, QueueLL<std::string> & exps)
{
	bool sucess = true;
	std::string num;
	unsigned int i = 0;
	while(i < str.size())
	{
		if (digits.find(str[i]) != std::string::npos)
		{
			int ini = i;
			while(digits.find(str[i]) != std::string::npos)
			{
				num.push_back(str[i]);
				++i;
			}
			int tmp = stoi(num);
			if(tmp > 32.767)
			{
				std::cout << "Erro na coluna " << ini << ": O operando'"
					  	  << tmp << "' está fora da faixa permitida!" << std::endl;
				sucess = false;
			}
			else
				exps.insert(num);

			num.resize(0);
		}

		if(valOperators.find(str[i]) != std::string::npos)
		{
			std::string s(1,str[i]);
			exps.insert(s);
		}
		else if(invOperators.find(str[i]) != std::string::npos)
		{
			std::cout << "Erro na coluna " << i << ": O operador '"
					  << str[i] << "' não pertence à lista de operadores válidos!" << std::endl;
			sucess = false;
		}
		else if(!isspace(str[i]) && str[i] != '\0')
		{
			std::cout << "Erro na coluna " << i << ": O operando '"
					  << str[i] << "' não é uma constante válida!" << std::endl;
			sucess = false;
		}
		++i;
	}
	return sucess;
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
		QueueLL<std::string> exps;

		getline(myStream, expression);

		//Se não houveram erros na tokenização		
		if(token(expression, exps))
		{
			//Realizar a conversão da fila exps de Infixo para Posfixo
			std::cout << "Sucesso!" << std::endl;
		}
		std::cout << std::endl << std::endl;

	}

	return 0;
}

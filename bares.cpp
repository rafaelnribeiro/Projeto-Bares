#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

std::string digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::string valOperators = {'(', ')', '^', '*', '/', '%', '-', '+'};

std::string invOperators = {'=', '>', '<', '.'};



std::vector<std::string> token(std::string str)
{
	std::string num;
	std::vector<std::string> exps;
	int col = 0;
	unsigned int i = 0;
	while(i < str.size())
	{
		if (digits.find(str[i]) != std::string::npos)
		{
			while(digits.find(str[i]) != std::string::npos)
			{
				num.push_back(str[i]);
				++i;
			}
			exps.push_back(num);
			num.resize(0);
		}

		if(valOperators.find(str[i]) != std::string::npos)
		{
			std::string s(1,str[i]);
			exps.push_back(s);
		}
		else if(invOperators.find(str[i]) != std::string::npos)
		{
			std::cout << "Erro na coluna " << col << ": O operador '"
					  << str[i] << "'não pertence à lista de operadores válidos!" << std::endl;
		}
		else if(!isspace(str[i]) && str[i] != '\0')
		{
			std::cout << "Erro na coluna " << col << ": O operando '"
					  << str[i] << "' não é uma constante válida!" << std::endl;
		}

		++col;
		++i;
	}
	return exps;
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
		getline(myStream, expression);
		std::vector<std::string> exps = token(expression);
		for (std::string e: exps)
		{
			std::cout << "{" << e << "} ";
		}
		std::cout << std::endl << std::endl;
	}

	return 0;
}

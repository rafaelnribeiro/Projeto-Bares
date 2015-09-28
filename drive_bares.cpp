#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

std::string digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::string symbols = {'(', ')', '^', '*', '/', '%', '-', '+'};



std::vector<std::string> token(std::string str)
{
	std::string num;
	std::vector<std::string> exps;
	for(char c: str)
	{
		if (digits.find(c) != std::string::npos)
		{
			num.push_back(c);
		}
		else if(symbols.find(c) != std::string::npos)
		{
			if(num.size() > 0)
			{
				exps.push_back(num);
				num.resize(0);
			}
			std::string s(1,c);
			exps.push_back(s);
		}
		else if(!isspace(c))
		{
			std::cout << std::endl << "Símbolo "<< c <<" é inválido!" << std::endl;
		}
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
		std::cout << std::endl;
	}

	return 0;
}
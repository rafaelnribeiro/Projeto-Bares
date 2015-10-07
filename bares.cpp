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


//Calcula a ordem de precedência dos operadores	
int comparePref (std::string opr) {
	char c = opr[0];
	switch(c)
	{
		case '+':
			return 5;
			break;

		case '-':
			return 5;
			break;

		case '*':
			return 4;
			break;

		case '/':
			return 4;
			break;

		case '%':
			return 4;
			break;

		case '^':
			return 3;
			break;
	}

	return 0;
}

//Cria uma fila de tokens
bool stringToInfix(std::string str, QueueLL<token> & exps)
{
	//Checa se a string enviada é vazia
	if (str.size() == 0)
		return false;

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
	return true;
}

//Transforma uma expressão infixa em posfixa
bool infixToPosfix (QueueLL<token> & exps, QueueLL<token> & posFix) {

	bool sucess = true;

	StackLL<token> stk;

	SimbolType expected = OPERAND;//Tipo de token esperado no momento
	int pos = 0;
	bool first = true;

	StackLL<int> stkPrt;//Pilha para tratar o erro de escopo aberto

	while(!exps.empty())
	{
		token tmp = exps.remove();

		//Se já apareceu pelo menos um número
		if(tmp.type == OPERAND)
			first = false;

		//Tratamento para o erro de falta de operando/operador
		if(tmp.type != expected && tmp.info[0] != ')' && tmp.info[0] != '(')
		{
			if(expected == OPERATOR)
			{
				std::cout << "Erro coluna " << pos << ": Falta operador"<< std::endl;
			}
			else
			{
				//Se ,na lista, o primeiro operador aparecer antes do primeiro operando
				if(first)
					pos = tmp.position;

				std::cout << "Erro coluna " << pos << ": Falta operando"<< std::endl;
			}
			sucess = false;
		}

		//Tratamento para erro de operador/operando inválido
		if (!tmp.isValid)
		{
			if (tmp.type == OPERAND)
				std::cout << "Erro coluna " << tmp.position << ": Operando '" << tmp.info << "' é inválido!" << std::endl;
			else
				std::cout << "Erro coluna " << tmp.position << ": Operador '" << tmp.info << "' é inválido!" << std::endl;

			sucess = false;
		}



		if (tmp.type == OPERAND)
		{
			//Tratamento para erro de constante numérica inválida
			if(tmp.isValid && stoi(tmp.info) > 32767)
			{
				std::cout << "Erro coluna " << tmp.position << ": Operando '" << tmp.info << "' está fora da faixa permitida!" << std::endl;

			}

			//Operandos vão direto para a fila
			posFix.insert(tmp);
			expected = OPERATOR;
		}
		else if (tmp.info[0] == '(')
		{
			//Empilha o '('
			stk.push(tmp);

			//Adiciona a posição do parenteses à pilha de inteiros
			stkPrt.push(tmp.position);

		}
		else if (tmp.info[0] == ')')
		{
			//Tratamento de erro para fechamento de escopo inválido
			if(stkPrt.empty())
			{
				std::cout << "Erro coluna " << tmp.position << ": Fechamento de escopo inválido" << std::endl;
				sucess = false;
			}
			else
			{
				stkPrt.pop();

				//Desempilha todos os tokens até encontrar um '('
				while (!stk.empty() && stk.top().info[0] != '(')
				{
					posFix.insert(stk.pop());
				}

				//Desempilha o '('
				if(!stk.empty())
				stk.pop();
			}
		}
		else
		{
			//Desempilha todos os operandos de precedência maior ou igual ao atual os adiciona a fila
			while (!stk.empty() && stk.top().info[0] != '(' && comparePref(stk.top().info) <= comparePref(tmp.info))
			{
				posFix.insert(stk.pop());
			}
			//Empilha o operador atual
			stk.push(tmp);

			expected = OPERAND;
		}
		pos = tmp.position;
	}

	//Desempilha os operadores restantes e os adiciona a fila
	while (!stk.empty())
	{
		posFix.insert(stk.pop());
	}

	//Tratamento para erro de escopo aberto
	while(!stkPrt.empty())
	{
		std::cout << "Erro coluna " << stkPrt.pop() << ": Escopo aberto" << std::endl;
		sucess = false;
	}

	//Caso a fila termine esperando um operando
	if(expected == OPERAND)
	{
		std::cout << "Erro coluna " << pos << ": Falta operando"<< std::endl;
		sucess = false;
	}

	return sucess;

}

//Calcula uma expressão posfixa
bool calcPosfix(QueueLL<token> & exps, int & result)
{
	if (exps.empty())
		return false;

	StackLL<int> stack; //Pilha de inteiros
	token simb; //Token atual
	int op1, op2;


	while(!exps.empty())
	{
		simb = exps.remove(); //Remove um token da fila
		//std::cout << simb.info << std::endl;
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
					//Tratamento de erro de divisão por zero
					if(op2 == 0)
					{
						std::cout << "Erro coluna " << simb.position << ": Divisão por zero!" << std::endl;
						return false;
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
	if (!stack.empty())
		result = stack.pop();

	return true;
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
		QueueLL<token> posFix;
		int result;

		getline(myStream, expression);

		if (stringToInfix(expression, exps))
		{
			if (infixToPosfix(exps, posFix))
			{
				if (calcPosfix(posFix, result))
				{
					std::cout << result << std::endl;
				}
			}
		}
		std::cout << std::endl;
	}

	return 0;
}

#ifndef _STACKLL_H
#define _STACKLL_H

#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename Data>
//! Pilha com lista encadeada.
class StackLL
{
	private:
		//! Nó da pilha.
		struct node
		{
			Data miData; //!< Informação do nó.
			node * mpNext; //!< Ponteiro para o próximo nó.
		};

		node * mpHead; //!< Ponteiro para o início da pilha.

		StackLL(const StackLL &){}

	public:
		//! Construtor da classe.
		/*! Inicializa o ponteiro para o início da pilha.
		*/
		StackLL();

		//! Destrutor da classe.
		~StackLL();

		//! Insere um nó ao início da pilha.
		/*! @param _data Informação a ser adicionada ao novo nó.
		*/
		void push(const Data & _data);

		//! Remove o primeiro nó da pilha e retorna a iformação contida nele.
		/*! @return Informação do nó removido
		*/
		const Data pop();

		//! Retorna a informação do primeiro nó da pilha.
		/*! @return Informação do primeiro nó da pilha.
		*/
		const Data & top() const;

		//! Testa se a pilha está vazia.
		/*! @return true se a lista está vazia ou false, caso contrário.
		*/
		bool empty();

		//! Esvazia a pilha
		void clear();

		//Método para depuração
		inline friend
		std::ostream &operator << (std::ostream& _os, const StackLL& _oList)
		{
			node * current = _oList.mpHead;
			_os << "Pilha: [ ";
			while(current != nullptr)
			{
				_os << "(" << current->miData << ") ";
				current = current->mpNext;
			}
			_os << "]" << std::endl;
			return _os;
		}
};	

#include <StackLL.inl>
#endif
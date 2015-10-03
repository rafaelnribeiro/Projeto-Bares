//Pilha com lista encadeada

#ifndef _STACKLL_H
#define _STACKLL_H

#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename Data>
class StackLL
{
	private:
		struct node{
			Data miData;
			node * mpNext;
		};

		node * mpHead;

		StackLL(const StackLL &){}

	public:
		StackLL();
		~StackLL();

		void push(const Data & _data);
		const Data pop();
		const Data & top() const;

		bool empty();
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
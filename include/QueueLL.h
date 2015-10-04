//Fila com lista encadeada

#ifndef _QUEUELL_H_
#define _QUEUELL_H_

#include <iostream>
#include <ostream>

template <typename Data>

class QueueLL {
    private:
        struct node {
            Data miData;
            node * mpNext;
        };

        node * mpHead;

        node * mpEnd;

        QueueLL(const QueueLL &){}

    public:
        QueueLL();
        ~QueueLL();

        void insert (const Data _data);
        Data remove ();

        const Data & begin();
        const Data & end();

        bool empty();
        void clear();

        inline friend std::ostream &operator << (std::ostream& _os, const QueueLL& _oList) {
			node * current = _oList.mpEnd;
			_os << "Fila: [ ";
			while(current != nullptr) {
				_os << "(" << current->miData << ") ";
				current = current->mpNext;
			}
			_os << "]" << std::endl;
			return _os;
		}

};




















#endif

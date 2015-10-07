#ifndef _QUEUELL_H_
#define _QUEUELL_H_

#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename Data>

//! Fila com lista encadeada.
class QueueLL {
    private:
        //! Nó da fila.
        struct node {
            Data miData; //!< Informação do nó.
            node * mpNext; //!< Ponteiro para o próximo nó.
        };

        node * mpHead; //!< Ponteiro para o início da fila.

        node * mpEnd; //!< Ponteiro para o final da fila.

        QueueLL(const QueueLL &){}

    public:
        //! Construtor da classe.
		/*! Inicializa o ponteiro para o início e para o final da fila.
		*/
        QueueLL();

        //! Destrutor da classe.
        ~QueueLL();

        //! Insere um nó ao final da fila.
        /*! @param _data Informação a ser adicionada ao novo nó.
        */
        void insert (const Data & _data);


        //! Remove o primeiro nó da fila e retorna a informação contida nele.
        /*! @return Informação do nó removido
        */
        Data remove ();

        //! Retorna a informação do primeiro nó da fila.
		/*! @return Informação do primeiro nó da fila.
		*/
        const Data & begin() const;

        //! Retorna a informação do último nó da fila.
		/*! @return Informação do último nó da fila.
		*/
        const Data & end() const;

        //! Testa se a fila está vazia.
		/*! @return true se a lista está vazia ou false, caso contrário.
		*/
        bool empty();

        //! Esvazia a fila.
        void clear();

        //! Método para depuração
        inline friend std::ostream &operator << (std::ostream& _os, const QueueLL& _oList) {
			node * current = _oList.mpHead;
			_os << "Fila: [ ";
			while(current != nullptr) {
				_os << "(" << current->miData << ") ";
				current = current->mpNext;
			}
			_os << "]" << std::endl;
			return _os;
		}

};
#include <QueueLL.inl>
#endif

template <typename Data>
QueueLL<Data>::QueueLL() {

    this->mpHead = nullptr;
    this->mpEnd = nullptr;

}

template <typename Data>
QueueLL<Data>::~QueueLL() {
    this->clear();
}

template <typename Data>
void QueueLL<Data>::insert(const Data & _data) {

    node * newNode = new node();
    newNode->miData = _data;
    newNode->mpNext = this->mpEnd;
    if (this->mpHead == nullptr && this->mpEnd == nullptr) {
        this->mpEnd = newNode;
        this->mpHead = newNode;
    } else {
        this->mpEnd = newNode;
    }
}

template <typename Data>
Data QueueLL<Data>::remove() {

    Data data = this->begin();

    node * tmp = this->mpHead;
	this->mpHead = this->mpHead->mpNext;

	delete tmp;

    return data;

}

template <typename Data>
const Data & QueueLL<Data>::begin() const {

    if(this->mpHead == nullptr)
        throw std::underflow_error("const Data & QueueLL<Data>::begin const(): Underflow!");

    return this->mpHead->miData;
}

template <typename Data>
const Data & QueueLL<Data>::end() const {

    if(this->mpEnd == nullptr)
        throw std::underflow_error("const Data & QueueLL<Data>::end const(): Underflow!");

    return this->mpEnd->miData;
}

template <typename Data>
bool QueueLL<Data>::empty(){

    if (this->mpEnd == nullptr && this->mpHead == nullptr )
        return true;

    return false;

}

template <typename Data>
void QueueLL<Data>::clear () {

    while (this->mpEnd != nullptr) {
        this->remove();
    }


}

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
    if (this->mpHead == nullptr && this->mpEnd == nullptr) {
        this->mpEnd = newNode;
        this->mpHead = newNode;
        newNode->mpNext = nullptr;
    } else {
        this->mpEnd->mpNext = newNode;
        this->mpEnd = newNode;
        newNode->mpNext = nullptr;
    }
}

template <typename Data>
Data QueueLL<Data>::remove() {

    Data data = this->begin();

    if(this->mpEnd == this->mpHead){
        this->mpEnd = nullptr;
    }

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
    node * tmp;
    while (this->mpHead != nullptr) {
        tmp = this->mpHead;
    	this->mpHead = this->mpHead->mpNext;
    	delete tmp;
    }

    this->mpEnd = nullptr;
}

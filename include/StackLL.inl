template <typename Data>
StackLL<Data>::StackLL()
{
	this->mpHead = nullptr;
}

template <typename Data>
StackLL<Data>::~StackLL()
{
	this->clear();
}

template <typename Data>
void StackLL<Data>::push(const Data & _data)
{
	node * newNode = new node();
	newNode->miData = _data;
	newNode->mpNext = this->mpHead;
	this->mpHead = newNode;
}

template <typename Data>
const Data StackLL<Data>::pop()
{
	Data data = this->top();

	node * tmp = this->mpHead;
	this->mpHead = this->mpHead->mpNext;

	delete tmp;

	return data;
}

template <typename Data>
const Data & StackLL<Data>::top() const
{
	if(this->mpHead == nullptr)
		throw std::underflow_error("const Data & StackLL<Data>::top const(): Underflow!");
	return this->mpHead->miData;
}

template <typename Data>
bool StackLL<Data>::empty()
{
	if(this->mpHead == nullptr)
		return true;
	else
		return false;
}


template <typename Data>
void StackLL<Data>::clear()
{
	node * tmp;
	while(this->mpHead != nullptr)
	{
		tmp = mpHead;
		this->mpHead = this->mpHead->mpNext;
		delete tmp;
	}
}
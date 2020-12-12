#include <conio.h>
#include <iostream>
#include <cassert> 

class Node
{
public:

	int value;
	Node* Next;

	Node()
	{
		int value = 0;
		Node* Next = NULL;
	}

	Node(int value, Node* Next)
	{
		this->value = value;
		this->Next = Next;
	}
};

class List
{
	Node* Head;
public:
	List() { Head = NULL; }
	~List();
	void add(int);
	int Pop();
	int len();
	void operator=(List*);
	List operator+(List*);
	void operator+=(List*);
	int erase(int);
	int getValueItemN(int);
	void insertValueInPosN(int, int);
	void push_front(int);
	void push_back(int);
private:
	Node getHead();
	void clear();
	void copy(List*);
};

List::~List()
{
	clear();
}

void List::add(int value)
{
	Head = new Node(value, Head);
}

int List::Pop()
{
	assert(Head);
	int value = Head->value;
	Head = Head->Next;
	return value;
}

int List::len()
{
	assert(Head);
	Node* temp = Head;
	int count = 0;

	while (temp)
	{
		count++;
		temp = temp->Next;
	}

	return count;
}

Node List::getHead()
{
	assert(Head);
	return *Head;
}

void List::operator=(List* list)
{
	copy(list);
}

void List::copy(List* list)
{
	clear();
	assert(list);

	Node* temp = list->Head;

	while (temp)
	{
		Head = new Node{ temp->value, Head };
		temp = temp->Next;
	};
};

void List::clear()
{
	while (Head)
	{
		Node* temp = Head->Next;
		delete Head;
		Head = temp;
	}
}

List List::operator+(List* list)
{
	assert(list);
	Node* temp = Head;
	temp = list->Head;
	assert(temp);

	while (temp)
	{
		Head = new Node{ temp->value, Head };
		temp = temp->Next;
		assert(temp);
	}

	return List();
}


void List::operator+=(List* list)
{
	assert(list);
	Node* temp = Head;
	temp = list->Head;
	assert(temp);

	while (temp)
	{
		Head = new Node{ temp->value, Head };
		temp = temp->Next;
		assert(temp);
	}
}
int List::erase(int N)
{
	assert(N >= 0);
	Node* temp = Head;
	for (int i = 0; i < N - 1; ++i)
	{
		assert(temp);
		temp = temp->Next;
	}
	assert(temp);
	assert(temp->Next);
	Node* buff = temp->Next->Next;
	int value = temp->Next->value;
	delete temp->Next;
	temp->Next = buff;
	return value;
}

int List::getValueItemN(int N)
{
	assert(N >= 0);
	Node* temp = Head;

	for (int i = 0; i < N; ++i)
	{
		assert(temp);
		temp = temp->Next;
	}

	int value = temp->value;
	return value;
}

void List::insertValueInPosN(int N, int value)
{
	assert(N >= 0);
	Node * temp = Head;
	for (int i = 0; i < N - 2; ++i)
	{
		assert(temp);
		temp = temp->Next;
	}
	assert(temp);
	temp->Next = new Node{ value, temp->Next };
}

void List::push_back(int value)
{
	Node* temp = Head;
	assert(temp->Next);

	while (temp->Next)
	{
		assert(temp->Next->Next);
		temp = temp->Next;
	}

	temp->Next = new Node(value, new Node);
}

void List::push_front(int value)
{
	Head = new Node(value, Head);
}






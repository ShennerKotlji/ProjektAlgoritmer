#pragma once

template <typename T>
class List
{
public:
	class Node 
	{
	public:
		T element;
		Node* next;
		Node(T element);
		~Node();
	};

	List();
	virtual ~List();
	List(const List &other);
	List& operator=(const List &other);
	void insertAt(int pos, const T &element);
	int length() const;
	T getAt(int pos);
	void removeAt(int pos);
	bool removeElement(const T &element);
	bool findElement(const T &toFind) const;
	void getAll(T arr[], int cap);

	
private:
	Node* first;
	int nrOfNodes;

};

template<typename T>
inline List<T>::List()
{
	this->first = nullptr;
	this->nrOfNodes = 0;
}

template<typename T>
inline List<T>::~List()
{
	if (first != nullptr)
	{
		Node* walker = first;
		Node* temp = nullptr;

		while (walker != nullptr)
		{
			temp = walker->next;
			delete walker;
			walker = temp;
		}
	}
	
}

template<typename T>
inline List<T>::List(const List &other)
{
	this->first = nullptr;
	this->nrOfNodes = 0;
	Node* walker = other.first;
	int pos = 0;
	
	while (walker != nullptr)
	{
		insertAt(pos,walker->element);
		walker = walker->next;
		pos++;
	}
}

template<typename T>
List<T>& List<T>::operator=(const List & other)
{
	
	if (this != &other)
	{
		Node* walker = first;
		Node* temp = nullptr;

		while (walker != nullptr)
		{
			temp = walker->next;
			delete walker;
			walker = temp;
		}
		this->first = nullptr;
		this->nrOfNodes = 0;
		walker = other.first;
		int pos = 0;

		while (walker != nullptr)
		{
			insertAt(pos, walker->element);
			walker = walker->next;
			pos++;
		}
	}

	return *this;
}

template<typename T>
inline void List<T>::insertAt(int pos, const T & element)
{
	if (pos < 0 || pos > nrOfNodes) 
	{
		throw "Could not insert element";
	}

	else if (pos == 0) 
	{
		Node* temp = new Node(element);
		temp->next = first;
		first = temp;
	}
	else 
	{
		Node* walker = first;
		for (int i = 0; i<pos-1; i++) 
		{
			walker = walker->next;
		}
		Node* temp = new Node(element);
		temp->next = walker->next;
		walker->next = temp;
		
	}

	nrOfNodes++;
}

template<typename T>
inline int List<T>::length() const
{
	return nrOfNodes;
}

template<typename T>
inline T List<T>::getAt(int pos)
{
	if (pos < 0 || pos > nrOfNodes)
	{
		throw "Could not find element";
	}

	else
	{
		Node* walker = first;

		for (int i = 0; i<pos; i++)
		{
			walker = walker->next;
		}

		return walker->element;
	}
	
}

template<typename T>
inline void List<T>::removeAt(int pos) 
{
	if (pos < 0 || pos > nrOfNodes)
	{
		throw "Could not find element";
	}
	Node* walker = first;
	Node* temp = nullptr;
	
	if (pos > 0) 
	{
		for (int i = 0; i < pos - 1; i++)
		{
			walker = walker->next;
		}

		temp = walker->next;
		walker->next = temp->next;
		delete temp;
		nrOfNodes--;
	}

	else if (pos == 0) 
	{
		temp = first->next;
		delete first;
		first = temp;
		nrOfNodes--;
	}
}

template<typename T>
inline bool List<T>::removeElement(const T & element)
{
	bool wasRemoved = false;
	Node* walker = first;
	Node* temp = nullptr;

	if (first != nullptr && first->element == element )
	{
		temp = first->next;
		delete first;
		first = temp;
		nrOfNodes--;
		wasRemoved = true;
	}

	else 
	{
		for (int i = 1; i < nrOfNodes; i++)
		{
			if (walker->next->element == element)
			{
				temp = walker->next->next;
				delete walker->next;
				walker->next = temp;
				nrOfNodes--;
				wasRemoved = true;
			}

			walker = walker->next;
		}
	}
		
	return wasRemoved;
}

template<typename T>
inline bool List<T>::findElement(const T & toFind) const
{

	bool find = false;
	Node* walker = first;
	Node* temp = nullptr;

	if (first != nullptr && first->element == toFind)
	{
		find = true;
	}

	else
	{
		for (int i = 1; i < nrOfNodes; i++)
		{
			if (walker->next->element == toFind)
			{
				find = true;
			}

			walker = walker->next;
		}
	}

	return find;
}

template<typename T>
inline void List<T>::getAll(T arr[], int cap)
{
	Node*walker = first;

	if (cap >= nrOfNodes && nrOfNodes > 0) 
	{
			for (int i = 0; i < nrOfNodes; i++)
			{
				arr[i] = walker->element;
				walker = walker->next;
			}
	}
	
	else 
	{
		throw "Capacity is not enough";
	}
}

template<typename T>
inline List<T>::Node::Node(T element)
{
	this->element = element;
	this->next = nullptr;
}

template<typename T>
inline List<T>::Node::~Node()
{
	
}

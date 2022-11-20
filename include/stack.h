// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <class T>
class Stack
{
public:
	Stack(size_t _size = 10);

	bool IsEmpty();
	bool IsFull();

	T Pop();
	void Push(const T& el);

	int GetSize();
	int GetHead();
	T GetLastEl();

	void Clear();

	~Stack();

private:
	T* indicator;
	size_t dimension;
	int head;
};

template<class T>
Stack<T>::Stack(size_t _size = 10)
{
	if (_size <= 0)
	{
		throw "U choice dimension which <= 0";
	}
	else
	{
		dimension = _size;
		head = -1;
		indicator = new T[dimension];
	}
}

template<class T>
bool Stack<T>::IsEmpty()
{
	if (head == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool Stack<T>::IsFull()
{
	if (head == dimension - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
T Stack<T>::Pop()
{
	if (IsEmpty() == 1)
	{
		throw "Stack is Empty";
	}
	else
	{
		return indicator[head--];
	}
}

template<class T>
void Stack<T>::Push(const T& el)
{
	if (IsFull() == 0)
	{
		indicator[++head] = el;
	}
	else
	{
		dimension = dimension * 2;
		T* tmp = new T[dimension];
		for (int i = 0; i < head + 1; i++)
		{
			tmp[i] = indicator[i];
		}
		delete[] indicator;
		indicator = tmp;
		indicator[++head] = el;
	}
}

template<class T>
int Stack<T>::GetSize()
{
	return dimension;
}

template<class T>
int Stack<T>::GetHead()
{
	return head;
}

template<class T>
T Stack<T>::GetLastEl()
{
	if (IsEmpty())
	{
		throw "Stack is Empty";
	}
	return indicator[head];
}

template<class T>
void Stack<T>::Clear()
{
	head = -1;
}

template<class T>
Stack<T>::~Stack()
{
	delete[] indicator;
}

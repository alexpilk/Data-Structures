// sdizo1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>

// indeks: 235067
class CList
{
	struct Element
	{
		int value;
		Element *next;

		Element(int value)
		{
			this->value = value;
			next = nullptr;
		}
		Element(Element & el)
		{
			value = el.value;
			next = el.next;
		}
	};

	int size;
	Element *head;

public:
	CList()
	{
		size = 0;
		head = nullptr;
	}

	void add(int value)
	{
		if (head == nullptr)
			head = new Element(value);
		else
		{
			Element *it = head;
			while (it->next != nullptr)
			{
				it = it->next;
			}
			it->next = new Element(value);
		}
		size++;
	}

	int getSize()
	{
		return size;
	}

	void addOnIndex(int value, int index)
	{
		if (index == 0)
			addOnFront(value);
		else if (index <= size && index > 0)
		{
			Element *el = new Element(value);
			Element *it = head;
			for (int i = 0; i < index - 1; i++)
			{
				it = it->next;
			}
			el->next = it->next;
			it->next = el;
			size++;
		}
		else
			std::cout << "index out of array" << std::endl;
	}

	void removeOnIndex(int index)
	{
		if (index == 0)
			removeOnFront();
		else if (index < size && index > 0)
		{
			Element *it = head;
			for (int i = 0; i < index - 1; i++)
			{
				it = it->next;
			}
			Element *el = it->next->next;
			delete it->next;
			it->next = el;
			size--;
		}
		else
			std::cout << "index out of array" << std::endl;
	}
	void addOnFront(int value)
	{
		Element *el = head;
		head = new Element(value);
		head->next = el;
		size++;
	}

	void removeOnFront()
	{
		if (size != 0)
		{
			Element *el = head->next;
			delete head;
			head = el;
			size--;
		}
		else
			std::cout << "empty list!!!!!" << std::endl;
	}
	void remove()
	{
		if (size != 0)
		{
			Element *it = head;
			while (it->next->next != nullptr)
			{
				it = it->next;
			}
			delete it->next;
			it->next = nullptr;
			size--;
		}
	}

	int findValue(int value)
	{		
		Element *el = head;
		for (int i = 0; el != nullptr; i++, el = el->next)
		{
			if (el->value == value)
			{
				return i;
			}
		}
		return -1;
	}

	int findOnIndex(int index, bool & success)
	{
		if (index < size && index >= 0)
		{
			Element *el = head;
			for (int i = 0; i < index; i++)
			{
				el = el->next;
			}
			success = true;
			return el->value;
		}
		
		std::cout << "index out of LIST" << std::endl;
		success = false;
		return -1;
	}

	void print()
	{
		Element* it = head;
		while (it->next != nullptr)
		{
			std::cout << it->value << std::endl;
			it = it->next;
		}
		std::cout << it->value << std::endl;
	}
};


class Stack{
	public:
		CList list;

	Stack(){
		CList *list = new CList();
	}

	void push(int element){
		list.add(element);
	}

	int pop(){
		bool *success;
		int element = list.findOnIndex(list.getSize()-1, *success);
		list.remove();
		return element;
	}

	void print(){
		list.print();
	}
};

class FIFO: public Stack{
    public:
    int pop(){
		bool *success;
		int element = list.findOnIndex(0, *success);
		list.removeOnFront();
		return element;
    }
};

void list_testing(){
	CList *list = new CList();
	list->add(3);
	list->add(-3);
	list->addOnFront(124);
	list->addOnIndex(1,3);
	list->print();
	std::cout << std::endl;
	list->removeOnIndex(0);
	list->print();
	std::cout << std::endl << std::endl;
	std::cout << list->findValue(-4);
}

void stack_testing(){
	std::cout << "Creating stack" << std::endl;
	Stack* stack = new Stack();
	stack->push(1);
	stack->push(2);
	stack->print();
	int el = stack->pop();
	std::cout << "Element popped = " << el << std::endl;
	stack->print();
}

void fifo_testing(){
	std::cout << "Creating FIFO" << std::endl;
	FIFO* fifo = new FIFO();
	fifo->push(1);
	fifo->push(2);
	fifo->print();
	int el = fifo->pop();
	std::cout << "Element popped = " << el << std::endl;
	fifo->print();
}

int main()
{
	// list_testing();
	stack_testing();
	fifo_testing();
  return 0;
}

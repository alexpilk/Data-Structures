// sdizo1.cpp : Defines the entry point for the console application.
//

#include <iostream>

// indeks: 235067
using namespace std;

struct Element
	{
		int value;
		int priority;
		int index;
		Element *next;

		Element(int value)
		{
			this->value = value;
			next = nullptr;
		}
		Element(int value, int priority)
		{
			this->value = value;
			this->priority = priority;
			next = nullptr;
		}
		Element(Element & el)
		{
			value = el.value;
			next = el.next;
		}
	};

class CList
{
	public:
	

	int size;
	Element *head;

public:
	CList()
	{
		size = 0;
		head = nullptr;
	}

	void add(int value){
		add(value, 0);
	}

	void add(int value, int priority)
	{
		if (head == nullptr)
			head = new Element(value, priority);
		else
		{
			Element *it = head;
			while (it->next != nullptr)
			{
				it = it->next;
			}
			it->next = new Element(value, priority);
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
			cout << "index out of array" << endl;
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
			cout << "index out of array" << endl;
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
			cout << "empty list!!!!!" << endl;
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

	Element* findOnIndex(int index, bool & success)
	{
		if (index < size && index >= 0)
		{
			Element *el = head;
			for (int i = 0; i < index; i++)
			{
				el = el->next;
			}
			success = true;
			return el;
		}

		cout << "index out of LIST" << endl;
		success = false;
		throw;
	}

	void print()
	{
		Element* it = head;
		while (it->next != nullptr)
		{
			cout << it->value << endl;
			it = it->next;
		}
		cout << it->value << endl;
	}
};


class Stack {
public:
	CList list;

	Stack() {
		//list = new CList();
	}

	int getSize() {
		return list.getSize();
	}

	bool empty() {
		return getSize() == 0;
	}

	void push(int el) {
		list.add(el);
	}

	int top() {
		bool success;
		int element = list.findOnIndex(list.getSize() - 1, success)->value;
		return element;
	}

	int pop() {
		int element = top();
		list.remove();
		return element;
	}

	void print() {
		list.print();
	}
};

class FIFO : public Stack {
public:
	int top() {
		bool success;
		int element = list.findOnIndex(0, success)->value;
		return element;
	}

	int pop() {
		int el = top();
		list.removeOnFront();
		return el;
	}
};

class PriorityQueue : public Stack{
	public:
	
	void push(int el, int priority) {
		list.add(el, priority);
	}

	int top(){
		return topElement()->value;
	}

	Element* topElement() {
		bool success;
		Element* max_element;
		for(int i = 0; i < getSize(); i++){
			Element* current_element = list.findOnIndex(i, success);
			if(max_element->priority <= current_element->priority){
				max_element = current_element;
				max_element->index = i;
			}
		}
		return max_element;
	}

	int pop() {
		Element* element = topElement();
		int value = element->value;
		list.removeOnIndex(element->index);
		return value;
	}
	
};
//void list_testing()
//{
//	CList *list = new CList();
//	list->add(3);
//	list->add(-3);
//	list->addOnFront(124);
//	list->addOnIndex(1,3);
//	list->print();
//	cout << endl;
//	list->removeOnIndex(0);
//	list->print();
//	cout << endl << endl;
//	cout << list->findValue(-4);
//}

void stack_testing()
{
	Stack *stack = new Stack();
	stack->push(1);
	stack->push(2);
	stack->print();
	cout << endl;
	int el = stack->top();
	cout << "Top: " << el << endl;
	stack->print();
	el = stack->pop();
	cout << "Pop: " << el << endl;
	stack->print();
}


void fifo_testing()
{
	FIFO *fifo = new FIFO();
	fifo->push(1);
	fifo->push(2);
	fifo->print();
	cout << endl;
	int el = fifo->top();
	cout << "Top: " << el << endl;
	fifo->print();
	el = fifo->pop();
	cout << "Pop: " << el << endl;
	fifo->print();
}

void prio_testing()
{
	PriorityQueue *prio = new PriorityQueue();
	prio->push(1, 0);
	prio->push(2, 3);
	prio->push(5, 0);
	prio->print();
	cout << endl;
	int el = prio->top();
	cout << "Top: " << el << endl;
	prio->print();
	el = prio->pop();
	cout << "Pop: " << el << endl;
	prio->print();
}

int main() {
	prio_testing();
	// system("pause");
	return 0;
}

#include <iostream>
#include <locale.h>
#include <time.h>
#include <chrono>

using namespace std;

class Node
{
public:
	Node* nextElem;
	int value;
	Node()
	{
		nextElem = nullptr;
	}
};

class Queue
{
public:
	Node *head;
	Queue();
	void printQueue();
	int  pop();
	void push(int x);
	void shellSort();
	int  at(int i);
	void changeValue(int i1, int i2);
	void setValue(int i1, int i2);
};

Queue::Queue()
{
	head = nullptr;
}

void Queue::printQueue()
{
	if (this->head == nullptr)
	{
		cout << "Очередь пустая" << endl;
	}
	else
	{
		Node *curElem = this->head->nextElem;
		int count = 0;
		while (curElem != nullptr)
		{
			cout << "[" << count << "]" << ": " << curElem->value << endl;
			count++;
			curElem = curElem->nextElem;
		}
	}
}

void Queue::push(int x)
{
	if (this->head == nullptr)
	{
		this->head = new Node;
		Node *curElem = new Node;
		curElem->value = x;
		this->head->nextElem = curElem;
	}
	else
	{
		Node *curElem = this->head;
		while (curElem->nextElem != nullptr)
		{
			curElem = curElem->nextElem;
		}
		curElem->nextElem = new Node;
		curElem->nextElem->value = x;
	}
}

int Queue::pop()
{
	if (this->head->nextElem == nullptr)
	{
		cout << "Удалять нечего" << endl;
		return 0;
	}
	else
	{
		Node *curElem = this->head;
		int valueDel;

		curElem = curElem->nextElem;
		valueDel = curElem->value;
		this->head->nextElem = curElem->nextElem;
		delete curElem;

		cout << endl;
		cout << "Значение, которое было удалено: " << valueDel << endl;
		return valueDel;
	}
}

int Queue::at(int i)
{
	int count_i = 0;
	Node *curElem = this->head;
	while (curElem != nullptr)
	{
		if (count_i == i)
		{
			return curElem->value;
		}
		count_i++;
		curElem = curElem->nextElem;
	}
}

void Queue::changeValue(int i1, int i2)
{
	Node *curElem = this->head;
	Node *firstElem = nullptr;
	Node *secondElem = nullptr;
	int count_i = 0;
	while (curElem != nullptr)
	{
		if (count_i == i1)
		{
			firstElem = curElem;
		}
		if (count_i == i2)
		{
			secondElem = curElem;
		}
		count_i++;
		curElem = curElem->nextElem;
	}
	firstElem->value = secondElem->value;
}

void Queue::setValue(int i, int v)
{
	int count_i = 0;
	Node *curElem = this->head;
	Node *firstElem = nullptr;
	while (curElem != nullptr)
	{
		if (count_i == i)
		{
			firstElem = curElem;
		}
		count_i++;
		curElem = curElem->nextElem;
	}
	firstElem->value = v;
}

void Queue::shellSort()
{
	Node *curElem = this->head;
	int length = 0;

	while (curElem != nullptr)
	{
		length++;
		curElem = curElem->nextElem;
	}

	int gap = length / 2;

	while (gap >= 1)
	{
		for (int i = gap; i < length; i++)
		{
			int tempVal = at(i);
			int j;
			for (j = i; j >= gap && at(j - gap) > tempVal; j -= gap)
			{
				changeValue(j, j - gap);
			}
			setValue(j, tempVal);
		}
		gap = gap / 2;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");

	int buffer;
	int n;
	Queue q;

	cout << "Кол-во элементов очереди: ";
	cin >> n;
	srand(time(0));

	for (int i = 0; i < n; i++)
	{
		buffer = rand();
		q.push(buffer);
	}

	/*cout << "Queue:" << endl;
	q.printQueue();
	q.pop();
	cout << endl;

	cout << "New Queue:" << endl;
	q.printQueue();
	cout << endl;*/

	auto beg = chrono::steady_clock::now();

	q.shellSort();
	cout << "Время сортировки: "<< chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - beg).count() << endl;
	/*cout << "Sorted Queue:" << endl;
	q.printQueue();*/
	
	system("pause");
	return 0;
}
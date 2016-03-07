#pragma once

template <class Item>
class FCFS
{
private:
	struct Node
	{
		Item item;
		struct Node * next;
	};

	Node * front;
	Node * rear;
	int items;
public:
	FCFS();
	~FCFS();
	bool isEmpty() const
	{
		return items == 0;
	}
	int size() const
	{
		return items;
	}
	bool enqueue(const Item & item);
	bool dequeue(Item & item);
};

template <class Item>
FCFS<Item>::FCFS()
{
	front = rear = nullptr;
	items = 0;
}

template <class Item>
FCFS<Item>::~FCFS()
{
	Node * temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

template<class Item>
bool FCFS<Item>::enqueue(const Item & item)
{
	Node * add = new Node;
	add->item = item;
	add->next = nullptr;
	++items;

	if (front == nullptr)
		front = add;
	else
		rear->next = add;

	rear = add;
	return true;
}

template<class Item>
bool FCFS<Item>::dequeue(Item & item)
{
	if (front == nullptr)
		return false;

	item = front->item;
	--items;
	Node * temp = front;
	front = front->next;
	delete temp;

	if (items == 0)
		rear = nullptr;

	return true;
}

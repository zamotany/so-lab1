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

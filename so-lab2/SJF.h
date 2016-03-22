#pragma once
#include "Task.h"

class SJF
{
private:
	struct Node
	{
		Task item;
		struct Node * next;
	};

	Node * front;
	int items;
public:
	SJF();
	~SJF();
	bool isEmpty() const { return items == 0; }
	int size() const { return items; }
	bool enqueue(const Task & item);
	bool dequeue(Task & item);
};

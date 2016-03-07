#include "SJF.h"

SJF::SJF()
{
	front  = nullptr;
	items = 0;
}

SJF::~SJF()
{
	Node * temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

bool SJF::enqueue(const Task & item)
{
	Node * add = new Node;
	add->item = item;
	add->next = front;
	++items;

	if (add->next = nullptr) {
		front = add;
		return true;
	}

	do {
		if (item.getTime() >= add->next->item.getTime())
		{
			add->next = add->next->next;
		}
		else break;

	} while (add->next != nullptr);
	
	return true;
}

bool SJF::dequeue(Task & item)
{
	if (front == nullptr)
		return false;

	item = front->item;
	--items;
	Node * temp = front;
	front = front->next;
	delete temp;

	return true;
}

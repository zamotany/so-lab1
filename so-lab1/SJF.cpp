#include "SJF.h"

SJF::SJF()
{
	front = nullptr;
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
	add->next = nullptr;
	++items;

	if (front == nullptr)
	{
		front = add;
		return false;
	}
	else
	{
		Node* temp = front;
		Node* prev = nullptr;
		Node* next = nullptr;
		do
		{
			if (item.getTime() <= temp->item.getTime())
				break;

			prev = temp;
			next = temp->next;

			temp = temp->next;
		} while (temp != nullptr);
		if (prev == nullptr)
		{
			add->next = front;
			front = add;
		}
		else if(next == nullptr)
		{
			prev->next = add;
		}
		else
		{
			prev->next = add;
			add->next = next;
		}
	}	
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

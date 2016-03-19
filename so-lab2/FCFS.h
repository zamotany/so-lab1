#pragma once

// \brief FCFS class.
// \details Class representing a queue that runs on FCFS (First-Come First-Served) scheduling algorithm.
template <class Item>
class FCFS
{
private:
	// \brief Struct representing a node in queue.
	// \detail Node contains actual item and poiter to the next node in queue.
	struct Node
	{
		Item item;
		struct Node * next;
	};
	
	// \var Poiter to the first item in queue.
	Node * front;
	
	// \var Poiter to the last item in queue.
	Node * rear;
	
	// \var Number of items in queue.
	int items;
public:
	// \brief Default constructor.
	FCFS();
	
	// \brief Destructor.
	~FCFS();
	
	// \brief Checks if queue is empty
	// \return True if queue is empty, false otherwise.
	bool isEmpty() const { return items == 0; }
	
	// \brief Return number of items in queue.
	// \return Number of items in queue.
	int size() const { return items; }
	
	// \brief Adds item passed in parameter to the queue.
	// \param Item which will be added to the queue.
	// \return True if adding was successful, false otherwise.
	bool enqueue(const Item & item);
	
	// \brief Pass item from front of the queue to conteiner which is passed in parameter. Deletes item from queue!
	// \param A Container to item from queue.
	// \return True if dequeuing was successful, false otherwise.
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

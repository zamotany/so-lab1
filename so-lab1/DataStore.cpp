#include "DataStore.h"

DataStore::DataStore(unsigned short store) : Store_(store), CurrentTask_(nullptr)
{
}

DataStore::~DataStore()
{
}

Task& DataStore::pop()
{
	std::lock_guard<std::mutex> lk(Mutex_);

	switch (Store_)
	{
	case 0:
		Task task;
		FCFS_.dequeue(task);
		return task;
	case 1:
		return Task();
	case 2:
		return Task();
	default:
		return Task();
	}
}

void DataStore::done()
{
	if (CurrentTask_ != nullptr && Store_ == 2)
	{
		std::lock_guard<std::mutex> lk(Mutex_);
	}
}

void DataStore::add(const Task & task)
{
	std::lock_guard<std::mutex> lk(Mutex_);

	if (Store_ == 0)
		FCFS_.enqueue(task);
	//temp
}

#include "DataStore.h"

DataStore::DataStore(unsigned short store) : Store_(store), CurrentTaskValid_(false)
{
}

DataStore::~DataStore()
{
}

Task& DataStore::pop()
{
	std::lock_guard<std::mutex> lk(Mutex_);

	Task task;

	switch (Store_)
	{
	case 0:
		FCFS_.dequeue(task);
		break;
	case 1:
		break;
	case 2:
		CurrentTask_ = RR_.pop();
		CurrentTaskValid_ = true;
		break;
	default:
		break;
	}

	return task;
}

void DataStore::done()
{
	if (CurrentTaskValid_ && Store_ == 2)
	{
		std::lock_guard<std::mutex> lk(Mutex_);
		if (!CurrentTask_.isFinished())
		{
			RR_.push(CurrentTask_);
			CurrentTaskValid_ = false;
		}
	}
}

void DataStore::add(const Task& task)
{
	std::lock_guard<std::mutex> lk(Mutex_);

	switch (Store_)
	{
	case 0:
		FCFS_.enqueue(task);
		break;
	case 1:
		break;
	case 2:
		RR_.push(task);
		break;
	default:
		break;
	}
}

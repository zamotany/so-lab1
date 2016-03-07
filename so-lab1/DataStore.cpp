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

	switch (Store_)
	{
	case 0:
		Task task;
		FCFS_.dequeue(task);
		return task;
	case 1:
		return Task();
	case 2:
		CurrentTask_ = RR_.pop();
		CurrentTaskValid_ = true;
		return CurrentTask_;
	default:
		return Task();
	}
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

	if (Store_ == 0)
		FCFS_.enqueue(task);
	else if (Store_ == 2)
		RR_.push(task);
	//temp
}

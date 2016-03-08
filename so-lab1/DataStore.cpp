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
		if(!FCFS_.isEmpty())
			FCFS_.dequeue(task);
		break;
	case 1:
		if(!SJF_.isEmpty())
			SJF_.dequeue(task);
		break;
	case 2:
		if (!RR_.isEmpty())
		{
			CurrentTask_ = RR_.pop();
			CurrentTaskValid_ = true;
			task = CurrentTask_;
		}
		break;
	default:
		break;
	}

	return task;
}

bool DataStore::done(unsigned int timeQuant)
{
	if (CurrentTaskValid_ && Store_ == 2)
	{
		std::lock_guard<std::mutex> lk(Mutex_);
		if (!CurrentTask_.isFinished())
		{
			CurrentTask_.setCurrentState(timeQuant);
			RR_.push(CurrentTask_);
			CurrentTaskValid_ = false;
			return false;
		}
	}
	return true;
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
		SJF_.enqueue(task);
		break;
	case 2:
		RR_.push(task);
		break;
	default:
		break;
	}
}

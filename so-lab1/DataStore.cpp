#include "DataStore.h"

DataStore::DataStore(unsigned short store) : Store_(store)
{
}

DataStore::~DataStore()
{
}

Task* DataStore::top()
{
	if (Store_ == 0)
		return nullptr;
}

void DataStore::remove(Task * task)
{
	if (Store_ == 0)
		return;
}

Task DataStore::pop()
{
	return Task(); //TEMP
}

void DataStore::add(const Task & task)
{
	if (Store_ == 0)
		FCFS_.enqueue(task);
	//temp
}

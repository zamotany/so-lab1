#pragma once

#include "Task.h"
#include "FCFS.h"
#include <mutex>

class DataStore
{
public:
	// \brief Default constructor.
	// \param store Storing mechanism (0 - FCFS, 1 - SJF, 2 - RR).
	DataStore(unsigned short store);

	// \brief Default destructor.
	~DataStore();

	// \brief Get next element.
	// \note Does not remove returned element.
	// \return Pointer to element.
	Task* top();

	// \brief Remove specified element if present.
	// \param Pointer to element to remove.
	void remove(Task* task);

	// \brief Get next element and remove it from data store.
	// \return Element.
	Task pop();
	
	// \brief Add element to data store.
	// \param task Element to add.
	void add(const Task& task);
private:
	FCFS<Task> FCFS_;
	unsigned short Store_;
	std::mutex Mutex_;
	
};
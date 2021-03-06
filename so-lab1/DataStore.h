#pragma once

#include "Task.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
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
	// \return Referenece to element.
	Task& pop();

	// \brief Signalize end of time quant in RR.
	// \param timeQuant Quant of time used in RR.
	// \return True if task was completed, false otherwise.
	bool done(unsigned int timeQuant);
	
	// \brief Add element to data store.
	// \param task Element to add.
	void add(const Task& task);
private:
	FCFS<Task> FCFS_;
	RR<Task> RR_;
	SJF SJF_;

	unsigned short Store_;
	Task CurrentTask_;
	bool CurrentTaskValid_;
	std::mutex Mutex_;
	
};
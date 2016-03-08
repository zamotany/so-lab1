#pragma once

#include <thread>
#include "Task.h"

// \brief CPU simulator.
// \author Pawe³ Trys³a
class Processor
{
public:
	// \brief Default constructor.
	Processor();

	// \brief Default destructor.
	~Processor();

	// \brief Set mode to round robin with given time quant.
	// \param timeQuant Quant of time.
	void setRoundRobin(unsigned long timeQuant);

	// \brief Execute task.
	// \param Task reference to execute.
	void execute(Task& task);
private:
	bool IsRR_;
	unsigned long TimeQuant_;
};
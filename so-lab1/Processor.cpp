#include "Processor.h"

Processor::Processor() : IsRR_(false)
{
}

Processor::~Processor()
{
}

void Processor::setRoundRobin(unsigned long timeQuant)
{
	IsRR_ = true;
	TimeQuant_ = timeQuant;
}

void Processor::execute(Task& task)
{
	if (IsRR_)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(TimeQuant_));
		task.setCurrentState(task.getTime() + TimeQuant_);
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(task.getTime()));
		task.setCurrentState(task.getTime());
	}
}
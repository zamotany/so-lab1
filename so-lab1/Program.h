#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include "DataStore.h"
#include "Task.h"
#include "extlib\Random.h"
#include "extlib\INIParser.h"

class Program
{
public:
	// \brief Default constructor.
	// \param config Path to configuration file.
	Program(const std::string config);

	// \brief Default destructor.
	~Program();

	// \brief Execute mathod.
	// \return Status code.
	int exec();
private:
	void WorkerTask_();
	bool Exit_;
	std::mutex Mutex_;
	std::thread Worker_;
	std::condition_variable BreakCond_;

	sfe::INIParser Config_;
	DataStore DS_;
	std::chrono::milliseconds Interval_;
	std::chrono::duration<double> Accumulator_;
	unsigned long MinTaskDuration_;
	unsigned long MaxTaskDuration_;
};
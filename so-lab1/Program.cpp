#include "Program.h"

Program::Program(const std::string config) : Exit_(false), Config_(config), DS_(Config_.getInt("DS", "Mechanism", 0))
{
	Interval_ = std::chrono::milliseconds(Config_.getInt("Generator", "Interval", 1000));
	Accumulator_ = std::chrono::milliseconds::zero();
	MinTaskDuration_ = Config_.getInt("Generator", "MinTaskDuration", 1);
	MaxTaskDuration_ = Config_.getInt("Generator", "MaxTaskDuration", 1000000000);
}

Program::~Program()
{
	{
		std::lock_guard<std::mutex> lk(Mutex_);
		Exit_ = true;
	}
	BreakCond_.notify_one();
	if (Worker_.joinable())
		Worker_.join();
}

int Program::exec()
{
	Worker_ = std::thread(&Program::WorkerTask_, this);

	bool isRR = Config_.getInt("DS", "Mechanism", 0) == 2;
	unsigned long tasksToExecute = Config_.getInt("CPU", "TasksToExecute", 0);
	unsigned long timeQuant = Config_.getInt("CPU", "TimeQuant", 1);

	if (isRR)
		CPU_.setRoundRobin(timeQuant);

	while (tasksToExecute > 0)
	{
		Task task = DS_.pop();
		if (task.getTime() != 0)
		{
			std::cout << "New task: " << task.getTime() << " status: " << task.getCurrentState() << std::endl;
			CPU_.execute(task);
			DS_.done(timeQuant);
			tasksToExecute--;
		}
	}
	std::cin.get();
	return 0;
}

void Program::WorkerTask_()
{
	bool exit = false;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	Random rand;

	while (!exit)
	{
		start = std::chrono::system_clock::now();

		if (Accumulator_ >= Interval_)
		{
			Task task;
			task.setTime(rand.next(MinTaskDuration_, MaxTaskDuration_));
			DS_.add(task);
			//std::cout << "New task: " << task.getTime() << std::endl;

			Accumulator_ = std::chrono::milliseconds::zero();
		}

		{
			std::unique_lock<std::mutex> lk(Mutex_);
			if (BreakCond_.wait_for(lk, std::chrono::milliseconds(10), [this]() { return Exit_; }))
				exit = Exit_;
		}
		
		end = std::chrono::system_clock::now();
		Accumulator_ += end - start;
	}
}

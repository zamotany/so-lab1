#pragma once

// \brief A Task class.
// \details A class representing procesor task.

class Task
{
private:
	// \var Time needed to process the task.
	unsigned long time;
	
	// \var Current state of the task processing (time procesor spend on task).
	unsigned long currentState;
public:
	// \brief Default constructor.
	Task() { time = currentState = 0L; }

	// \brief Sets time required to process task.
	// \param time required to process task.
	void setTime(unsigned long value) { time = value; }

	// \brief Returns time needed to process task.
	// \return Time needed to process task.
	unsigned long getTime() const { return time; }

	// \brief Checks if task is finished.
	// \return True if task is finished, false otherwise.
	bool isFinished() const { return currentState >= time; }

	// \brief Sets current state of task (time that task was processed).
	// \param Current state of task.
	void setCurrentState(unsigned long value)
	{
		currentState += value;
		if (currentState > time)
			currentState = time;
	}

	// \brief Returns current state of task.
	// \return Current state of task.
	unsigned long getCurrentState() const { return currentState; }

	// \brief Resets current state of task (Sets time that task was processed).
	void reset() { currentState = 0L; }
};

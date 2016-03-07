#pragma once

//! \brief A Task class.
//! \details A class representing procesor task.

class Task
{
private:
	unsigned long time;			//! \var Time needed to process the task.
	unsigned long currentState;	//! \var Current state of the task processing (time procesor spend on task).
public:
	Task() { time = currentState = 0L; }								//! \fn 
	void setTime(unsigned long value) { time = value; }
	bool isFinished() const { return !(currentState <= time); }
	void setCurrentState(unsigned long value) { currentState = value; }
	unsigned long getCurrentState() const { return currentState; }
	void reset() { currentState = 0L; }
};

#pragma once

//! \brief A Task class.
//! \details A class representing procesor task.

class Task
{
private:
	int time;			//! \var Time needed to process the task.
	int currentState;	//! \var Current state of the task processing (time procesor spend on task).
public:
	Task() { time = currentState = 0; }								//! \fn 
	void setTime(int value) { time = value; }
	bool isFinished() const { return !(currentState <= time); }
	void setCurrentState(int value) { currentState = value; }
	int getCurrentState() const { return currentState; }
	void reset() { currentState = 0; }
};

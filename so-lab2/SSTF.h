#pragma once
#include <cmath>

// \brief SSTF algorythm class.
// \details Class representing a queue that runs on SSTF (Shortest Seek Time First) disk scheduling algorithm.
class SSTF
{
private:
	// \var Actual position of the virtual disk head.
	unsigned int m_headPosition;

	// \var Pointer to the array of next positions.
	unsigned int * m_array;

	// \var Size of the array.
	size_t m_size;
public:
	// \brief Default constructor.
	// \param headPosition Initial position of the head, 0 by default.
	SSTF(unsigned int headPosition = 0);
	
	// \brief Sets head on the given position.
	// \param newPosition New position of the head.
	void setHeadPosition(unsigned int newPosition) { m_headPosition = newPosition; }

	// \brief Load an array of next positions of the head.
	// \param arr          Pointer to an array.
	// \param size         Size of the given array.
	void load(const unsigned int * arr, size_t size);

	// \brief Returns next nearest position of the head.
	// \return Next nearest position of the head.
	unsigned int getNext();

	// \brief Destructor.
	~SSTF();
};

#include "SSTF.h"

SSTF::SSTF(unsigned int headPosition)
{
	m_headPosition = headPosition;
	m_size = 0;
	m_array = nullptr;
}

void SSTF::load(const unsigned int * arr, size_t size)
{
	m_size = size;
	m_array = new unsigned int[m_size];
	
	for (size_t i = 0; i < m_size; ++i)
		m_array[i] = arr[i];
}

unsigned int SSTF::getNext()
{
	unsigned int min = std::abs((long)m_headPosition - (long)m_array[0]);

	size_t index = 0;
	for (size_t i = 1; i < m_size; ++i)
		if ((unsigned int)std::abs((long)m_headPosition - (long)m_array[i]) < min)
		{
			min = std::abs((long)m_headPosition - (long)m_array[i]);
			m_headPosition = m_array[i];
			index = i;
		}
	if (index == 0) m_headPosition = m_array[0];
	--m_size;
	for (size_t i = index; i < m_size; ++i)
		m_array[i] = m_array[i + 1];

	return m_headPosition;
}

SSTF::~SSTF()
{
	delete[] m_array;
}

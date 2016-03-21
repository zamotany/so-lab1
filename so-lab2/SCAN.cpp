#include "SCAN.h"

SCAN::SCAN(unsigned int n, unsigned int headPosition)
{
	m_maxPosition = n;
	m_headPosition = headPosition;
	m_lastHeadPosition = m_headPosition;
	m_size = 0;
	m_array = nullptr;
}

void SCAN::setHeadPosition(unsigned int newPosition)
{
	m_lastHeadPosition = m_headPosition;
	m_headPosition = newPosition;
}

void SCAN::load(const unsigned int * arr, size_t size)
{
	m_size = size;
	m_array = new unsigned int[m_size];

	for (size_t i = 0; i < m_size; ++i)
		m_array[i] = arr[i];

	size_t min = 0;
	size_t max = size - 1;
	long long p;
	do
	{
		p = -1;
		for (size_t i = min; i < max; ++i)
			if (m_array[i] > m_array[i + 1])
			{
				std::swap(m_array[i], m_array[i + 1]);
				if (p < 0) min = i;
				p = i;
			}
		if (min) min--;
		max = p;
	} while (p >= 0);
}

unsigned int SCAN::getNext()
{
	if (m_headPosition < (unsigned int)std::abs((long)m_headPosition - (long)m_maxPosition))
	{
		if (m_headPosition >= m_array[0])
		{
			unsigned int min = std::abs((long)m_headPosition - (long)m_array[0]);
			m_headPosition = m_array[0];
			for (size_t i = 1; i < m_size, m_array[i] < m_headPosition; ++i)
			{
				if ((unsigned int)std::abs((long)m_headPosition - (long)m_array[i]) < min)
				{
					min = (unsigned int)std::abs((long)m_headPosition - (long)m_array[i]);
					m_lastHeadPosition = m_headPosition;
					m_headPosition = m_array[i];
				}
			}
		}
		else if (m_lastHeadPosition == m_maxPosition && m_headPosition == 0)
		{
			m_lastHeadPosition = m_headPosition;
			m_headPosition = m_array[0];
		}
		else if (m_headPosition == 0)
		{
			m_lastHeadPosition = m_headPosition;
			m_headPosition = m_maxPosition;
		}
	}
	else
	{
		if (m_headPosition <= m_array[m_size - 1])
		{
			unsigned int min = std::abs((long)m_headPosition - (long)m_array[m_size - 1]);
			m_headPosition = m_array[m_size - 1];
			for (size_t i = m_size - 1; i >= 0, m_array[i] > m_headPosition; --i)
			{
				if ((unsigned int)std::abs((long)m_headPosition - (long)m_array[i]) < min)
				{
					min = (unsigned int)std::abs((long)m_headPosition - (long)m_array[i]);
					m_lastHeadPosition = m_headPosition;
					m_headPosition = m_array[i];
				}
			}
		}
		else if (m_lastHeadPosition == 0 && m_headPosition == m_maxPosition)
		{
			m_lastHeadPosition = m_headPosition;
			m_headPosition = m_array[m_size - 1];
		}
		else if (m_headPosition == m_maxPosition)
		{
			m_lastHeadPosition = m_headPosition;
			m_headPosition = 0;
		}
	}

	return m_headPosition;
}

SCAN::~SCAN()
{
	delete[] m_array;
}

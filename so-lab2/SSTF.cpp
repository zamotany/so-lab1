#include "SSTF.h"

SSTF::SSTF(unsigned int headPosition)
{
	_headPosition = headPosition;
	_size = 0;
	_array = nullptr;
}

void SSTF::load(const unsigned int * arr, size_t size)
{
	_size = size;
	_array = new unsigned int[_size];
	
	for (size_t i = 0; i < _size; ++i)
		_array[i] = arr[i];
}

unsigned int SSTF::getNext()
{
	unsigned int min = std::abs((long)_headPosition - (long)_array[0]);

	size_t index = 0;
	for (size_t i = 1; i < _size; ++i)
		if ((unsigned int)std::abs((long)_headPosition - (long)_array[i]) < min)
		{
			min = std::abs((long)_headPosition - (long)_array[i]);
			_headPosition = _array[i];
			index = i;
		}
	if (index == 0) _headPosition = _array[0];
	--_size;
	for (size_t i = index; i < _size; ++i)
		_array[i] = _array[i + 1];

	return _headPosition;
}

SSTF::~SSTF()
{
	delete[] _array;
}

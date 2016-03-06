#pragma once

#include <queue>

template <typename T> class RR
{
public:
	// \brief Push item to queue.
	// \param item Item to push.
	void push(const T& item)
	{
		Store_.push(item);
	}

	// \brief Pop front item.
	// \return Poped item.
	T pop()
	{
		T item = Store_.front();
		Store_.pop();
		return item;
	}
private:
	std::queue<T> Store_;
};
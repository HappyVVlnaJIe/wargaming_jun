#pragma once

#include <mutex>
#include <memory>

/*
* +:
*	данные хранятся в куче 
*	есть Mutex что позволяет работать с большим кол-вом потоков
*	благодаря умным указателям не будет утечек данных буфера при уничтожении буфера
* -:
*	данные хранятся в куче
*/

template <class DATA_T>
class CircularBuffer {
public:
	explicit CircularBuffer(size_t max_size) :
		data(std::unique_ptr<DATA_T[]>(new DATA_T[max_size])),
		max_size(max_size)
		{};

	void Add(DATA_T value);
	DATA_T Get();
	void Clear();
	bool Empty() const;
	bool Full() const;
	size_t MaxSize() const;
	size_t Size() const;

private:
	std::mutex mutex;
	std::unique_ptr<DATA_T[]> data;
	size_t head = 0;
	size_t tail = 0;
	const size_t max_size;
	bool full = false;
};

template<class DATA_T>
inline void CircularBuffer<DATA_T>::Add(DATA_T value)
{
	std::lock_guard<std::mutex> lock(mutex);

	data[head] = value;

	if (Full())
	{
		tail = (tail + 1) % max_size;
	}

	head = (head + 1) % max_size;

	full = head == tail;
}

template<class DATA_T>
inline DATA_T CircularBuffer<DATA_T>::Get()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (Empty()) {
		throw BufferIsEmpty();
	}
	DATA_T result = data[tail];
	full = false;
	tail = (tail + 1) % max_size;

	return result;
}

template<class DATA_T>
inline void CircularBuffer<DATA_T>::Clear()
{
	std::lock_guard<std::mutex> lock(mutex);
	head = tail;
	full = false;
}

template<class DATA_T>
inline bool CircularBuffer<DATA_T>::Empty() const
{
	return (!Full() && (head == tail));
}

template<class DATA_T>
inline bool CircularBuffer<DATA_T>::Full() const
{
	return full;
}

template<class DATA_T>
inline size_t CircularBuffer<DATA_T>::MaxSize() const
{
	return max_size;
}

template<class DATA_T>
inline size_t CircularBuffer<DATA_T>::Size() const
{
	if (!Full()) {
		return (head >= tail) ? head - tail : max_size + head - tail;
	}
	else {
		return MaxSize();
	}
}

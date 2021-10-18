#pragma once

#include "errors.h"

/*
* +:
*	данные хранятся в стеке
*	есть доступ по индексу
* -:
*	данные хранятся в стеке
*	если больше 2-х потоков нужны критические секции при обращении к буферу
*	кол-во записей/чтений без очистки буфер не должно быть больше SIZE_MAX
*/

template<size_t max_size, typename DATA_T>
class CircularBufferWithArray {
private:
	DATA_T data[max_size];
	size_t read_count=0, write_count=0; // количество чтений/записей
public:
	void Add(DATA_T value);
	DATA_T Read();
	DATA_T& operator[](size_t index);
	const DATA_T& operator[](size_t index) const;
	bool IsEmpty();
	bool IsFull();
	size_t Size() const; //кол-во элементов в буфере
	size_t MaxSize() const; //размер буфера
	void Clear();
};

template<size_t max_size, typename DATA_T>
inline void CircularBufferWithArray<max_size, DATA_T>::Add(DATA_T value)
{
	if (IsFull()) {
		throw BufferIsFull();
	}
	data[write_count%max_size] = value;
	write_count++;
}

template<size_t max_size, typename DATA_T>
inline DATA_T CircularBufferWithArray<max_size, DATA_T>::Read()
{
	if (IsEmpty()) {
		throw BufferIsEmpty();
	}
	size_t cur_read_index = read_count%max_size;
	read_count++;
	return data[cur_read_index];
}

template<size_t max_size, typename DATA_T>
inline DATA_T& CircularBufferWithArray<max_size, DATA_T>::operator[](size_t index)
{
	if (IsEmpty()) {
		throw BufferIsEmpty();
	}
	if (index >= MaxSize()) {
		throw BufferIndexOutOfBounds();
	}
	if (index >= Size()) {
		throw BufferIndexMoreCount();
	}
	return data[(read_count+index)% max_size];
}

template<size_t max_size, typename DATA_T>
inline const DATA_T& CircularBufferWithArray<max_size, DATA_T>::operator[](size_t index) const
{
	if (IsEmpty()) {
		throw BufferIsEmpty();
	}
	if (index >= MaxSize()) {
		throw BufferIndexOutOfBounds();
	}
	if (index >= Size()) {
		throw BufferIndexMoreCount();
	}
	return data[(read_count + index) % max_size];
}

template<size_t max_size, typename DATA_T>
inline bool CircularBufferWithArray<max_size, DATA_T>::IsEmpty()
{
	return write_count==read_count;
}

template<size_t max_size, typename DATA_T>
inline bool CircularBufferWithArray<max_size, DATA_T>::IsFull()
{
	return (write_count-read_count)==max_size;
}

template<size_t max_size, typename DATA_T>
inline size_t CircularBufferWithArray<max_size, DATA_T>::Size() const
{
	return write_count-read_count;
}

template<size_t max_size, typename DATA_T>
inline size_t CircularBufferWithArray<max_size, DATA_T>::MaxSize() const
{
	return max_size;
}

template<size_t max_size, typename DATA_T>
inline void CircularBufferWithArray<max_size, DATA_T>::Clear()
{
	read_count = 0;
	write_count = 0;
}

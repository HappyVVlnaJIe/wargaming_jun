#include "function_for_p1.h"
#include "circular_buffer_with_array.h"
#include "circular_buffer_with_unique_ptr.h"
#include "test_runner.h"
#include "sort_for_p3.h"

#include <iostream>
#include <numeric>

void TestCircularBufferWithArray() {
	CircularBufferWithArray<10, int> circular_buffer;

	ASSERT_EQUAL(circular_buffer.MaxSize(), 10);

	for (int i = 0; i < 10; i++) {
		circular_buffer.Add(i);
	}
	try
	{
		circular_buffer.Add(10);
		std::cout << "<Buffer is full> exception not work (function Add) in FILE:" << __FILE__ << ":" << __LINE__ << std::endl;
	}
	catch (const std::exception& e)
	{
		ASSERT_EQUAL(e.what(), BufferIsFull::error_text);
	}

	ASSERT_EQUAL(circular_buffer.IsFull(), true);
	ASSERT_EQUAL(circular_buffer.Size(), 10);

	vector<int> read_result;
	vector<int> expected_read_result(10); /*= { 0,1,2,3,4,5,6,7,8,9 }*/;
	std::iota(expected_read_result.begin(),expected_read_result.end(),0);
	for (int i = 0; i < 10; i++) {
		read_result.push_back(circular_buffer.Read());
	}
	ASSERT_EQUAL(read_result, expected_read_result);
	try
	{
		circular_buffer.Read();
		std::cout << "<Buffer is empty> exception not work(function Read) in FILE:" << __FILE__ << ":" << __LINE__ << std::endl;
	}
	catch (const std::exception& e)
	{
		ASSERT_EQUAL(e.what(), BufferIsEmpty::error_text);
	}

	ASSERT_EQUAL(circular_buffer.IsFull(), false);

	try
	{
		auto temp=circular_buffer[circular_buffer.Size()];
		std::cout << "<Buffer is empty> exception not work(function operator[]) in FILE: " << __FILE__ << ":" << __LINE__ << std::endl;
	}
	catch (const std::exception& e)
	{
		ASSERT_EQUAL(e.what(), BufferIsEmpty::error_text);
	}
	circular_buffer.Add(2);
	try
	{
		auto temp = circular_buffer[1];
		std::cout << "<Buffer index more count> exception not work(function operator[]) in FILE:" << __FILE__ << ":" << __LINE__<<std::endl;
	}
	catch (const std::exception& e)
	{
		ASSERT_EQUAL(e.what(), BufferIndexMoreCount::error_text);
	}
	try
	{
		auto temp = circular_buffer[10];
		std::cout << "<Buffer index out of bounds> exception not work(function operator[]) in FILE:" << __FILE__ << ":" << __LINE__ << std::endl;
	}
	catch (const std::exception& e)
	{
		ASSERT_EQUAL(e.what(), BufferIndexOutOfBounds::error_text);
	}
	try
	{
		auto temp = circular_buffer[0];
	}
	catch (const std::exception& e)
	{
		std::cout<<e.what()<<"in FILE:" << __FILE__ << ":" << __LINE__ << std::endl;
	}

	ASSERT_EQUAL(circular_buffer.IsEmpty(), false);
	circular_buffer.Read();
	ASSERT_EQUAL(circular_buffer.IsEmpty(), true);

	circular_buffer.Add(1);
	ASSERT_EQUAL(circular_buffer.Size(), 1);
	circular_buffer.Clear();
	ASSERT_EQUAL(circular_buffer.Size(), 0);
}

void TestCircularBufferWithUniquePtr() {

	CircularBuffer<int> circular_buffer(3);

	ASSERT_EQUAL(circular_buffer.MaxSize(), 3);
	ASSERT_EQUAL(circular_buffer.Empty(), true);
	ASSERT_EQUAL(circular_buffer.Full(), false);

	int x = 1, y=2,z=3;
	vector<int> expected_result;
	circular_buffer.Add(x); expected_result.push_back(x);
	circular_buffer.Add(y); expected_result.push_back(y);
	circular_buffer.Add(z); expected_result.push_back(z);

	ASSERT_EQUAL(circular_buffer.Size(), 3);
	ASSERT_EQUAL(circular_buffer.Empty(), false);
	ASSERT_EQUAL(circular_buffer.Full(), true);
	
	vector<int> read_result;
	try
	{
		for (size_t i = 0; i < circular_buffer.MaxSize(); i++) {
			read_result.push_back(circular_buffer.Get());
		}		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "in FILE:" << __FILE__ << ":" << __LINE__ << std::endl;
	}
	ASSERT_EQUAL(read_result, expected_result);
	try
	{
		circular_buffer.Get();
	}
	catch (const std::exception& e)
	{
		ASSERT_EQUAL(e.what(), BufferIsEmpty::error_text);
	}
}

void RadixSortTest() {
	vector<unsigned> input = { 5,10,15,20,25,50,40,30,20,10,9524,878,17,1,99,18785,3649,164,94,
		123,432,654,3123,654,2123,543,131,653,123,533,1141,532,213,2241,824,1124,42,134,411,
		491,341,1234,527,388,245,1992,654,243,987 };
	vector<unsigned> output(input.size());
	vector<unsigned> expected_output=input;
	std::sort(expected_output.begin(), expected_output.end());
	radixSort(input.begin(), input.end(), output.begin());

	ASSERT_EQUAL(output, expected_output);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCircularBufferWithArray);
	RUN_TEST(tr, TestCircularBufferWithUniquePtr);
	RUN_TEST(tr, RadixSortTest);
	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>        
#include <iterator>            
#include <queue>            
using namespace std;

/*
* radix sort самая быстрая из сортировок, насколько я знаю
*/

template <typename InputIterator, typename OutputIterator> 
void radixSort(InputIterator start, InputIterator end, OutputIterator output) {
    const int BASE = 10;  
    std::queue<typename std::iterator_traits<OutputIterator>::value_type > bucket[BASE];    

    unsigned size = end - start;

    typename std::iterator_traits<InputIterator>::value_type max = *std::max_element(start, end);    // O(n)


    std::copy(start, end, output);    // O(n)

    // Iterative Radix Sort - if k is log BASE (max), then the complexity is O( k * n)
    for (unsigned power = 1; max != 0; max /= BASE, power *= BASE) { // If BASE was 2, can use shift. Although compiler should be smart enough to optimise this.
        for (OutputIterator it = output; it != output + size; it++) {
            unsigned bucketNumber = (unsigned)((*it / power) % BASE);
            bucket[bucketNumber].push(*it);        // O(1)
        }
        OutputIterator it = output;
        for (int i = 0; i < BASE; i++) {
            int bucketSize = bucket[i].size();
            for (int j = 0; j < bucketSize; j++) {
                *it = bucket[i].front();
                bucket[i].pop();
                it++;
            }
        }
    }
}
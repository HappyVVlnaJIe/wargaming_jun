#include "errors.h"

const std::string BufferIsFull::error_text = "You can't add new element. Buffer is full";
const std::string BufferIndexOutOfBounds::error_text = "Buffer index out of bounds";
const std::string BufferIsEmpty::error_text = "Buffer is empty";
const std::string BufferIndexMoreCount::error_text = "Buffer index more count of elements in buffer";
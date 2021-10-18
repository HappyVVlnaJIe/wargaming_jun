#pragma once

#include <exception>
#include <stdexcept>

class BufferIsFull : public std::runtime_error {
public:
    BufferIsFull() :std::runtime_error{ error_text }{};
    static const std::string error_text;
};

class BufferIndexOutOfBounds : public std::runtime_error {
public:
    BufferIndexOutOfBounds() :std::runtime_error{ error_text }{};
    static const std::string error_text;
};

class BufferIsEmpty : public std::runtime_error {
public:
    BufferIsEmpty() :std::runtime_error{ error_text }{};
    static const std::string error_text;
};

class BufferIndexMoreCount : public std::runtime_error {
public:
    BufferIndexMoreCount() :std::runtime_error{ error_text }{};
    static const std::string error_text;
};

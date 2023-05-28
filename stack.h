
#ifndef STACK_H
#define STACK_H

#include "quack.h"

template <class T>
class Stack {
public:
    void push(T newItem);

    T pop();

    T peek();

    bool isEmpty() const;

private:
    Quack<T> myStack;
};

#include "stack.cpp"  
#endif

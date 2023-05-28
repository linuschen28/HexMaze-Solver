
#ifndef QUEUE_H
#define QUEUE_H

#include "quack.h"

template <class T>
class Queue {
public:
    void enqueue(T newItem);


    T dequeue();

    T peek();

    bool isEmpty() const;

private:
    Quack<T> myQueue;
};
#include "queue.cpp"
#endif

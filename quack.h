
#ifndef QUACK_H
#define QUACK_H

#include <vector>
using namespace std;

template <class T>
class Quack {
public:
    Quack();

    void pushR(T newItem);

    T popL();

    T popR();

    T peekL();

    T peekR();

    bool isEmpty() const;

private:
    vector<T> data; /* Store the quack data here! */
    int n1;
    int n2;
};

#include "quack.cpp"
#endif

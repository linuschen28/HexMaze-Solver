
template <class T>
void Stack<T>::push(T newItem) {
    myStack.pushR(newItem);
}

template <class T>
T Stack<T>::pop() {
    return myStack.popR();
}

template <class T>
T Stack<T>::peek() {
    return myStack.peekR();
}

template <class T>
bool Stack<T>::isEmpty() const {
    return myStack.isEmpty();
}
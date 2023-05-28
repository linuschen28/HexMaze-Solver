
template <class T>
void Queue<T>::enqueue(T newItem) {
    myQueue.pushR(newItem);
}

template <class T>
T Queue<T>::dequeue() {
    return myQueue.popL();
}

template <class T>
T Queue<T>::peek() {
    return myQueue.peekL();
}

template <class T>
bool Queue<T>::isEmpty() const {
    return myQueue.isEmpty();
}

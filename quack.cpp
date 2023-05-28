
template <class T>
Quack<T>::Quack() {
    n1 = 0; // left end (front of vector)
    n2 = -1; // right end (back of vector)
}

template <class T>
void Quack<T>::pushR(T newItem) {
    data.push_back(newItem);
    n2++;
}

template <class T>
T Quack<T>::popL() {
    T dummy;
    if (isEmpty()) {
        return dummy;
    }
    T temp = data[n1];
    data[n1] = NULL;
    n1++;
    
    int data_size = n2 - n1 + 1;
    int resized_vector = n1;
    vector<T> resized_data (data_size, dummy);
    if (resized_vector >= data_size) {
        for (int i = 0; i <= data_size - 1; i++) {
            resized_data[i] = data[n1];
            n1++;
        }
        data = resized_data;
        n1 = 0;
        n2 = data_size - 1;
    }

    return temp;
}

template <class T>
T Quack<T>::popR() {
    T dummy;
    if (isEmpty()) {
        return dummy;
    }
    T temp = data[n2];
    data.pop_back();
    n2--;

    int data_size = n2 - n1 + 1;
    int resized_vector = n1;
    vector<T> resized_data (data_size, dummy);
    if (resized_vector >= data_size) {
        for (int i = 0; i <= data_size - 1; i++) {
            resized_data[i] = data[n1];
            n1++;
        }
        data = resized_data;
        n1 = 0;
        n2 = data_size - 1;
    }

    return temp;
}

template <class T>
T Quack<T>::peekL() {
    if (isEmpty()) {
        T dummy;
        return dummy;
    }
    return data[n1];
}

template <class T>
T Quack<T>::peekR() {
    if (isEmpty()) {
        T dummy;
        return dummy;
    }
    return data[n2];
}

template <class T>
bool Quack<T>::isEmpty() const {
    if (n2 < n1) return true;
    return false;
}

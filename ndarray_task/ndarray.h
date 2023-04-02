#ifndef NDARRAY_NDARRAY_H
#define NDARRAY_NDARRAY_H


#include <iostream>
#include <cstdlib>
#include <ctime>


template <typename T>
class NDArray {
private:
    int dimension;
    T *arr;
    int *shape;

public:
    NDArray(int d, int s[]) {
        dimension = d;
        shape = new int[dimension];
        for (int i = 0; i < dimension; i++) {
            shape[i] = s[i];
        }
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        arr = new T[size];
    }

    NDArray(const NDArray &x) {
        dimension = x.dimension;
        shape = new int[dimension];
        for (int i = 0; i < dimension; i++) {
            shape[i] = x.shape[i];
        }
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = x.arr[i];
        }
    }
    // fill zero
    void fill_zeros() {
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        for (int i = 0; i < size; i++) {
            arr[i] = static_cast<T>(0);
        }
    }

    // fill one
    void fill_ones() {
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        for (int i = 0; i < size; i++) {
            arr[i] = static_cast<T>(1);
        }
    }

    // fill random
    void fill_random() {
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        std::srand(std::time(NULL));
        for (int i = 0; i < size; i++) {
            arr[i] = static_cast<T>(std::rand()) / static_cast<T>(1);
        }
    }

    // array print
    void print() {
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ", ";
        }
        std::cout << "]" << std::endl;
    }

    // addition
    NDArray<T> operator+(NDArray<T> const &obj) {
        NDArray<T> result(dimension, shape);
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] + obj.arr[i];
        }
        return result;
    }

    // subtraction
    NDArray<T> operator-(NDArray<T> const &obj) {
        NDArray<T> result(dimension, shape);
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] - obj.arr[i];
        }
        return result;
    }

    //multiply
    NDArray<T> operator*(NDArray<T> const &obj) {
        NDArray<T> result(dimension, shape);
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] * obj.arr[i];
        }
        return result;
    }

    //division
    NDArray<T> operator/(NDArray<T> const &obj) {
        NDArray<T> result(dimension, shape);
        int size = 1;
        for (int i = 0; i < dimension; i++) {
            size *= shape[i];
        }
        for (int i = 0; i < size; i++) {
            result.arr[i] = arr[i] / obj.arr[i];
        }
        return result;
    }

    // matrix multiply
    NDArray<T> dot(NDArray<T> &x) {
    if (dimension != 2 || x.dimension != 2 || shape[1] != x.shape[0]) {
        throw std::invalid_argument("Invalid shapes for matrix multiply");
    }
    int new_shape[2] = {shape[0], x.shape[1]};
    NDArray<T> result(2, new_shape);
    for (int i = 0; i < shape[0]; i++) {
        for (int j = 0; j < x.shape[1]; j++) {
            T sum = static_cast<T>(0);
            for (int k = 0; k < shape[1]; k++) {
                sum += arr[i * shape[1] + k] * x.arr[k * x.shape[1] + j];
            }
            result.arr[i * x.shape[1] + j] = sum;
        }
    }
    return result;
}

    // matrix transposition
    NDArray<T> transpose() {
    if (dimension != 2) {
        throw std::invalid_argument("Invalid shape for transpose");
    }
    int new_shape[2] = {shape[1], shape[0]};
    NDArray<T> result(2, new_shape);
    for (int i = 0; i < shape[0]; i++) {
        for (int j = 0; j < shape[1]; j++) {
            result.arr[j * shape[0] + i] = arr[i * shape[1] + j];
        }
    }
    return result;
}
    // min
    T min(int axis = -1) {
    if (axis < -1 || axis >= dimension) {
        throw std::invalid_argument("Invalid axis for reduction");
    }
    int size = 1;
    for (int i = 0; i < dimension; i++) {
        if (i != axis && shape[i] != 1) {
            throw std::invalid_argument("Invalid shape for reduction");
        }
        size *= shape[i];
    }
    T result = arr[0];
    for (int i = 0; i < size; i++) {
        if (i % shape[axis] == 0) {
            T buf = arr[i];
            for (int j = 1; j < shape[axis]; j++) {
                buf = std::min(buf, arr[i + j]);
            }
            result = i == 0 ? buf : std::min(result, buf);
        }
    }
    return result;
}

    // max
T max(int axis = -1) {
    if (axis < -1 || axis >= dimension) {
        throw std::invalid_argument("Invalid axis for reduction");
    }
    int size = 1;
    for (int i = 0; i < dimension; i++) {
        if (i != axis && shape[i] != 1) {
            throw std::invalid_argument("Invalid shape for reduction");
        }
        size *= shape[i];
    }
    T result = arr[0];
    for (int i = 0; i < size; i++) {
        if (i % shape[axis] == 0) {
            T buf = arr[i];
            for (int j = 1; j < shape[axis]; j++) {
                buf = std::max(buf, arr[i + j]);
            }
            result = i == 0 ? buf : std::max(result, buf);
        }
    }
    return result;
}
//average
T average(int axis = -1) {
    if (axis < -1 || axis >= dimension) {
        throw std::invalid_argument("Invalid axis for reduction");
    }
    int size = 1;
    for (int i = 0; i < dimension; i++) {
        if (i != axis && shape[i] != 1) {
            throw std::invalid_argument("Invalid shape for reduction");
        }
        size *= shape[i];
    }
    T result = static_cast<T>(0);
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (i % shape[axis] == 0) {
            T buf = static_cast<T>(0);
            for (int j = 0; j < shape[axis]; j++) {
                buf += arr[i + j];
            }
            buf /= static_cast<T>(shape[axis]);
            result += buf;
            count++;
        }
    }
    return result / static_cast<T>(count);
}

    ~NDArray() {
        delete[] shape;
        delete[] arr;
    }
};


#endif
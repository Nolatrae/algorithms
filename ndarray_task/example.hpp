#include <iostream>
#include "ndarray.h"

void empty(){
    std::cout << "The default constructor creates an empty array of the specified size: 5x5" << std::endl;
    int shape[2] = {5, 5};
    NDArray<int> arr(2, shape);
}

void zeros(){
    std::cout << "Creating a 2x2 array filled with fill_zeros" << std::endl;
    int shape[2] = {2, 2};
    NDArray<int> arr(2, shape);
    arr.fill_zeros();
    arr.print();
}

void ones(){
    std::cout << "Creating a 2x2 array filled with fill_ones" << std::endl;
    int shape[2] = {2, 2};
    NDArray<int> arr(2, shape);
    arr.fill_ones();
    arr.print();
}

void randomInt(){
    std::cout << "Creating a 2x2x2 array filled with random integer values" << std::endl;
    int shape[3] = {2, 2, 2};
    NDArray<int> arr(3, shape);
    arr.fill_random();
    arr.print();
}

void randomFloat(){
    std::cout << "Creating a 2x2x2 array filled with random float values" << std::endl;
    int shape[3] = {2, 2, 2};
    NDArray<float> arr(3, shape);
    arr.fill_random();
    arr.print();
}

void addition(){
    std::cout << "The element-by-element addition of 2 arrays" << std::endl;
    int shape[2] = {4, 4};
    NDArray<int> arr1(2, shape);
    NDArray<int> arr2(2, shape);
    arr1.fill_ones();
    arr2.fill_ones();
    NDArray<int> arr3 = arr1 + arr2;
    arr3.print();
}

void substruction(){
    std::cout << "The element-by-element subtraction of 2 arrays" << std::endl;
    int shape[2] = {4, 4};
    NDArray<int> arr1(2, shape);
    NDArray<int> arr2(2, shape);
    arr1.fill_ones();
    arr2.fill_ones();
    NDArray<int> arr3 = arr1 - arr2;
    arr3.print();
}

void multiply(){
    std::cout << "The element-by-element multiply of 2 arrays" << std::endl;
    int shape[2] = {4, 4};
    NDArray<int> arr1(2, shape);
    NDArray<int> arr2(2, shape);
    arr1.fill_random();
    arr2.fill_random();
    NDArray<int> arr3 = arr1 * arr2;
    arr3.print();
}

void division(){
    std::cout << "The element-by-element division of 2 arrays" << std::endl;
    int shape[2] = {4, 4};
    NDArray<int> arr1(2, shape);
    NDArray<int> arr2(2, shape);
    arr1.fill_ones();
    arr2.fill_ones();
    NDArray<int> arr3 = arr1 / arr2;
    arr3.print();
}

void matrixmultiply(){
    std::cout << "matrix multiplication of 2 arrays" << std::endl;
    int shape[2] = {2, 2};
    NDArray<int> arr1(2, shape);
    NDArray<int> arr2(2, shape);
    arr1.fill_random();
    arr2.fill_random();
    NDArray<int> arr3 = arr1.dot(arr2);
    arr3.print();
}

void transposematrix(){
    std::cout << "matrix transposition" << std::endl;
    int shape[2] = {3, 3};
    NDArray<int> arr(2, shape);
    arr.fill_random();
    arr.print();
    arr.transpose();
    arr.print();
}

void min(){
    std::cout << "the minimal value of array" << std::endl;
    int shape[2] = {3, 3};
    NDArray<int> arr(2, shape);
    arr.fill_random();
    int minimum = arr.min();
    std::cout << minimum;
    
}

void max(){
    std::cout << "the maximum value of array" << std::endl;
    int shape[2] = {3, 3};
    NDArray<int> arr(2, shape);
    arr.fill_random();
    int maximum = arr.max();
    std::cout << maximum;
}

void average(){
    std::cout << "the average value of array" << std::endl;
    int shape[2] = {3, 3};
    NDArray<int> arr(2, shape);
    arr.fill_random();
    float average = arr.average();
    std::cout << average;
}
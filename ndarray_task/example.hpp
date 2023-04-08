#include <iostream>
#include "NDArray.h"

void empty()
{
  NDArray<int> arr({5, 5});
  std::cout << arr << std::endl;
}

void zeros()
{
  auto arr = NDArray<int>::zeros({2, 2});
  std::cout << arr << std::endl;
}

void ones()
{
  auto arr = NDArray<int>::ones({2, 2});
  std::cout << arr << std::endl;
}

void randomInt()
{
  auto arr = NDArray<int>::random({2, 2, 2});
  std::cout << arr << std::endl;
}

void randomFloat()
{
  auto arr = NDArray<float>::random({2, 2, 2});
  std::cout << arr << std::endl;
}

void addition()
{
  auto arr1 = NDArray<int>::random({3, 3});
  auto arr2 = NDArray<int>::ones({3, 3});
  auto arr3 = arr1 + arr2;
  std::cout << "arr1 = " << arr1 << std::endl;
  std::cout << "arr2 = " << arr2 << std::endl;
  std::cout << "result is " << arr3 << std::endl;
}

void substruction()
{
  auto arr1 = NDArray<int>::random({3, 3});
  auto arr2 = NDArray<int>::ones({3, 3});
  auto arr3 = arr1 - arr2;
  std::cout << "arr1 = " << arr1 << std::endl;
  std::cout << "arr2 = " << arr2 << std::endl;
  std::cout << "result is " << arr3 << std::endl;
}

void multiply()
{
  auto arr1 = NDArray<int>::random({2, 2});
  auto arr2 = NDArray<int>::random({2, 2});
  auto arr3 = arr1 * arr2;
  std::cout << "arr1 = " << arr1 << std::endl;
  std::cout << "arr2 = " << arr2 << std::endl;
  std::cout << "result is " << arr3 << std::endl;
}

void division()
{
  auto arr1 = NDArray<int>::random({2, 2});
  auto arr2 = NDArray<int>::random({2, 2});
  auto arr3 = arr1 / arr2;
  std::cout << "arr1 = " << arr1 << std::endl;
  std::cout << "arr2 = " << arr2 << std::endl;
  std::cout << "result is " << arr3 << std::endl;
}

void matrixmultiply()
{
  auto arr1 = NDArray<int>::random({2, 2});
  auto arr2 = NDArray<int>::random({2, 2});
  auto arr3 = arr1.matmul(arr2);
  std::cout << "arr1 = " << arr1 << std::endl;
  std::cout << "arr2 = " << arr2 << std::endl;
  std::cout << "result is " << arr3 << std::endl;
}

void transposematrix()
{
  auto arr1 = NDArray<int>::random({4, 4});
  auto arr2 = arr1.transpose();
  std::cout << "arr1 = " << arr1 << std::endl;
  std::cout << "arr2 = " << arr2 << std::endl;
}

template <typename T>
void print_vec(const std::vector<T> &vec)
{
  for (size_t i = 0; i < vec.size(); i++)
  {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
}

void min()
{
  auto arr = NDArray<int>::random({4, 4});
  auto minimum = arr.min();
  std::cout << arr << std::endl
            << "Minimum value of array: ";
  print_vec(minimum);
  std::cout << std::endl;
}

void max()
{
  auto arr = NDArray<int>::random({4, 4});
  auto maximum = arr.max(0);
  std::cout << arr << std::endl
            << "Maximum value of each column: ";
  print_vec(maximum);
  std::cout << std::endl;
}

void average()
{
  auto arr = NDArray<int>::random({4, 4});
  auto mean = arr.mean(1);
  std::cout << arr << std::endl
            << "Mean value of each row: ";
  print_vec(mean);
  std::cout << std::endl;
}
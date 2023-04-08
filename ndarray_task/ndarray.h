#ifndef NDARRAY_NDARRAY_H
#define NDARRAY_NDARRAY_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include <numeric>
#include <utility>
#include <stdexcept>

template <typename T>
class NDArray
{
private:
  std::vector<int> shape;
  int size;
  std::vector<T> data;

public:
  NDArray(std::vector<int> shape)
  {
    this->shape = shape;
    this->size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<int>());
    data = std::vector<T>(size);
  }

  static NDArray zeros(std::vector<int> shape)
  {
    NDArray arr(shape);
    return arr;
  }

  static NDArray ones(std::vector<int> shape)
  {
    NDArray arr(shape);
    if (std::is_same_v<T, float>)
    {
      std::fill(arr.data.begin(), arr.data.end(), 1);
    }
    else if (std::is_same_v<T, int>)
    {
      std::fill(arr.data.begin(), arr.data.end(), 1);
    }
    return arr;
  }

  static NDArray random(std::vector<int> shape)
  {
    NDArray arr(shape);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < arr.size; i++)
    {
      if constexpr (std::is_same_v<T, float>)
      {
        arr.data[i] = (float)std::rand() / RAND_MAX;
      }
      else if constexpr (std::is_same_v<T, int>)
      {
        arr.data[i] = std::rand();
      }
    }
    return arr;
  }

  T &operator[](std::vector<int> indices)
  {
    int idx = 0;
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
      idx += indices[i] * std::accumulate(shape.begin() + i + 1, shape.end(), 1, std::multiplies<int>());
    }
    return data[idx];
  }

  const T &operator[](std::vector<int> indices) const
  {
    int idx = 0;
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
      idx += indices[i] * std::accumulate(shape.begin() + i + 1, shape.end(), 1, std::multiplies<int>());
    }
    return data[idx];
  }

  friend std::ostream &operator<<(std::ostream &os, const NDArray<T> &arr)
  {
    std::vector<int> indices(arr.shape.size(), 0);
    for (int i = 0; i < arr.size; i++)
    {
      os << arr[indices] << " ";
      for (int j = arr.shape.size() - 1; j >= 0; j--)
      {
        indices[j]++;
        if (indices[j] < arr.shape[j])
          break;
        indices[j] = 0;
      }
      if (i % arr.shape.back() == arr.shape.back() - 1)
        os << std::endl;
    }
    return os;
  }

  NDArray<T> operator+(const NDArray<T> &other)
  {
    if (shape != other.shape)
      throw std::invalid_argument("Dimensions don't match");
    NDArray<T> res(shape);
    for (int i = 0; i < size; ++i)
    {
      res.data[i] = data[i] + other.data[i];
    }
    return res;
  }

  NDArray<T> operator-(const NDArray<T> &other)
  {
    if (shape != other.shape)
      throw std::invalid_argument("Dimensions don't match");
    NDArray<T> res(shape);
    for (int i = 0; i < size; ++i)
    {
      res.data[i] = data[i] - other.data[i];
    }
    return res;
  }

  NDArray<T> operator*(const NDArray<T> &other)
  {
    if (shape != other.shape)
      throw std::invalid_argument("Dimensions don't match");
    NDArray<T> res(shape);
    for (int i = 0; i < size; ++i)
    {
      res.data[i] = data[i] * other.data[i];
    }
    return res;
  }

  NDArray<T> operator/(const NDArray<T> &other)
  {
    if (shape != other.shape)
      throw std::invalid_argument("Dimensions don't match");
    NDArray<T> res(shape);
    for (int i = 0; i < size; ++i)
    {
      if constexpr (std::is_same_v<T, float>)
      {
        if (other.data[i] == 0)
          throw std::invalid_argument("Division by zero");
      }
      res.data[i] = data[i] / other.data[i];
    }
    return res;
  }

  NDArray<T> matmul(const NDArray<T> &other)
  {
    if (shape.size() != 2 || other.shape.size() != 2 || shape[1] != other.shape[0])
    {
      throw std::invalid_argument("Incompatible shapes for matrix multiplication");
    }

    std::vector<int> out_shape = {shape[0], other.shape[1]};
    NDArray<T> out = NDArray<T>::zeros(out_shape);

    for (int i = 0; i < out_shape[0]; i++)
    {
      for (int j = 0; j < out_shape[1]; j++)
      {
        float dot_product = 0;
        for (int k = 0; k < shape[1]; k++)
        {
          dot_product += (*this)[{i, k}] * other[{k, j}];
        }
        out[{i, j}] = dot_product;
      }
    }

    return out;
  }

  NDArray<T> transpose()
  {
    if (shape.size() != 2)
    {
      throw std::invalid_argument("Can only transpose 2-dimensional arrays");
    }

    std::vector<int> transposed_shape = {shape[1], shape[0]};

    NDArray<T> transposed_array = NDArray<T>::zeros(transposed_shape);

    for (int i = 0; i < shape[0]; i++)
    {
      for (int j = 0; j < shape[1]; j++)
      {
        transposed_array[{j, i}] = (*this)[{i, j}];
      }
    }

    return transposed_array;
  }

  std::vector<T> min(int axis = -1)
  {
    if (axis == -1)
    {
      return {find_min(data)};
    }
    else if (axis == 0)
    {
      std::vector<T> mins;
      for (int j = 0; j < shape[1]; j++)
      {
        std::vector<int> col;

        for (int i = 0; i < shape[0]; i++)
        {
          int index = i * shape[1] + j;
          col.push_back(data[index]);
        }
        mins.push_back(find_min(col));
      }
      return mins;
    }
    else if (axis == 1)
    {
      std::vector<T> mins;
      for (int i = 0; i < shape[0]; i++)
      {
        int row_start = i * shape[1];
        std::vector<int> row(data.begin() + row_start, data.begin() + row_start + shape[1]);
        mins.push_back(find_min(row));
      }
      return mins;
    }
    throw std::invalid_argument("Can only axis 0, 1");
  }

  std::vector<T> max(int axis = -1)
  {
    if (axis == -1)
    {
      return {find_max(data)};
    }
    else if (axis == 0)
    {
      std::vector<T> maxs;
      for (int j = 0; j < shape[1]; j++)
      {
        std::vector<int> col;

        for (int i = 0; i < shape[0]; i++)
        {
          int index = i * shape[1] + j;
          col.push_back(data[index]);
        }
        maxs.push_back(find_max(col));
      }
      return maxs;
    }
    else if (axis == 1)
    {
      std::vector<T> maxs;
      for (int i = 0; i < shape[0]; i++)
      {
        int row_start = i * shape[1];
        std::vector<int> row(data.begin() + row_start, data.begin() + row_start + shape[1]);
        maxs.push_back(find_max(row));
      }
      return maxs;
    }
    throw std::invalid_argument("Can only axis 0, 1");
  }

  std::vector<float> mean(int axis = -1)
  {
    if (axis == -1)
    {
      return {find_mean(data)};
    }
    else if (axis == 0)
    {
      std::vector<float> means;
      for (int j = 0; j < shape[1]; j++)
      {
        std::vector<int> col;

        for (int i = 0; i < shape[0]; i++)
        {
          int index = i * shape[1] + j;
          col.push_back(data[index]);
        }
        means.push_back(find_mean(col));
      }
      return means;
    }
    else if (axis == 1)
    {
      std::vector<float> means;
      for (int i = 0; i < shape[0]; i++)
      {
        int row_start = i * shape[1];
        std::vector<int> row(data.begin() + row_start, data.begin() + row_start + shape[1]);
        means.push_back(find_mean(row));
      }
      return means;
    }
    throw std::invalid_argument("Can only axis 0, 1");
  }

  T find_min(std::vector<T> vec)
  {
    T min_val = vec[0];
    for (int i = 1; i < static_cast<int>(vec.size()); i++)
    {
      if (vec[i] < min_val)
      {
        min_val = vec[i];
      }
    }
    return min_val;
  }

  T find_max(std::vector<T> vec)
  {
    T max_val = vec[0];
    for (int i = 1; i < static_cast<int>(vec.size()); i++)
    {
      if (vec[i] > max_val)
      {
        max_val = vec[i];
      }
    }
    return max_val;
  }

  float find_mean(std::vector<T> vec)
  {
    float sum = 0;
    for (int i = 0; i < static_cast<int>(vec.size()); i++)
    {
      sum += vec[i];
    }
    return sum / vec.size();
  }
};

#endif
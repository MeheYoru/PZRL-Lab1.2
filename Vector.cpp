#include <stdio.h>
#include "Vector.h"

Vector::Vector(const ValueType* rawArray, const size_t size, float coef = 2.0f) 
{
  double* array {new(double[size])};

  for (size_t i = 0; i < size; i++)
  {
    array[i] = rawArray[i];
  }
  _data = array;
  _capacity = size;
  _size = size;
}

void Vector::checkFit() {
  if(_size == _capacity) {
      _capacity *= _multiplicativeCoef;
      double* newArray {new(double[_size*_multiplicativeCoef])};
      for (size_t i = 0; i < _size; i++)
      {
        newArray[i] = _data[i];
      }
      delete[] _data;
      _data = newArray;
    }
}

void Vector::pushBack(const ValueType& value) {
  this->checkFit();
  _data[_size] = value;
  _size++;
}

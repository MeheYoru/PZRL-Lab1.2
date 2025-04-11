#include <stdio.h>
#include "Vector.h"
#include <algorithm>
#include <stdexcept>

Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
        : _data(new ValueType[size]), _size(size), _capacity(size), _multiplicativeCoef(coef) {
        std::copy(rawArray, rawArray + size, _data);
    }


Vector::Vector(const Vector& other): _data(new ValueType[other._size]), _size(other._size), _capacity(other._size), _multiplicativeCoef(other._multiplicativeCoef) {
        std::copy(other._data, other._data + _size, _data);
    }

Vector& Vector::operator=(const Vector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._size;
            _multiplicativeCoef = other._multiplicativeCoef;
            _data = new ValueType[_capacity];
            std::copy(other._data, other._data + _size, _data);
        }
        return *this;
    }
Vector::Vector(Vector&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity),
          _multiplicativeCoef(other._multiplicativeCoef) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

Vector& Vector::operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            _multiplicativeCoef = other._multiplicativeCoef;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }
Vector::~Vector() {
        delete[] _data;
    }
void Vector::pushBack(const ValueType& value) {

        if (_size == _capacity) {
            reserve((_capacity == 0?_multiplicativeCoef:static_cast<size_t>(_capacity * _multiplicativeCoef)));
        }
        _data[_size++] = value;
    }

void Vector::pushFront(const ValueType& value) {
        insert(value, 0);
}

void Vector::insert(const ValueType& value, size_t pos) {
        if (pos > _size) pos = _size;
        if (_size == _capacity) {
            reserve((_capacity == 0?_multiplicativeCoef:static_cast<size_t>(_capacity * _multiplicativeCoef)));
        }
        for (size_t i = _size; i > pos; --i) {
            _data[i] = _data[i - 1];
        }
        _data[pos] = value;
        ++_size;
    }


void Vector::insert(const ValueType* values, size_t size, size_t pos) {
        if (pos > _size) pos = _size;
        const size_t newSize = _size + size;
        if (newSize > _capacity) {
            size_t newCapacity = _capacity;
            while (newCapacity < newSize) {
                newCapacity = newCapacity == 0 ? 1 : static_cast<size_t>(newCapacity * _multiplicativeCoef);
            }
            reserve(newCapacity);
        }
        for (size_t i = _size; i > pos; --i) {
            _data[i + size - 1] = _data[i - 1];
        }
        std::copy(values, values + size, _data + pos);
        _size = newSize;
    }

    void Vector::insert(const Vector& vector, size_t pos) {
        insert(vector._data, vector._size, pos);
    }

    void Vector::popBack() {
        if(_size == 0){ 
            throw std::out_of_range("Error");
        }
        --_size;
        
    }

    void Vector::erase(size_t pos, size_t count) {
        if (pos >= _size) return;
        const size_t endPos = std::min(pos + count, _size);
        const size_t shift = endPos - pos;
        for (size_t i = endPos; i < _size; ++i) {
            _data[i - shift] = _data[i];
        }
        _size -= shift;
    }

    void Vector::popFront() {
        if(_size == 0){ 
            throw std::out_of_range("Error");
        }
        erase(0, 1);
    }
    
    void Vector::eraseBetween(size_t beginPos, size_t endPos) {
        if (beginPos >= endPos || beginPos >= _size) return;
        endPos = std::min(endPos, _size);
        erase(beginPos, endPos - beginPos);
    }
    size_t Vector::size() const { return _size; }
    size_t Vector::capacity() const { return _capacity; }
    double Vector::loadFactor() const { return _capacity == 0 ? 0.0 : static_cast<double>(_size) / _capacity; }
    
    ValueType& Vector::operator[](size_t idx) { return _data[idx]; }
    const ValueType& Vector::operator[](size_t idx) const { return _data[idx]; }
    
    long long Vector::find(const ValueType& value) const {
        for (size_t i = 0; i < _size; ++i) {
            if (_data[i] == value) return i;
        }
        return -1;
    }

    void Vector::reserve(size_t capacity) {
        if (capacity > _capacity) {
            ValueType* newData = new ValueType[capacity];
            std::copy(_data, _data + _size, newData);
            delete[] _data;
            _data = newData;
            _capacity = capacity;
        }
    }

    void Vector::shrinkToFit() {
        if (_capacity > _size) {
            ValueType* newData = (_size == 0?nullptr:new ValueType[_size]);
            std::copy(_data, _data + _size, newData);
            delete[] _data;
            _data = newData;
            _capacity = _size;
        }
    }
    Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}
    ValueType& Vector::Iterator::operator*() { return *_ptr; }
    const ValueType& Vector::Iterator::operator*() const { return *_ptr; }
    ValueType* Vector::Iterator::operator->() { return _ptr; }
    const ValueType* Vector::Iterator::operator->() const { return _ptr; }
    Vector::Iterator Vector::Iterator::operator++() { ++_ptr; return *this; }
    Vector::Iterator Vector::Iterator::operator++(int) { Iterator tmp = *this; ++_ptr; return tmp; }
    bool Vector::Iterator::operator==(const Iterator& other) const { return _ptr == other._ptr; }
    bool Vector::Iterator::operator!=(const Iterator& other) const { return _ptr != other._ptr; }



    Vector::Iterator Vector::begin() { return Iterator(_data); }
    Vector::Iterator Vector::end() { return Iterator(_data + _size); }
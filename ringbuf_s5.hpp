#ifndef RINGBUF_HPP
#define RINGBUF_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class RingBuffer {
private: // taken from the w3schools course, it is considered a good practice to define public and private methods
    T* _buf;
    size_t _size;
    T* _pTail;
    T* _pHead;
    bool _empty;

public: 
    RingBuffer(size_t sz) : _size(sz), _empty(true) {
        _buf = new T[_size];
        _pHead = _pTail = _buf;
    }

    ~RingBuffer() {
        delete [] _buf;
    }

    size_t getSize() const { return _size; }

    size_t getCount() const {
        if (_empty) {
            return 0;
        } else if (_pTail == _pHead) {
            return _size; // the buffer is full
        } else if (_pTail > _pHead) {
            return _pTail - _pHead;
        } else {
            return (_size - (_pHead - _pTail));
        }
    }

    size_t getFree() const {
        return _size - getCount();
    }

    bool isEmpty() const { return _empty; }

    bool isFull() const { return (!_empty && _pHead == _pTail); }

    void push(const T& value) {
        if (isFull()) {
            throw std::out_of_range("Out of range error");
        }
        *_pTail = value;
        _empty = false;

        if (_pTail == _buf + _size - 1) {
            _pTail = _buf;
        } else {
            ++_pTail;
        }
    }

    T& front() {
        return *_pHead;
    }

    const T& front() const {
        return *_pHead;
    }

    T& back() {
        return *(_pTail == _buf ? _buf + _size - 1 : _pTail - 1);
    }

    const T& back() const {
        return *(_pTail == _buf ? _buf + _size - 1 : _pTail - 1);
    }

    // added at stage 5
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Out of range error");
        }

        if (_pHead == _buf + _size - 1) {
            _pHead = _buf;
        } else {
            ++_pHead;
        }

        if (_pHead == _pTail) {
            _empty = true;
        }
    }
};

#endif // RINGBUF_HPP

#ifndef RINGBUF_HPP
#define RINGBUF_HPP

#include <cstddef>

template<typename T>
class RingBuffer {
    T* _buf;
    size_t _size;
    T* _pTail;
    T* _pHead; 
    bool _empty;

    RingBuffer(size_t sz) : _size(sz), _empty(true) {
        _buf = new T[_size];
        _pHead = _pTail = _buf;
    }

    // Destructor
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

    // what's added on stage 3
    void push(const T& value) {
        if (isFull()) {
            throw std::out_of_range("Out of range error");
        }
        *_pTail = value;
        _empty = false; // flag is changed, reflecting the addition of an element

        if (_pTail == _buf + _size - 1) {
            _pTail = _buf;
        } else {
            ++_pTail;
        }
    }
};

#endif // RINGBUF_HPP

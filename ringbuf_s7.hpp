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

    RingBuffer(const RingBuffer& other) : _size(other._size), _empty(other._empty) {
        _buf = new T[_size];
        std::copy(other._buf, other._buf + _size, _buf);
        
        size_t headOffset = other._pHead - other._buf;
        size_t tailOffset = other._pTail - other._buf;
        _pHead = _buf + headOffset;
        _pTail = _buf + tailOffset;
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

    // added at stage 7
    static void swap(RingBuffer& lhv, RingBuffer& rhv) {
        using std::swap;
        swap(lhv._buf, rhv._buf);
        swap(lhv._size, rhv._size);
        swap(lhv._pTail, rhv._pTail);
        swap(lhv._pHead, rhv._pHead);
        swap(lhv._empty, rhv._empty);
        }
    
    RingBuffer& operator=(const RingBuffer& rhv) {
        RingBuffer temp(rhv);
        swap(*this, temp);
        return *this;
    }

};

#endif // RINGBUF_HPP

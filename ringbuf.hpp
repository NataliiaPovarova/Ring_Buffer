#ifndef RINGBUF_HPP
#define RINGBUF_HPP


template<typename T>
class RingBuffer {

    T* _buf;
    size_t _size;
    T* _pTail;
    T* _pHead;
    bool _empty;
    RingBuffer(size_t sz) : _size(sz), _empty(true)
    {
        _buf = new T[_size];
        _pHead = _pTail = _buf;
    }
    ~RingBuffer()
    {
        delete [] _buf;
    }


};


#endif // RINGBUF_HPP
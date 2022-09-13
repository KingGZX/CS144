#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity): _que{}, _capacity(capacity), _maximumcapacity(capacity), _writtensize(0), _readsize(0), _error(false), _end(false){}

size_t ByteStream::write(const string &data) {
    size_t _writesize = min(_capacity, data.length());
    string _writedata = data.substr(0, _writesize);
    for(size_t i = 0 ; i < _writesize ; i ++){
        _que.push_back(_writedata[i]);
    }
    _capacity -= _writesize;
    _writtensize += _writesize;
    return _writesize;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t _popsize = min(len, _que.size());
    string _readdata(_que.begin(), _que.begin() + _popsize);
    return _readdata;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t _popsize = min(len, _que.size());
    for(size_t i = 0 ; i < _popsize ; i ++){
        _que.pop_front();
    }
    _capacity += _popsize;
    _readsize += _popsize;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string _readdata = peek_output(len);
    pop_output(len);
    return _readdata;
}

void ByteStream::end_input() {_end = true;}

bool ByteStream::input_ended() const { return _end; }

size_t ByteStream::buffer_size() const { return _que.size(); }

bool ByteStream::buffer_empty() const { return _capacity == _maximumcapacity; }

bool ByteStream::eof() const { return _end && _readsize == _writtensize; }

size_t ByteStream::bytes_written() const { return _writtensize; }

size_t ByteStream::bytes_read() const { return _readsize; }

size_t ByteStream::remaining_capacity() const { return _capacity; }

#ifndef CHRUNK_H
#define CHRUNK_H

#include <cstdlib>

namespace MemoryManage_Arrays{

template<class T, size_t size>
class Chrunk
{
    Chrunk *nextChrunk;
    Chrunk *prevChrunk;

    T items[size];
public:
    Chrunk(Chrunk *prev, Chrunk *next);
    ~Chrunk();

    T &operator [](size_t index);

    Chrunk *next(){
        return this->nextChrunk;
    }

    void next(Chrunk * item){
        this->nextChrunk = item;
    }

    Chrunk *prev(){
        return this->prevChrunk;
    }

    void prev(Chrunk * item){
        this->prevChrunk = item;
    }
};

}

#include "chrunk.cpp"

#endif // CHRUNK_H

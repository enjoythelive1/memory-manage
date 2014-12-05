#ifndef CHRUNK_CPP
#define CHRUNK_CPP

#include "chrunk.h"

template<class T, size_t size>
Chrunk<T, size>::Chrunk(Chrunk * prev = 0, Chrunk * next = 0):
    prevChrunk(prev), nextChrunk(next)
{
}


inline T &Chrunk::operator [](size_t index)
{
    return this->items[index];
}

#endif

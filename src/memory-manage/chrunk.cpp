#ifndef CHRUNK_CPP
#define CHRUNK_CPP

#include "chrunk.h"
namespace MemoryManage_Arrays{

template<class T, size_t size>
Chrunk<T, size>::Chrunk(Chrunk * prev = 0, Chrunk * next = 0):
    prevChrunk(prev), nextChrunk(next)
{
}

template<class T, size_t size>
Chrunk<T, size>::~Chrunk()
{
    //delete this->items;
}

template<class T, size_t size>
inline T &Chrunk<T, size>::operator [](size_t index)
{
    return this->items[index];
}

}
#endif

#ifndef DINAMYCARRAY_H
#define DINAMYCARRAY_H

#include <cstdlib>
#include "chrunk.h"

#define OUT_OF_INDEX_ERROR = 99999

template<class T, int chrunkSize = 100>
class DinamycArray
{
    size_t size = 0;
    size_t currentMax = 0;
    Chrunk<T, chrunkSize> *items = 0;

public:
    DinamycArray(size_t size);

    DinamycArray(DinamycArray &other); //copy
    DinamycArray operator = (DinamycArray &other); //copy

#if __cplusplus == 201103L
    DinamycArray(DinamycArray &&other); //move
    DinamycArray operator = (DinamycArray &&other); //move
#endif

    ~DinamycArray();

    T& operator[](size_t index);

    T get(size_t index);
    void set(size_t index, T value);

    void add(size_t index);
    void removeAt(size_t index);
    void insertAt(size_t index, T item);

    size_t length();
};

#include "dinamycarray.h"

#endif // DINAMYCARRAY_H

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstdlib>
#include "chrunk.h"

namespace MemoryManage_Arrays{
#define OUT_OF_INDEX_ERROR 99999

template<class T>
signed char defaultComparer(T &item1, T &item2);

template<class T, int chrunkSize = 100>
class DynamicArray
{
    size_t size;
    size_t csize;
    size_t maxindex;
    Chrunk<T, chrunkSize> *items;

    void setToSize(size_t newSize);

public:
    DynamicArray(size_t size = chrunkSize);

    DynamicArray(DynamicArray &other); //copy
    DynamicArray  operator = (DynamicArray &other); //copy

#if __cplusplus == 201103L
    DynamicArray(DynamicArray &&other); //move
    DynamicArray  operator = (DynamicArray &&other); //move
#endif

    ~DynamicArray();

    T&  operator[](size_t index);

    T  get(size_t index) const;
    void  set(size_t index, T &value);

    void  add(T item);
    void  removeAt(size_t index);
    void  insertAt(size_t index, T &item);

    void  clear();
    void  shrink();

    bool  equal(DynamicArray &other, signed char (*comp)(T &item1, T &item2) = 0);
    bool  equal(T *other, size_t length, signed char (*comp)(T &item1, T &item2) = 0);

    bool  operator == (DynamicArray &other);

    size_t  length() const;

    friend void orderedInsert(DynamicArray &list, T &item, signed char (*comparer)(T &item1, T &item2) = 0);

    friend int orderedIndexOf(DynamicArray &list, T &item, signed char (*comparer)(T &item1, T &item2) = 0);

    friend void orderedRemove(DynamicArray &list, T &item, signed char (*comparer)(T &item1, T &item2) = 0);

    friend void sort(DynamicArray &list, signed char (*comparer)(T &item1, T &item2) = 0);
};

template<class T, int chrunkSize>
void  orderedInsert(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2) = 0);

template<class T, int chrunkSize>
size_t  orderedIndexOf(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2) = 0);

template<class T, int chrunkSize>
void  orderedRemove(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2) = 0);

// must be used because a Dinamyc list
template<class T, int chrunkSize>
void  sort(DynamicArray<T, chrunkSize> list, signed char (*comparer)(T &item1, T &item2) = 0);

}
#include "DynamicArray.cpp"

#endif // DYNAMICARRAY_H

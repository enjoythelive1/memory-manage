#ifndef DINAMYCARRAY_H
#define DINAMYCARRAY_H

#include <cstdlib>
#include "chrunk.h"

namespace MemoryManage_Arrays{
#define OUT_OF_INDEX_ERROR 99999

template<class T, int chrunkSize = 100>
class DinamycArray
{
    size_t size;
    size_t csize;
    Chrunk<T, chrunkSize> *items;

    void setToSize(size_t newSize);

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

    T get(size_t index) const;
    void set(size_t index, T value);

    void add(T item);
    void removeAt(size_t index);
    void insertAt(size_t index, T item);

    void clear();
    void shrink();

    size_t length() const;

    friend void orderedInsert(DinamycArray list, T item, signed char (*comparer)(T &item1, T &item2));

    friend size_t orderedIndexOf(DinamycArray list, T item, signed char (*comparer)(T &item1, T &item2));

    friend void orderedRemove(DinamycArray list, T item, signed char (*comparer)(T &item1, T &item2));

    friend void sort(DinamycArray list, signed char (*comparer)(T &item1, T &item2));
};

template<class T, int chrunkSize>
void orderedInsert(DinamycArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2));

template<class T, int chrunkSize>
size_t orderedIndexOf(DinamycArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2));

template<class T, int chrunkSize>
void orderedRemove(DinamycArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2));

template<class T, int chrunkSize>
void sort(DinamycArray<T, chrunkSize> list, signed char (*comparer)(T &item1, T &item2));

}
#include "dinamycarray.h"

#endif // DINAMYCARRAY_H

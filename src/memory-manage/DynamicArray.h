#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#ifndef DLL_EXPORT
#define DLL_EXPORT
#endif // DLL_EXPORT

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
    Chrunk<T, chrunkSize> *items;

    void setToSize(size_t newSize);

public:
    DynamicArray(size_t size);

    DynamicArray(DynamicArray &other); //copy
    DynamicArray DLL_EXPORT operator = (DynamicArray &other); //copy

#if __cplusplus == 201103L
    DynamicArray(DynamicArray &&other); //move
    DynamicArray DLL_EXPORT operator = (DynamicArray &&other); //move
#endif

    ~DynamicArray();

    T& DLL_EXPORT operator[](size_t index);

    T DLL_EXPORT get(size_t index) const;
    void DLL_EXPORT set(size_t index, T &value);

    void DLL_EXPORT add(T item);
    void DLL_EXPORT removeAt(size_t index);
    void DLL_EXPORT insertAt(size_t index, T &item);

    void DLL_EXPORT clear();
    void DLL_EXPORT shrink();

    bool DLL_EXPORT equal(DynamicArray &other, signed char (*comp)(T &item1, T &item2));
    bool DLL_EXPORT equal(T *other, size_t length, signed char (*comp)(T &item1, T &item2));

    bool DLL_EXPORT operator == (DynamicArray &other) {
        return equal(other);
    }

    size_t DLL_EXPORT length() const;

    friend void orderedInsert(DynamicArray &list, T &item, signed char (*comparer)(T &item1, T &item2));

    friend int orderedIndexOf(DynamicArray &list, T &item, signed char (*comparer)(T &item1, T &item2));

    friend void orderedRemove(DynamicArray &list, T &item, signed char (*comparer)(T &item1, T &item2));

    friend void sort(DynamicArray &list, signed char (*comparer)(T &item1, T &item2));
};

template<class T, int chrunkSize>
void DLL_EXPORT orderedInsert(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2));

template<class T, int chrunkSize>
size_t DLL_EXPORT orderedIndexOf(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2));

template<class T, int chrunkSize>
void DLL_EXPORT orderedRemove(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2));

// must be used because a Dinamyc list
template<class T, int chrunkSize>
void DLL_EXPORT sort(DynamicArray<T, chrunkSize> list, signed char (*comparer)(T &item1, T &item2));

}
#include "DynamicArray.h"

#endif // DYNAMICARRAY_H

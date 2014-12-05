#ifndef DYNAMICARRAY_CPP
#define DYNAMICARRAY_CPP

#include "DynamicArray.h"
#include "chrunk.h"

namespace MemoryManage_Arrays
{

template<class T, int chrunkSize>
DynamicArray<T,chrunkSize>::DynamicArray(size_t size = chrunkSize):items(0)
{
    setToSize(size);
}

// copy
template<class T, int chrunkSize>
DynamicArray<T,chrunkSize>::DynamicArray(DynamicArray<T,chrunkSize> &other):items(0)
{
    setToSize(other.length());

    for(size_t i = 0; i < other.length(); i++)
        set(i, other.get(i));
}

#if __cplusplus == 201103L
// move
template<class T, int chrunkSize>
DynamicArray<T,chrunkSize>::DynamicArray(DynamicArray<T,chrunkSize> &&other):items(0)
{
    items = other.items;
    setToSize(other.length());
    other.items = 0;
}

// move
template<class T, int chrunkSize>
DynamicArray<T,chrunkSize> DynamicArray<T,chrunkSize>::operator =(DynamicArray<T,chrunkSize> &&other)
{
    clear();

    items = other.items;
    setToSize(other.length());
    other.items = 0;
}

#endif

template<class T, int chrunkSize>
DynamicArray<T,chrunkSize>::~DynamicArray()
{
    clear();
}

// copy
template<class T, int chrunkSize>
DynamicArray<T,chrunkSize> DynamicArray<T,chrunkSize>::operator =(DynamicArray<T,chrunkSize> &other)
{
    clear();

    setToSize(other.length());

    for(size_t i = 0; i < other.length(); i++)
        set(i, other.get(i));
}

template<class T, int chrunkSize>
T &DynamicArray<T,chrunkSize>::operator [](size_t index)
{
    if(index >= size)
        throw OUT_OF_INDEX_ERROR;

    unsigned chrunkIndex = index / chrunkSize;
    size_t chrunkItem = index % chrunkSize;

    Chrunk<T,chrunkSize> toCheck = items;

    for(unsigned i = 0; i < chrunkIndex; i++)
    {
        toCheck = toCheck.next();
    }

    return toCheck[chrunkItem];
}

template<class T, int chrunkSize>
T DynamicArray<T,chrunkSize>::get(size_t index) const
{
    return this[index];
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::set(size_t index, T value)
{
    this[index] = value;
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::add(T item)
{
    size_t newIndex = size;

    setToSize(newIndex + 1);

    set(newIndex, item);
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::removeAt(size_t index)
{
    if(index >= size)
        throw OUT_OF_INDEX_ERROR;

    if (index == size - 1)
    {
        size--;
    }
    else
    {
        set(index, get(++index));
        removeAt(index);
    }
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::insertAt(size_t index, T item)
{
    bool mustMove = index < size;

    this->setToSize(index + 1);

    T cvalue = this->get(index);

    this->set(index, item);

    if (mustMove)                   // this way the tail-recursion can be optimized by compiler
        insertAt(index+1, cvalue);
}

template<class T, int chrunkSize>
size_t DynamicArray<T,chrunkSize>::length() const
{
    return size;
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::setToSize(size_t newSize)
{
    if(newSize && size < newSize)
    {
        if(!items)
            items = new Chrunk<T,chrunkSize>();

        unsigned chrunks = newSize / chrunkSize;

        if(newSize % chrunkSize)
            chrunks++;

        size = newSize;
        csize = chrunks * chrunkSize;

        Chrunk<T, chrunkSize> *cchrnk = items;
        for(unsigned i = 0; i < chrunks - 1; i++)
        {
            if(!cchrnk->next())
            {
                cchrnk.next(new Chrunk<T, chrunkSize>(cchrnk));
            }

            cchrnk = cchrnk->next();
        }
    }
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::clear()
{

    Chrunk<T,chrunkSize> *next = 0;

    while(items && next = items.next())
    {
        delete items;
        items = next;
    }

    size = 0;
    csize = 0;
}

template<class T, int chrunkSize>
void DynamicArray<T,chrunkSize>::shrink()
{

    unsigned deleteFrom = size / chrunkSize - 1;
    if (size % chrunkSize)
    {
        deleteFrom++;
    }

    Chrunk<T, chrunkSize> *toDelete = items;
    for (unsigned i = 0; i < deleteFrom && toDelete; i++)
        toDelete = toDelete.next();

    Chrunk<T,chrunkSize> *next = 0;
    while(toDelete && next = toDelete.next())
    {
        delete toDelete;
        toDelete = next;
    }

    csize = (deleteFrom + 1) * chrunkSize;
}

template<class T, int chrunkSize>
void orderedInsert(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2)){

}

template<class T, int chrunkSize>
size_t orderedIndexOf(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2)){
    return 0;
}

template<class T, int chrunkSize>
void orderedRemove(DynamicArray<T, chrunkSize> list, T item, signed char (*comparer)(T &item1, T &item2)){

}

template<class T, int chrunkSize>
void sort(DynamicArray<T, chrunkSize> list, signed char (*comparer)(T &item1, T &item2)){

}

}
#endif // DYNAMICARRAY_CPP

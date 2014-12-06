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
DynamicArray<T,chrunkSize> DLL_EXPORT DynamicArray<T,chrunkSize>::operator =(DynamicArray<T,chrunkSize> &&other)
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
DynamicArray<T,chrunkSize> DLL_EXPORT DynamicArray<T,chrunkSize>::operator =(DynamicArray<T,chrunkSize> &other)
{
    clear();

    setToSize(other.length());

    for(size_t i = 0; i < other.length(); i++)
        set(i, other.get(i));
}

template<class T, int chrunkSize>
T DLL_EXPORT &DynamicArray<T,chrunkSize>::operator [](size_t index)
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
T DLL_EXPORT DynamicArray<T,chrunkSize>::get(size_t index) const
{
    return this[index];
}

template<class T, int chrunkSize>
void DLL_EXPORT DynamicArray<T,chrunkSize>::set(size_t index, T &value)
{
    this[index] = value;
}

template<class T, int chrunkSize>
void DLL_EXPORT DynamicArray<T,chrunkSize>::add(T item)
{
    size_t newIndex = size;

    setToSize(newIndex + 1);

    set(newIndex, item);
}

template<class T, int chrunkSize>
void DLL_EXPORT DynamicArray<T,chrunkSize>::removeAt(size_t index)
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
void DLL_EXPORT DynamicArray<T,chrunkSize>::insertAt(size_t index, T &item)
{
    bool mustMove = index < size;

    this->setToSize(index + 1);

    T cvalue = this->get(index);

    this->set(index, item);

    if (mustMove)                   // this way the tail-recursion can be optimized by compiler
        insertAt(index+1, cvalue);
}

template<class T, int chrunkSize>
size_t DLL_EXPORT DynamicArray<T,chrunkSize>::length() const
{
    return size;
}
template<class T, int chrunkSize>
bool DLL_EXPORT DynamicArray<T,chrunkSize>::equal(DynamicArray<T,chrunkSize> &other, signed char (*comp)(T &item1, T &item2) = 0){
    if (length() != other.length()) return false;

    if(!comp)
        comp = defaultComparer<T>;

    for(size_t i = 0; i < length(); i++){
        if (!comp(this[i], other[i]))
            return false;
    }

    return true;
}

template<class T, int chrunkSize>
bool DLL_EXPORT DynamicArray<T,chrunkSize>::equal(T *other, size_t length, signed char (*comp)(T &item1, T &item2) = 0){
    if (length > this->length()) return false;

    if(!comp)
        comp = defaultComparer<T>;

    for(size_t i = 0; i < length; i++){
        if (!comp(this[i], other[i]))
            return false;
    }

    return true;
}

template<class T, int chrunkSize>
void DLL_EXPORT DynamicArray<T,chrunkSize>::setToSize(size_t newSize)
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
void DLL_EXPORT DynamicArray<T,chrunkSize>::clear()
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
void DLL_EXPORT DynamicArray<T,chrunkSize>::shrink()
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
void DLL_EXPORT orderedInsert(DynamicArray<T, chrunkSize> &list, T &item, signed char (*comp)(T &item1, T &item2) = 0){
    if(!comp)
        comp = defaultComparer<T>;

    int start = 0, end = list.lenght(), half;

    signed char comparison;

    while(end > start){
        half = (start + end) / 2;

        comparison = comp(list[half], item);

        if(comparison == 1)
            start = half + 1;
        else if(comparison == -1)
            end = half - 1;
        else {
            break;
        }
    }

    list.insertAt(half + 1, item);
}

template<class T, int chrunkSize>
int DLL_EXPORT orderedIndexOf(DynamicArray<T, chrunkSize> &list, T &item, signed char (*comp)(T &item1, T &item2) = 0){
    if(!comp)
        comp = defaultComparer<T>;

    int start = 0, end = list.lenght(), half;

    signed char comparison;

    while(end > start){

        half = (start + end) / 2;
        comparison = comp(list[half], item);

        if(comparison == 1)
            start = half + 1;
        else if(comparison == -1)
            end = half - 1;
        else {
            return half;
        }
    }

    return -1;
}

template<class T, int chrunkSize>
void DLL_EXPORT orderedRemove(DynamicArray<T, chrunkSize> &list, T &item, signed char (*comp)(T &item1, T &item2) = 0){
    if(!comp)
        comp = defaultComparer<T>;

    int itemIndex = orderedIndexOf(list, item, comp);

    if(itemIndex == -1){
        return;
    }

    list.removeAt(itemIndex);
}

template<class T>
signed char defaultComparer(T &item1, T &item2) {
    return (item1 == item2)? 0 : (item1 > item2)? 1 : -1;
}

template<class T, int chrunkSize>
void quicksort(DynamicArray<T, chrunkSize> &list, size_t start=0, size_t end=0, signed char (*comp)(T &item1, T &item2) = 0){
    if(!comp)
        comp = defaultComparer<T>;

    if(!end)
        end = list.length() - 1;

    if (end - start < 8)
        return insertionSort(list, start, end, comp);

    size_t pivot = end;

    size_t leftEnding = start, rightEnding = end - 1;

    T valueHolder;
    signed char lr, lp, rp;
    while (leftEnding != rightEnding) {
        lr = comp(list[leftEnding], list[rightEnding]);
        lp = comp(list[leftEnding], list[pivot]);
        rp = comp(list[rightEnding], list[pivot]);

        if (lr == 1 && lp == 1) {
            valueHolder = list[leftEnding];
            list[leftEnding] = list[rightEnding];
            list[rightEnding] = valueHolder;
            leftEnding++;
            rightEnding--;
        } else {
            if (lp == -1)
                leftEnding++;

            if(rp == 1)
                rightEnding--;
        }

    }

    valueHolder = list[leftEnding];
    list[leftEnding] = list[pivot];
    list[pivot] = valueHolder;

    quicksort(list, start, leftEnding - 1, comp);
    quicksort(list, leftEnding + 1, end, comp);
}

template<class T, int chrunkSize>
void insertionSort(DynamicArray<T, chrunkSize> &list, size_t start=0, size_t end=0, signed char (*comp)(T &item1, T &item2) = 0){
    if(!comp)
        comp = defaultComparer<T>;

    if(!end)
        end = list.length() - 1;

    if(start - end <= 1){
        return;
    }

    T vholder;
    for(size_t sorted = start + 1; sorted <= end; sorted++){

        for(size_t i = sorted; i > start; i--) {
            if(comp(list[i], list[i - 1]) == -1) {
                vholder = list[i - 1];
                list[i - 1] = list[i];
                list[i] = vholder;
            } else {
                break;
            }
        }

    }

}

template<class T, int chrunkSize>
void DLL_EXPORT sort(DynamicArray<T, chrunkSize> &list, signed char (*comp)(T &item1, T &item2) = 0){
    if(!comp)
        comp = defaultComparer<T>;

    quicksort(list, 0, list.length() - 1, comp);
}

}
#endif // DYNAMICARRAY_CPP

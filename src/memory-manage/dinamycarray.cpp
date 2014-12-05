#ifndef DINAMYCARRAY_CPP
#define DINAMYCARRAY_CPP

#include "dinamycarray.h"
#include "chrunk.h"


template<class T, int chrunkSize>
DinamycArray<T,chrunkSize>::DinamycArray(size_t size = chrunkSize): size(size)
{
    int chrunks = size / chrunkSize + 1;

    Chrunk<T,chrunkSize> *elemets = this->items = new Chrunk<T,chrunkSize>();

    for(unsigned i = 0; i < chrunks - 1; i++) {
        elemets->next(new Chrunk<T,chrunkSize>(elements));
        elemets = elemets->next();
    }
}

// copy
template<class T, int chrunkSize>
DinamycArray<T,chrunkSize>::DinamycArray(DinamycArray<T,chrunkSize> &other):size(other.length())
{
    int chrunks = size / chrunkSize + 1;

    Chrunk<T,chrunkSize> *elemets = this->items = new Chrunk<T,chrunkSize>();

    for(unsigned i = 0; i < chrunks - 1; i++) {
        elemets->next(new Chrunk<T,chrunkSize>(elements));
        elemets = elemets->next();
    }
    
    for(size_t i = 0; i < other.length(); i++)
        set(i, other.get(i));
}

#if __cplusplus == 201103L
// move
template<class T, int chrunkSize>
DinamycArray<T,chrunkSize>::DinamycArray(DinamycArray<T,chrunkSize> &&other):size(other.length())
{
    items = other.items;
    other.items = 0;
}

// move
template<class T, int chrunkSize>
DinamycArray<T,chrunkSize> DinamycArray<T,chrunkSize>::operator =(DinamycArray<T,chrunkSize> &&other)
{
    Chrunk<T,chrunkSize> *next = 0;
    while(next = item.next()) {
        delete items;
        items = next;
    }

    items = other.items;
    other.items = 0;
}

#endif

template<class T, int chrunkSize>
DinamycArray<T,chrunkSize>::~DinamycArray()
{
    Chrunk<T,chrunkSize> *next = 0;
    while(next = item.next()) {
        delete items;
        items = next;
    }
}

// copy
template<class T, int chrunkSize>
DinamycArray<T,chrunkSize> DinamycArray<T,chrunkSize>::operator =(DinamycArray<T,chrunkSize> &other)
{
    Chrunk<T,chrunkSize> *next = 0;
    while(next = item.next()) {
        delete items;
        items = next;
    }

    size = other.length();

    int chrunks = size / chrunkSize + 1;

    Chrunk<T,chrunkSize> *elemets = this->items = new Chrunk<T,chrunkSize>();

    for(unsigned i = 0; i < chrunks - 1; i++) {
        elemets->next(new Chrunk<T,chrunkSize>(elements));
        elemets = elemets->next();
    }

    for(size_t i = 0; i < other.length(); i++)
        set(i, other.get(i));
}

template<class T, int chrunkSize>
T &DinamycArray<T,chrunkSize>::operator [](size_t index)
{
    if(index >= size)
        throw OUT_OF_INDEX_ERROR;

    unsigned chrunkIndex = index / chrunkSize;
    size_t chrunkItem = index % chrunkSize;

    Chrunk<T,chrunkSize> toCheck = items;

    for(unsigned i = 0; i < chrunkIndex; i++){
        toCheck = toCheck.next();
    }

    return toCheck[chrunkItem];
}

template<class T, int chrunkSize>
T DinamycArray<T,chrunkSize>::get(size_t index) const
{
    return this[index];
}

template<class T, int chrunkSize>
void DinamycArray<T,chrunkSize>::set(size_t index, T value)
{
    this[index] = value;
}

template<class T, int chrunkSize>
void DinamycArray<T,chrunkSize>::add(size_t index)
{
}

template<class T, int chrunkSize>
void DinamycArray<T,chrunkSize>::removeAt(size_t index)
{
}

template<class T, int chrunkSize>
void DinamycArray<T,chrunkSize>::insertAt(size_t index, T item)
{
}

template<class T, int chrunkSize>
size_t DinamycArray<T,chrunkSize>::length()
{

}


#endif // DINAMYCARRAY_CPP

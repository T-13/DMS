#pragma once

#include "../DmsObject.h"

template<class T>
class DmsDuplicator {

public:
    DmsDuplicator();
    DmsDuplicator(const DmsDuplicator<T> &duplicator);
    DmsDuplicator(T *original_, int amount_);

    int get_amount() { return amount; };
    T *get_clone() { return new T(*original); };

protected:
    T *original;
    int amount;
};

template<class T>
DmsDuplicator<T>::DmsDuplicator() {
}

template<class T>
DmsDuplicator<T>::DmsDuplicator(const DmsDuplicator<T> &duplicator)
        : original(duplicator.original), amount(duplicator.amount) {
}

template<class T>
DmsDuplicator<T>::DmsDuplicator(T *original_, int amount_)
        : original(original_), amount(amount_) {
}

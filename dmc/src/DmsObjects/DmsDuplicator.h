#pragma once

#include <vector>

#include "../DmsObject.h"

template<class T>
class DmsDuplicator {

public:
    DmsDuplicator();
    DmsDuplicator(const DmsDuplicator<T> &duplicator);
    DmsDuplicator(T *original_, int amount_);
    ~DmsDuplicator();

    int get_amount();
    T *get_clone();

protected:
    T *original;
    int amount;

private:
    std::vector<T*> clones;
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

template<class T>
DmsDuplicator<T>::~DmsDuplicator() {
    for (auto &clone : clones) {
        delete clone;
    }
}

template<class T>
int DmsDuplicator<T>::get_amount() {
    return amount;
}

template<class T>
T *DmsDuplicator<T>::get_clone() {
    T *clone = new T(*original);
    clones.push_back(clone); // Track creations for memory cleanup
    return clone;
}

#pragma once

#include "../DmsObject.h"

template<class T>
class DmsDuplicator {

public:
    DmsDuplicator();
    DmsDuplicator(T *original_, int amount_): original(original_), amount(amount_) {};

    int get_amount() { return amount; };
    T *get_clone() { return new T(*original); };

private:
    T *original = nullptr;
    int amount;
};

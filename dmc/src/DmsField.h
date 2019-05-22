#pragma once

#include <string>
#include <vector>

#include "DmsSerializable.h"

#include "lib/rang.hpp"

/**
 *
 *  DmsField is used to store atributes of DmsObjects
 *  Standardised and objectified field makes compilation/serialization easier
 *
 *  Parent points to the parent object of this field - In case of global variable it is a GlobalVariableHolder
 *  Name is the name of the variable/property
 *  Value is the value of the field
 *
 **/
template<class T>
class DmsField {
public:
    DmsField();
    DmsField(const DmsField<T> &dms_field);
    DmsField(std::string name_, T value_, bool is_resolved_);
    ~DmsField();

    T get_value() const;
    bool get_is_resolved() const;
    void set_value(T value_, bool is_resolved_);
    std::string get_name() const;

    void print(std::ostream &os, bool split = false) const;

protected:
    std::string name;
    T value;
    bool is_resolved;
};

template<class T>
DmsField<T>::DmsField() {
}

template<class T>
DmsField<T>::DmsField(std::string name_, T value_, bool is_resolved_)
        : name(name_), value(value_), is_resolved(is_resolved_) {
}

template<class T>
DmsField<T>::DmsField(const DmsField<T> &dms_field)
        : name(dms_field.name), value(dms_field.value), is_resolved(dms_field.is_resolved) {
}

template<class T>
DmsField<T>::~DmsField() {
}

template <class T>
T DmsField<T>::get_value() const {
    return value;
}

template<class T>
bool DmsField<T>::get_is_resolved() const {
    return is_resolved;
}
template <class T>
void DmsField<T>::set_value(T newValue, bool is_resolved_) {
    value = newValue;
    is_resolved = is_resolved_;
}

template<class T>
std::string DmsField<T>::get_name() const {
    return name;
}

template<class T>
void DmsField<T>::print(std::ostream &os, bool split) const {
    if (split) os << "-> ";
    os << name << ": " << value;
    if (split) os << std::endl;
}

// inline to avoid multiple definitions (function without arguments)
template<>
inline void DmsField<std::string>::print(std::ostream &os, bool split) const {
    if (split) os << "-> ";
    os << name << ": " << value;
    if (split) os << std::endl;
}

template<>
inline void DmsField<DmsSerializable*>::print(std::ostream &os, bool split) const {
    os << std::endl << "-> " << name << " =>";
    value->print(os, split);
    if (split) os << std::endl;
}

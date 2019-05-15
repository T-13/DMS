#pragma once

#include <string>
#include <vector>

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
class DmsObject;

template<class T>
class DmsField {
public:
    DmsField();
    DmsField(std::string name_, T value_, DmsObject *parent_);
    ~DmsField();

    T get_value() const;
    void set_value(T value_);
    std::string get_name() const;

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

protected:
    DmsObject *parent;
    std::string name;
    T value;
};

template<class T>
DmsField<T>::DmsField() {
}

template<class T>
DmsField<T>::DmsField(std::string name_, T value_, DmsObject *parent_)
        : parent(parent_), name(name_), value(value_) {
}

template<class T>
DmsField<T>::~DmsField() {
}

template <class T>
T DmsField<T>::get_value() const {
    return value;
}

template <class T>
void DmsField<T>::set_value(T newValue) {
    value = newValue;
}

template<class T>
std::string DmsField<T>::get_name() const {
    return name;
}

template<class T>
std::string DmsField<T>::serialize() {
    return name + " -> " + std::to_string(value) + "\n";
}

// inline to avoid multiple definitions (function without arguments)
template<>
inline std::string DmsField<std::string>::serialize() {
    return name + " -> " + value + "\n";
}

template<class T>
std::string DmsField<T>::compile() {
    return ""; // TODO
}

#include "DmsField.h"

template<typename T>
DmsField<T>::DmsField() {
}

template<typename T>
DmsField<T>::DmsField(const DmsField& field) {
    this->name = field.name;
    this->value = field.value;
    this->parent = field.parent;
}

template<typename T>
DmsField<T>::DmsField(std::string newName, T newValue, DmsObject* newParent) {
    this->name = newName;
    this->value = newValue;
    this->parent = newParent;
}

template<typename T>
T DmsField<T>::getValue() {
    return value;
}

template<typename T>
void DmsField<T>::setValue(T newValue) {
    value = newValue;
}

template<typename T>
std::string DmsField<T>::getName() const {
    return name;
}

template<typename T>
DmsField<T> DmsField<T>::operator=(const T& aValue) {
    setValue(aValue);
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator+(const T& aValue) {
    setValue(getValue() + aValue);
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator-(const T& aValue) {
    setValue(getValue() - aValue);
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator/(const T& aValue) {
    setValue(getValue() / aValue);
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator*(const T& aValue) {
    setValue(getValue() * aValue);
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator%(const T& aValue) {
    setValue(getValue() % aValue);
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator=(const DmsField<T>& aValue) {
    this->name = aValue.name;
    this->value = aValue.name;
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator+(const DmsField<T>& aValue) {
    this + aValue;
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator-(const DmsField<T>& aValue) {
    this - aValue;
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator/(const DmsField<T>& aValue) {
    this / aValue;
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator*(const DmsField<T>& aValue) {
    this * aValue;
    return this;
}

template<typename T>
DmsField<T> DmsField<T>::operator%(const DmsField<T>& aValue) {
    this % aValue;
    return this;
}

#include "DmsIntField.h"

DmsIntField::DmsIntField() {
}

DmsIntField::~DmsIntField() {
}

DmsIntField::DmsIntField(const DmsIntField &field)
        : DmsField(field.name, field.parent), value(field.value) {
}

DmsIntField::DmsIntField(std::string name_, int value_, DmsObject *parent_)
        : DmsField(name_, parent_), value(value_) {
}

void DmsIntField::set_value(int value_) {
    value = value_;
}

int DmsIntField::get_value() {
    return value;
}

#include "DmsFloatField.h"

DmsFloatField::DmsFloatField() {
}

DmsFloatField::~DmsFloatField() {
}

DmsFloatField::DmsFloatField(const DmsFloatField &field)
        : DmsField(field.name, field.parent), value(field.value) {
}

DmsFloatField::DmsFloatField(std::string name_, float value_, DmsObject *parent_)
        : DmsField(name_, parent_), value(value_) {
}

void DmsFloatField::set_value(float value_) {
    value = value_;
}

float DmsFloatField::get_value() {
    return value;
}

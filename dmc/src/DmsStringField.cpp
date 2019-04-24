#include "DmsStringField.h"

DmsStringField::DmsStringField() {
}

DmsStringField::~DmsStringField() {
}

DmsStringField::DmsStringField(const DmsStringField &field)
        : DmsField(field.name, field.parent), value(field.value) {
}

DmsStringField::DmsStringField(std::string name_, std::string value_, DmsObject *parent_)
        : DmsField(name_, parent_), value(value_) {
}

void DmsStringField::set_value(std::string value_) {
    value = value_;
}

std::string DmsStringField::get_value() {
    return value;
}

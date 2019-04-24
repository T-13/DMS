#include "DmsField.h"

DmsField::DmsField() {
}

DmsField::~DmsField() {
}

DmsField::DmsField(std::string name_, DmsObject *parent_)
        : parent(parent_), name(name_) {
}

std::string DmsField::get_name() const {
    return name;
}

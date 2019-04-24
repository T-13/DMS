#include "DmsField.h"

DmsField::DmsField() {
}

DmsField::~DmsField() {
}

DmsField::DmsField(std::string newName, DmsObject* newParent) {
    this->name = newName;
    this->parent = newParent;
}

std::string DmsField::getName() const {
    return name;
}

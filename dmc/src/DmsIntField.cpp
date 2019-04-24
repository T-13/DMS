#include "DmsIntField.h"


DmsIntField::DmsIntField()
{

}

DmsIntField::~DmsIntField()
{

}


DmsIntField::DmsIntField(const DmsIntField & other)
{
	this->name = other.name;
	this->value = other.value;
	this->parent = other.parent;
}

DmsIntField::DmsIntField(std::string newName, int newValue, DmsObject* newParent): DmsField(newName, newParent)
{
	this->value = newValue;
}

void DmsIntField::setValue(int newValue) {
	this->value = newValue;
}

int DmsIntField::getValue() {
	return this->value;
}

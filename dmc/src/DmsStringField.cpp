#include "DmsStringField.h"


DmsStringField::DmsStringField()
{

}

DmsStringField::~DmsStringField()
{

}


DmsStringField::DmsStringField(const DmsStringField & other)
{
	this->name = other.name;
	this->value = other.value;
	this->parent = other.parent;
}

DmsStringField::DmsStringField(std::string newName, std::string newValue, DmsObject* newParent): DmsField(newName, newParent)
{
	this->value = newValue;
}

void DmsStringField::setValue(std::string newValue) {
	this->value = newValue;
}

std::string DmsStringField::getValue() {
	return this->value;
}

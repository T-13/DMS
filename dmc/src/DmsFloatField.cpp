#include "DmsFloatField.h"


DmsFloatField::DmsFloatField()
{

}

DmsFloatField::~DmsFloatField(){

}

DmsFloatField::DmsFloatField(const DmsFloatField & other)
{
	this->name = other.name;
	this->value = other.value;
	this->parent = other.parent;
}

DmsFloatField::DmsFloatField(std::string newName, float newValue, DmsObject* newParent): DmsField(newName, newParent)
{
	this->value = newValue;
}

void DmsFloatField::setValue(float newValue) {
	this->value = newValue;
}

float DmsFloatField::getValue() {
	return this->value;
}

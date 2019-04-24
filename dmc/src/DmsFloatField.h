#pragma once
#include <string>
#include <vector>
#include "DmsField.h"

/**
 *
 *	DmsField is used to store atributes of DmsObjects
 *	Standardised and objectified field makes compilation/serialization easier
 *	
 *	Parent points to the parent object of this field - In case of global variable it is a GlobalVariableHolder
 *	Name is the name of the variable/property
 *	Value is the value of the field
 *	
 **/

class DmsFloatField: public DmsField
{
	int value;
public:
	DmsFloatField();
	DmsFloatField(const DmsFloatField & other);
	DmsFloatField(std::string newName, float newValue, DmsObject* newParent);
	~DmsFloatField();

	void setValue(float newValue);
	float getValue();

	std::string serialize() { return ""; };
	std::string compile() { return ""; };
};


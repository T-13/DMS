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

class DmsIntField: public DmsField
{
	int value;
public:
	DmsIntField();
	DmsIntField(const DmsIntField & other);
	DmsIntField(std::string newName, int newValue, DmsObject* newParent);
	~DmsIntField();

	void setValue(int newValue);
	int getValue();

	std::string serialize() { return ""; };
	std::string compile() { return ""; };
};


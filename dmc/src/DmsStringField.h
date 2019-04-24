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

class DmsStringField: public DmsField
{
	std::string value;
public:
	DmsStringField();
	DmsStringField(const DmsStringField & other);
	DmsStringField(std::string newName, std::string newValue, DmsObject* newParent);
	~DmsStringField();

	void setValue(std::string newValue);
	std::string getValue();

	std::string serialize() { return ""; };
	std::string compile() { return ""; };
};


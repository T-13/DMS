#pragma once
#include <string>
#include <vector>

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
class DmsObject;

template<typename T>
class DmsField
{
protected:
	DmsObject *parent;
	std::string name ;
	T value;
public:
	DmsField();
	DmsField(std::string newName, T newValue, DmsObject* newParent);
	DmsField(const DmsField& field);
	~DmsField();

	T getValue();
	void setValue(T newValue);
	std::string getName() const;

	DmsField<T> operator=(const T& value);
	DmsField<T> operator+(const T& value);
	DmsField<T> operator-(const T& value);
	DmsField<T> operator/(const T& value);
	DmsField<T> operator*(const T& value);
	DmsField<T> operator%(const T& value);	
	
	DmsField<T> operator=(const DmsField<T>& value);
	DmsField<T> operator+(const DmsField<T>& value);
	DmsField<T> operator-(const DmsField<T>& value);
	DmsField<T> operator/(const DmsField<T>& value);
	DmsField<T> operator*(const DmsField<T>& value);
	DmsField<T> operator%(const DmsField<T>& value);

	// TODO - Choose serialize or compile or both and choose type str/byte[]...
	std::string serialize(){ return ""; };
	std::string compile(){ return ""; };
};


#pragma once

#include <map>

#include "DmsField.h"
#include "DmsIntField.h"
#include "DmsFloatField.h"
#include "DmsStringField.h"

class DmsObject;

class DmsFieldScope {
public:
    DmsFieldScope();
    ~DmsFieldScope();

    void add_parent(DmsObject *parent_);

    void set_field_value(std::string name, int value);
    void set_field_value(std::string name, float value);
    void set_field_value(std::string name, std::string value);

    void get_field_value(std::string name, int *value);
    void get_field_value(std::string name, float *value);
    void get_field_value(std::string name, std::string *value);

    std::vector<std::string> get_all_field_names();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

 private:
    DmsObject* parent;

    std::map<std::string, DmsIntField> int_fields;
    std::map<std::string, DmsFloatField> float_fields;
    std::map<std::string, DmsStringField> string_fields;
};

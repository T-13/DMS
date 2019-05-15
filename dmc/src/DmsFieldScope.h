#pragma once

#include <map>

#include "DmsField.h"

class DmsObject;

class DmsFieldScope {
public:
    DmsFieldScope();
    ~DmsFieldScope();

    void set_enclosing_scope(DmsFieldScope *enclosing_scope);

    void set_field_value(std::string name, int value);
    void set_field_value(std::string name, float value);
    void set_field_value(std::string name, std::string value);
    void set_field_value(std::string name, DmsObject* object);

    template<typename T>
    T get_field_value(std::string name, bool *found); // Use with eg. get_field_value<int>

    std::vector<std::string> get_all_field_names();
    template<typename T>
    std::vector<T> get_all_field_values(); // Use with eg. get_all_field_values<int>()

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

 private:
    DmsFieldScope* enclosing_scope;

    std::map<std::string, DmsField<int>> int_fields;
    std::map<std::string, DmsField<float>> float_fields;
    std::map<std::string, DmsField<std::string>> string_fields;
    std::map<std::string, DmsField<DmsObject*>> object_fields;
};

template<>
inline int DmsFieldScope::get_field_value(std::string name, bool *found) {
    std::map<std::string, DmsField<int>>::iterator it = int_fields.find(name);
    if (it != int_fields.end()) {
        *found = true;
        return it->second.get_value();
    }
    *found = false;
    return 0;
}

template<>
inline float DmsFieldScope::get_field_value(std::string name, bool *found) {
    std::map<std::string, DmsField<float>>::iterator it = float_fields.find(name);
    if (it != float_fields.end()) {
        *found = true;
        return it->second.get_value();
    }
    *found = false;
    return enclosing_scope->get_field_value<float>(name, found);
}

template<>
inline std::string DmsFieldScope::get_field_value(std::string name, bool *found) {
    std::map<std::string, DmsField<std::string>>::iterator it = string_fields.find(name);
    if (it != string_fields.end()) {
        *found = true;
        return it->second.get_value();
    }
    *found = false;
    return "";
}

template<>
inline DmsObject* DmsFieldScope::get_field_value(std::string name, bool *found) {
    std::map<std::string, DmsField<DmsObject*>>::iterator it = object_fields.find(name);
    if (it != object_fields.end()) {
        *found = true;
        return it->second.get_value();
    }
    *found = false;
    return nullptr;
}

template<>
inline std::vector<int> DmsFieldScope::get_all_field_values() {
    std::vector<int> values;

    for (auto &field : int_fields) {
        values.push_back(field.second.get_value());
    }

    return values;
}

template<>
inline std::vector<float> DmsFieldScope::get_all_field_values() {
    std::vector<float> values;

    for (auto &field : float_fields) {
        values.push_back(field.second.get_value());
    }

    return values;
}

template<>
inline std::vector<std::string> DmsFieldScope::get_all_field_values() {
    std::vector<std::string> values;

    for (auto &field : string_fields) {
        values.push_back(field.second.get_value());
    }

    return values;
}

template<>
inline std::vector<DmsObject*> DmsFieldScope::get_all_field_values() {
    std::vector<DmsObject*> values;

    for (auto &field : object_fields) {
        values.push_back(field.second.get_value());
    }

    return values;
}

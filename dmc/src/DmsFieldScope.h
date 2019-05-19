#pragma once

#include <map>

#include "DmsField.h"
#include "DmsSerializable.h"

class DmsObject;

class DmsFieldScope {
public:
    DmsFieldScope();
    DmsFieldScope(const DmsFieldScope &original);
    ~DmsFieldScope();

    void set_enclosing_scope(DmsFieldScope *enclosing_scope);
    DmsFieldScope *get_enclosing_scope() const;

    void set_field_value(std::string name, float value, bool is_resolved);
    void set_field_value(std::string name, std::string value, bool is_resolved);
    void set_field_value(std::string name, DmsSerializable* object, bool is_resolved);

    template<typename T>
    DmsField<T> *get_field(std::string name); // Use with eg. get_field_value<int>

    std::vector<std::string> get_all_field_names();
    template<typename T>
    std::vector<DmsField<T>> get_all_fields() const; // Use with eg. get_all_fields<int>()

    std::string serialize();

 private:
    DmsFieldScope* enclosing_scope;

    std::map<std::string, DmsField<float>> float_fields;
    std::map<std::string, DmsField<std::string>> string_fields;
    std::map<std::string, DmsField<DmsSerializable*>> object_fields;
};

template<>
inline DmsField<float> *DmsFieldScope::get_field(std::string name) {
    std::map<std::string, DmsField<float>>::iterator it = float_fields.find(name);
    if (it != float_fields.end()) {
        return &it->second;
    }
    if (enclosing_scope != nullptr) {
        return enclosing_scope->get_field<float>(name);
    }
    return nullptr;
}

template<>
inline DmsField<std::string> *DmsFieldScope::get_field(std::string name) {
    std::map<std::string, DmsField<std::string>>::iterator it = string_fields.find(name);
    if (it != string_fields.end()) {
        return &it->second;
    }
    if (enclosing_scope != nullptr) {
        return get_field<std::string>(name);
    }
    return nullptr;
}

template<>
inline DmsField<DmsSerializable*> *DmsFieldScope::get_field(std::string name) {
    std::map<std::string, DmsField<DmsSerializable*>>::iterator it = object_fields.find(name);

    if (it != object_fields.end()) {
        return &it->second;
    }
    return nullptr;
}

template<>
inline std::vector<DmsField<float>> DmsFieldScope::get_all_fields() const{
    std::vector<DmsField<float>> values;

    for (auto &field : float_fields) {
        values.push_back(field.second);
    }

    return values;
}

template<>
inline std::vector<DmsField<std::string>> DmsFieldScope::get_all_fields() const{
    std::vector<DmsField<std::string>> values;

    for (auto &field : string_fields) {
        values.push_back(field.second);
    }

    return values;
}

template<>
inline std::vector<DmsField<DmsSerializable*>> DmsFieldScope::get_all_fields() const{
    std::vector<DmsField<DmsSerializable*>> values;

    for (auto &field : object_fields) {
        values.push_back(field.second);
    }

    return values;
}

#include "DmsFieldScope.h"

DmsFieldScope::DmsFieldScope()
        : parent(nullptr) {
}

DmsFieldScope::~DmsFieldScope() {
}

void DmsFieldScope::add_parent(DmsObject *parent_) {
    parent = parent_;
}

void DmsFieldScope::set_field_value(std::string name, int value) {
    std::map<std::string, DmsIntField>::iterator it = int_fields.find(name);

    if (it != int_fields.end()) {
        it->second.set_value(value);
    } else {
        int_fields[name] = DmsIntField(name, value, parent);
    }
}

void DmsFieldScope::set_field_value(std::string name, float value) {
    std::map<std::string, DmsFloatField>::iterator it = float_fields.find(name);

    if (it != float_fields.end()) {
        it->second.set_value(value);
    } else {
        float_fields[name] = DmsFloatField(name, value, parent);
    }
}

void DmsFieldScope::set_field_value(std::string name, std::string value) {
    std::map<std::string,DmsStringField>::iterator it = string_fields.find(name);

    if (it != string_fields.end()) {
        it->second.set_value(value);
    } else {
        string_fields[name] = DmsStringField(name, value, parent);
    }
}

void DmsFieldScope::get_field_value(std::string name, int *value) {
    std::map<std::string, DmsIntField>::iterator it = int_fields.find(name);

    if (it != int_fields.end()) {
        *value = it->second.get_value();
    }
}

void DmsFieldScope::get_field_value(std::string name, float *value) {
    std::map<std::string, DmsFloatField>::iterator it = float_fields.find(name);

    if (it != float_fields.end()) {
        *value = it->second.get_value();
    }
}

void DmsFieldScope::get_field_value(std::string name, std::string *value) {
    std::map<std::string, DmsStringField>::iterator it = string_fields.find(name);

    if (it != string_fields.end()) {
        *value = it->second.get_value();
    }
}

std::vector<std::string> DmsFieldScope::get_all_field_names() {
    std::vector<std::string> result;

    for (const auto a : int_fields) {
        result.push_back(a.first);
    }
    for (const auto a : float_fields) {
        result.push_back(a.first);
    }
    for (const auto a : string_fields) {
        result.push_back(a.first);
    }

    return result;
}

std::string DmsFieldScope::serialize() {
    std::string result = "";

    for (auto a : int_fields) {
        result += a.second.serialize();
    }
    for (auto a : float_fields) {
        result += a.second.serialize();
    }
    for (auto a : string_fields) {
        result += a.second.serialize();
    }

    return result;
}

std::string DmsFieldScope::compile() {
    std::string result = "";

    for (auto a : int_fields) {
        result += a.second.compile();
    }
    for (auto a : float_fields) {
        result += a.second.compile();
    }
    for (auto a : string_fields) {
        result += a.second.compile();
    }

    return result;
}

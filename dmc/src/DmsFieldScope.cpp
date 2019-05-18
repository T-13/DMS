#include "DmsFieldScope.h"

DmsFieldScope::DmsFieldScope()
        : enclosing_scope(nullptr) {
}

DmsFieldScope::~DmsFieldScope() {
}

void DmsFieldScope::set_enclosing_scope(DmsFieldScope *enclosing_scope_) {
    enclosing_scope = enclosing_scope_;
}

DmsFieldScope *DmsFieldScope::get_enclosing_scope() const {
    return enclosing_scope;
}

void DmsFieldScope::set_field_value(std::string name, float value, bool is_resolved) {
    std::map<std::string, DmsField<float>>::iterator it = float_fields.find(name);

    if (it != float_fields.end()) {
        it->second.set_value(value, is_resolved);
    } else {
        float_fields[name] = DmsField<float>(name, value, is_resolved);
    }
}

void DmsFieldScope::set_field_value(std::string name, std::string value, bool is_resolved) {
    std::map<std::string,DmsField<std::string>>::iterator it = string_fields.find(name);

    if (it != string_fields.end()) {
        it->second.set_value(value, is_resolved);
    } else {
        string_fields[name] = DmsField<std::string>(name, value, is_resolved);
    }
}

void DmsFieldScope::set_field_value(std::string name, DmsSerializable* value, bool is_resolved) {
    std::map<std::string, DmsField<DmsSerializable*>>::iterator it = object_fields.find(name);

    if (it != object_fields.end()) {
        it->second.set_value(value, is_resolved);
    } else {
        object_fields[name] = DmsField<DmsSerializable*>(name, value, is_resolved);
    }
}

std::vector<std::string> DmsFieldScope::get_all_field_names() {
    std::vector<std::string> result;

    for (const auto &field : float_fields) {
        result.push_back(field.first);
    }
    for (const auto &field : string_fields) {
        result.push_back(field.first);
    }
    for (const auto &field : object_fields) {
        result.push_back(field.first);
    }

    return result;
}

std::string DmsFieldScope::serialize() {
    std::string result = "";

    for (auto &field : float_fields) {
        result += field.second.serialize();
    }
    for (auto &field : string_fields) {
        result += field.second.serialize();
    }
    for (auto &field : object_fields) {
        result += field.second.serialize();
    }

    return result;
}

std::string DmsFieldScope::compile() {
    std::string result = "";

    for (auto &field : float_fields) {
        result += field.second.compile();
    }
    for (auto &field : string_fields) {
        result += field.second.compile();
    }
    for (auto &field : object_fields) {
        result += field.second.compile();
    }

    return result;
}

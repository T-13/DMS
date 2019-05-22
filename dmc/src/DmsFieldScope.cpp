#include "DmsFieldScope.h"

DmsFieldScope::DmsFieldScope()
        : enclosing_scope(nullptr) {
}

DmsFieldScope::DmsFieldScope(const DmsFieldScope &original)
        : enclosing_scope(original.enclosing_scope) {
    float_fields.clear();
    string_fields.clear();
    object_fields.clear();

    for (auto &field : original.get_all_fields<float>()) {
        set_field_value(field.get_name(), field.get_value(), field.get_is_resolved());
    }
    for (auto &field : original.get_all_fields<std::string>()) {
        set_field_value(field.get_name(), field.get_value(), field.get_is_resolved());
    }
    for (auto &field : original.get_all_fields<DmsSerializable*>()) {
        set_field_value(field.get_name(), field.get_value(), field.get_is_resolved());
    }
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

void DmsFieldScope::print(std::ostream &os, bool split) const {
    for (auto &field : float_fields) {
        if (!split) os << " ";
        field.second.print(os, split);
    }
    for (auto &field : string_fields) {
        if (!split) os << " ";
        field.second.print(os, split);
    }
    for (auto &field : object_fields) {
        field.second.print(os, false);
    }
}

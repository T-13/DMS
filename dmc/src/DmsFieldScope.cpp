#include "DmsFieldScope.h"

DmsFieldScope::~DmsFieldScope() {
}

void DmsFieldScope::addParent(DmsObject* newParent) {
    parent = newParent;
}

void DmsFieldScope::setFieldValue(std::string name, int value) {
    std::map<std::string, DmsField<int>>::iterator it = int_fields.find(name);

    if (it != int_fields.end()) {
        it->second.setValue(value);
    } else {
        int_fields[name] = DmsField<int>(name, value, parent);
    }
}

void DmsFieldScope::setFieldValue(std::string name, float value) {
    std::map<std::string, DmsField<float>>::iterator it = float_fields.find(name);

    if (it != float_fields.end()) {
        it->second.setValue(value);
    } else {
        float_fields[name] = DmsField<float>(name, value, parent);
    }
}

void DmsFieldScope::setFieldValue(std::string name, std::string value) {
    std::map<std::string, DmsField<std::string>>::iterator it = string_fields.find(name);

    if (it != string_fields.end()) {
        it->second.setValue(value);
    } else {
        string_fields[name] = DmsField<std::string >(name, value, parent);
    }
}

void DmsFieldScope::getFieldValue(std::string name, int* value) {
    std::map<std::string, DmsField<int>>::iterator it = int_fields.find(name);

    if (it != int_fields.end()) {
        *value = it->second.getValue();
    }
}

void DmsFieldScope::getFieldValue(std::string name, float* value) {
    std::map<std::string, DmsField<float>>::iterator it = float_fields.find(name);

    if (it != float_fields.end()) {
        *value = it->second.getValue();
    }
}

void DmsFieldScope::getFieldValue(std::string name, std::string* value) {
    std::map<std::string, DmsField<std::string>>::iterator it = string_fields.find(name);

    if (it != string_fields.end()) {
        *value = it->second.getValue();
    }
}

std::vector<std::string> DmsFieldScope::getAllFieldNames() {
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

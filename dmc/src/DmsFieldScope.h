#pragma once

#include <map>

#include "DmsField.h"

class DmsObject;

class DmsFieldScope {
public:
    DmsFieldScope();
    ~DmsFieldScope();

    void add_parent(DmsObject *parent_);

    void set_field_value(std::string name, int value);
    void set_field_value(std::string name, float value);
    void set_field_value(std::string name, std::string value);

    template<typename T>
    T get_field_value(std::string name);

    std::vector<std::string> get_all_field_names();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

 private:
    DmsObject* parent;

    std::map<std::string, DmsField<int>> int_fields;
    std::map<std::string, DmsField<float>> float_fields;
    std::map<std::string, DmsField<std::string>> string_fields;
};

template<>
inline int DmsFieldScope::get_field_value(std::string name) {
    std::map<std::string, DmsField<int>>::iterator it = int_fields.find(name);
    if (it != int_fields.end()) {
        return it->second.get_value();
    }
    return 0;
}

template<>
inline float DmsFieldScope::get_field_value(std::string name) {
    std::map<std::string, DmsField<float>>::iterator it = float_fields.find(name);
    if (it != float_fields.end()) {
        return it->second.get_value();
    }
    return 0.0f;
}

template<>
inline std::string DmsFieldScope::get_field_value(std::string name) {
    std::map<std::string, DmsField<std::string>>::iterator it = string_fields.find(name);
    if (it != string_fields.end()) {
        return it->second.get_value();
    }
    return "";
}

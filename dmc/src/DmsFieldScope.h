#pragma once

#include <map>

#include "DmsField.h"

class DmsObject;

class DmsFieldScope {
public:
    DmsFieldScope();
    ~DmsFieldScope();

    void addParent(DmsObject* newParent);

    void setFieldValue(std::string name, int value);
    void setFieldValue(std::string name, float value);
    void setFieldValue(std::string name, std::string value);

    void getFieldValue(std::string name, int* value);
    void getFieldValue(std::string name, float* value);
    void getFieldValue(std::string name, std::string* value);

    std::vector<std::string> getAllFieldNames();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

 private:
    DmsObject* parent;

    std::map<std::string, DmsField<int>> int_fields;
    std::map<std::string, DmsField<float>> float_fields;
    std::map<std::string, DmsField<std::string>> string_fields;
};


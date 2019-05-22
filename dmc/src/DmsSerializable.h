#pragma once

#include <string>

class DmsSerializable {
public:
    virtual std::string serialize(bool split = false) = 0;
};

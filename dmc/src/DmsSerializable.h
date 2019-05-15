#pragma once

#include <string>

class DmsSerializable {
public:
    virtual std::string serialize() = 0;
};

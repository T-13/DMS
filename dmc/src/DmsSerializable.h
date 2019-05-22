#pragma once

#include <string>

class DmsSerializable {
public:
    friend std::ostream &operator<<(std::ostream &os, const DmsSerializable &serializable) {
        serializable.print(os);
        return os;
    }

    virtual void print(std::ostream &os, bool split = false) const = 0;
};

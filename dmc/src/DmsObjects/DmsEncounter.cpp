#include "DmsEncounter.h"

DmsEncounter::DmsEncounter(DmsFieldScope *enclosing_scope)
        : DmsObject(enclosing_scope) {
}

bool DmsEncounter::verify() {
    std::vector<std::string> fields = field_scope.get_all_field_names();

    // Contains any unwanted field
    for (const auto &field : fields) {
        if (field.find("prefix_") != 0 && field.find("some_") != 0) {
            return false;
        }
    }

    return true;
}

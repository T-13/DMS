#include "Resolver.h"
#include <iostream>

Resolver::Resolver(DmsGame *game_){
    game = game_;
}

Node Resolver::resolve() {
    std::cout << game->serialize() << std::endl;
    for(auto constant_field : game->constants->field_scope.get_all_fields<std::string>()) {
        // All string fields have the option to not be resolves. Float and int field are resolved 100%
        if (!constant_field.get_is_resolved()) {
            std::cout << constant_field.get_name() << ": " << constant_field.get_is_resolved() << std::endl;
        }   
    }
}
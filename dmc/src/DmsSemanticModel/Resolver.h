#pragma once

#include <exception>
#include <string>

#include "../DmsGame.h"
#include "Node.h"

class ResolveException: public std::exception {
public:
    enum State {
        VariableUndefined,
        CircularVariableDependency
    };

    ResolveException(std::string variable, int type) {
        if (type == VariableUndefined) {
            m_msg = "Error{\nVariable: " + variable + " not defined in this scope\n}\n";
        } else if (type == CircularVariableDependency) {
            m_msg = "Error{\nVariable" + variable + " cannot be resolved <=> Circular variable dependancy\n}\n";
        }
    }

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

class Resolver {
public:
    Resolver(DmsGame* game_);

    Node resolve();

private:
    DmsGame* game;

    template<typename T>
    T resolve(DmsField<T> field);
};

template<>
inline std::string Resolver::resolve(DmsField<std::string> field){
    if (field.is_being_resolved) {
        throw new ResolveException(field.get_name(), ResolveException::CircularVariableDependency);
    }
}

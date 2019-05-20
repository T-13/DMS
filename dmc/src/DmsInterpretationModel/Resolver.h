#pragma once

#include <exception>
#include <string>

#include "../DmsGame.h"

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

    void resolve();

private:
    DmsGame* game;
};

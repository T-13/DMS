#pragma once

#include "../DmsGame.h"
#include "Node.h"
#include <exception>
#include <string>

class ResolveException: public std::exception {
private:
    std::string m_msg;
public:

    ResolveException(std::string variable, int type)
    {
        if(type == VARIABLE_NOT_DEFINED) {
            m_msg = "Error{\nVariable: " + variable + " not defined in this scope\n}\n";
        }
        else if(type == CIRCULAR_VARIABLE_DEPENDANCY) {
            m_msg = "Error{\nVariable" + variable + " cannot be resolved <=> Circular variable dependancy\n}\n";
        }
    }

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

    const static int VARIABLE_NOT_DEFINED = 0;
    const static int CIRCULAR_VARIABLE_DEPENDANCY = 1;
};

class Resolver {
    DmsGame* game;

public:
    Resolver(DmsGame* game_);

    Node resolve();

private:
    template<class T>
    T resolve(DmsField<T> field);


};

template<>
inline std::string Resolver::resolve(DmsField<std::string> field){
    if (field.is_being_resolved) {
        throw new ResolveException(field.get_name(), ResolveException::CIRCULAR_VARIABLE_DEPENDANCY);
    }

    

    
}
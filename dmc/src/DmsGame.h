#pragma once

#include "DmsObject.h"
#include "DmsObjects/DmsScenario.h"

class DmsGame {
public:
    DmsObject *constants;
    DmsObject *players;
    DmsObject *enemies;
    DmsObject *encounters;
    DmsObject *scenarios;
    DmsScenario *starting_scenario;

    DmsGame();
    ~DmsGame();

    void print(std::ostream &os) const;
};

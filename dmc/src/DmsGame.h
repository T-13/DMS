#pragma once

#include "DmsObject.h"

#include "DmsObjects/DmsScenario.h"
#include "DmsObjects/DmsConstants.h"

class DmsGame {
public:
    DmsGame();
    ~DmsGame();

    std::string serialize();
    std::string compile();

    DmsObject *constants;
    DmsObject *players;
    DmsObject *enemies;
    DmsObject *encounters;
    DmsObject *scenarios;
    DmsScenario *starting_scenario;
};

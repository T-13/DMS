#pragma once

#include "DmsObject.h"

#include "DmsObjects/DmsScenario.h"
#include "DmsObjects/DmsConstants.h"

class DmsGame {
public:
    DmsGame();
    ~DmsGame();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

    DmsObject *constants;
    DmsObject *players;
    DmsObject *enemies;
    DmsObject *encounters;
    DmsObject *scenarios;
    DmsScenario *starting_scenario;
};

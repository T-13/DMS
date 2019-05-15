#pragma once

#include "DmsObjects/DmsConstant.h"
#include "DmsObjects/DmsPlayer.h"
#include "DmsObjects/DmsEnemy.h"
#include "DmsObjects/DmsEncounter.h"
#include "DmsObjects/DmsScenario.h"

class DmsGame {
public:
    DmsGame();
    ~DmsGame();

    // TODO - Choose serialize or compile or both and choose type str/byte[]...
    std::string serialize();
    std::string compile();

    DmsConstant *constants;
    DmsPlayer *players;
    DmsEnemy *enemies;
    DmsEncounter *encounters;
    DmsScenario *scenarios;
};

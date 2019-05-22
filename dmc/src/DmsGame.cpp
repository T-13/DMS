#include "DmsGame.h"

#include "lib/rang.hpp"

DmsGame::DmsGame() {
    constants = new DmsObject();
    players = new DmsObject();
    enemies = new DmsObject();
    encounters = new DmsObject();
    scenarios = new DmsObject();
}

DmsGame::~DmsGame() {
    delete constants;
    delete players;
    delete enemies;
    delete encounters;
    delete scenarios;
}

void DmsGame::print(std::ostream &os) const {
    os << std::endl
        << rang::fgB::cyan << "CONSTANTS:"
        << rang::style::reset << rang::fg::reset << std::endl;
    constants->print(os, true);

    os << std::endl
        << rang::fgB::cyan << "PLAYERS:"
        << rang::style::reset << rang::fg::reset;
    players->print(os, false);

    os << std::endl << std::endl
        << rang::fgB::cyan << "ENEMIES:"
        << rang::style::reset << rang::fg::reset;
    enemies->print(os, false);

    os << std::endl << std::endl
        << rang::fgB::cyan << "ENCOUNTERS:"
        << rang::style::reset << rang::fg::reset;
    encounters->print(os, false);

    os << std::endl << std::endl
        << rang::fgB::cyan << "SCENARIOS:"
        << rang::style::reset << rang::fg::reset;
    scenarios->print(os, false);

    os << std::endl << std::endl;
}

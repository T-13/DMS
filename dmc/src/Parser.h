#pragma once

#include <istream>
#include <math.h>

#include "Scanner.h"
#include "DmsGame.h"
#include "DmsObjects/DmsPlayer.h"
#include "DmsObjects/DmsEnemy.h"
#include "DmsObjects/DmsDuplicator.h"
#include "DmsObjects/DmsScenario.h"

class Parser {
public:
    Parser(std::istream *input)
            : scanner(input), result(Ok) {
    }

    bool parse() {
        token = scanner.next_token();
        result = DUNGEON(); // Call top grammar procedure

        // Lexical error or premature EOF (syntax error)
        if (!token.eof()) {
            if (token.error()) {
                return Error;
            } else {
                result = Error;
            }
        }

        // Syntax error
        if (error()) {
            return Error;
        }

        return Ok;
    }

    bool error() {
        return result == Error;
    }

    DmsGame *game = new DmsGame();

protected:
    // BNF Grammar
    //
    // DUNGEON ::= CONSTANTS PLAYERS ENEMIES ENCOUNTERS SCENARIOS START
    //
    // CONSTANTS ::= "CONSTANTS:" CONSTANT | ε
    // CONSTANT ::= #identifier E | #identifier E CONSTANT
    //
    // PLAYERS ::= "PLAYERS:" PLAYER
    // PLAYER ::= #identifier STATS | #identifier STATS PLAYER
    //
    // ENEMIES ::= "ENEMIES:" ENEMY
    // ENEMY ::= #identifier STATS | #identifier STATS ENEMY
    //
    // STATS ::= STAT | STAT STATS
    // STAT ::= "has" E #identifier | has S #identifier
    //
    // ENCOUNTERS ::= "ENCOUNTERS:" HAPPENINGS
    // SCENARIOS ::= "SCENARIOS:" HAPPENINGS
    //
    // HAPPENINGS ::= #identifier "has" THING | #identifier "has" THING HAPPENINGS
    // THING ::= #identifier OCCURRENCES | #identifier OCCURRENCES + THING
    // OCCURRENCES ::= * #int | ε
    //
    // START ::= "START" #identifier
    //
    // E ::= T EE                                       // Expression
    // EE::= + T EE | - T EE | ε                        // Sub-Expression
    // T ::= F TT                                       // Term
    // TT::= * F TT | / F TT | ^ F TT | % F TT | ε      // Sub-Term
    // F ::= ( E ) | #float | #variable                 // Prioritized Expression

    bool DUNGEON() {
        return CONSTANTS() && PLAYERS() && ENEMIES() && ENCOUNTERS() && SCENARIOS() && START();
    }

    bool CONSTANTS() {
        if (token.lexem() == "CONSTANTS:") {
            token = scanner.next_token();
            return CONSTANT();
        }
        return Ok;
    }

    bool CONSTANT() {
        if (token.type() == Token::Identifier) {

            std::string field_name = token.lexem();

            token = scanner.next_token();
            if (token.type() == Token::String) {
                game->constants->field_scope.set_field_value(field_name, token.lexem(), true);
                token = scanner.next_token();

                if (token.type() == Token::Identifier) {
                    return CONSTANT();
                } else {
                    return Ok;
                }
            } else {
                float value;
                if (!E(value)) return Error;
                game->constants->field_scope.set_field_value(field_name, value, true);

                if (token.type() == Token::Identifier) {
                    return CONSTANT();
                } else {
                    return Ok;
                }
            }
        }
        return Error;
    }

    bool PLAYERS() {
        if (token.lexem() == "PLAYERS:") {
            current = game->players;

            token = scanner.next_token();
            return PLAYER();
        }
        return Error;
    }

    bool PLAYER() {
        if (token.type() == Token::Identifier) {
            std::string object_name = token.lexem();

            DmsObject *playersScope = current;
            current = new DmsPlayer();

            token = scanner.next_token();
            if (!STATS()) return Error;

            playersScope->field_scope.set_field_value(object_name, current, true);
            current = playersScope;

            if (token.type() == Token::Identifier) {
                return PLAYER();
            } else {
                return Ok;
            }
        }
        return Error;
    }

    bool ENEMIES() {
        if (token.lexem() == "ENEMIES:") {
            current = game->enemies;

            token = scanner.next_token();
            return ENEMY();
        }
        return Error;
    }

    bool ENEMY() {
        if (token.type() == Token::Identifier) {
            std::string object_name = token.lexem();

            DmsObject *enemyScope = current;
            current = new DmsEnemy();

            token = scanner.next_token();
            if (!STATS()) return Error;

            enemyScope->field_scope.set_field_value(object_name, current, true);
            current = enemyScope;

            if (token.type() == Token::Identifier) {
                return ENEMY();
            } else {
                return Ok;
            }
        }
        return Error;
    }

    bool STATS() {
        if (!STAT()) return Error;
        if (token.lexem() == "has") {
            return STATS();
        }
        return Ok;
    }

    bool STAT() {
        if (token.lexem() == "has") {
            token = scanner.next_token();

            if (token.type() == Token::String) {
                std::string value = token.lexem();
                token = scanner.next_token();
                if (token.type() == Token::Identifier) {
                    current->field_scope.set_field_value(token.lexem(), value, true);
                    token = scanner.next_token();
                    return Ok;
                }
            } else {
                float new_value;
                if (!E(new_value)) return Error;

                if (token.type() == Token::Identifier) {
                    current->field_scope.set_field_value(token.lexem(), new_value, true);
                    token = scanner.next_token();
                    return Ok;
                }
            }


        }
        return Error;
    }

    bool ENCOUNTERS() {
        if (token.lexem() == "ENCOUNTERS:") {
            current = game->encounters;

            token = scanner.next_token();
            return HAPPENINGS();
        }
        return Error;
    }

    bool SCENARIOS() {
        if (token.lexem() == "SCENARIOS:") {
            current = game->scenarios;

            token = scanner.next_token();
            return HAPPENINGS();
        }
        return Error;
    }

    bool HAPPENINGS() {
        if (token.type() == Token::Identifier) {

            scope = current;
            current = nullptr;
            bool isEncounter = false;
            if (scope == game->encounters) {
                current = new DmsEncounter();
                isEncounter = true;
            } else if (scope == game->scenarios) {
                current = new DmsScenario();
            } else {
                return Error;
            }

            std::string lexem = token.lexem();
            token = scanner.next_token();
            if (token.lexem() == "has") {
                token = scanner.next_token();

                if (!THING(isEncounter)) return Error;

                scope->field_scope.set_field_value(lexem, current, true);
                current = scope;

                if (token.type() == Token::Identifier) {
                    return HAPPENINGS();
                } else {
                    return Ok;
                }
            }
        }
        return Error;
    }

    bool THING(bool isEncounter) {
        if (token.type() == Token::Identifier) {
            std::string occurrence_name = token.lexem();

            token = scanner.next_token();
            if (!OCCURRENCES(occurrence_name, isEncounter)) return Error;

            if (token.lexem() == "+") {
                token = scanner.next_token();
                return THING(isEncounter);
            } else {
                return Ok;
            }
        }

        return Error;
    }

    bool OCCURRENCES(std::string occurrence_name, bool isEncounter) {
        if (token.lexem() == "*") {

            token = scanner.next_token();
            if (token.type() == Token::Float) {
                if (isEncounter) {
                    // Encounter
                    float temp = 0;
                    DmsField<float> *previous = current->field_scope.get_field<float>(occurrence_name);
                    if (previous != nullptr) {
                        temp += previous->get_value();
                    }
                    current->field_scope.set_field_value(occurrence_name, std::stof(token.lexem()) + temp, true);
                } else {
                    // Scenario
                    auto field = game->encounters->field_scope.get_field<DmsSerializable*>(occurrence_name);
                    if (field == nullptr) {
                        return Error;
                    }
                    DmsEncounter *encounter = static_cast<DmsEncounter*>(field->get_value());

                    static_cast<DmsScenario*>(current)->addEncounter(encounter, std::stof(token.lexem()));
                }


                token = scanner.next_token();
                return Ok;
            } else {
                return Error;
            }
        }

        if (isEncounter) {
            // Encounter
            current->field_scope.set_field_value(occurrence_name, 1, true);
        } else {
            // Scenario
            auto field = game->encounters->field_scope.get_field<DmsSerializable*>(occurrence_name);
            if (field == nullptr) {
                return Error;
            }
            DmsEncounter *encounter = static_cast<DmsEncounter*>(field->get_value());

            static_cast<DmsScenario*>(current)->addEncounter(encounter, 1);
        }

        return Ok;
    }

    bool START() {
        if (token.lexem() == "START") {
            token = scanner.next_token();
            if (token.type() == Token::Identifier) {
                DmsField<DmsScenario*> *scenario = reinterpret_cast<DmsField<DmsScenario*>*>(game->scenarios->field_scope.get_field<DmsSerializable*>(token.lexem()));
                if (scenario != nullptr) {
                    game->starting_scenario = scenario->get_value();
                    token = scanner.next_token();
                    return Ok;
                } else {
                    return Error;
                }
            }
        }
        return Error;
    }

    bool E(float &out_value) {
        float in_value;
        bool ret = T(in_value);
        ret = ret && EE(in_value, out_value);
        return ret;
    }

    bool EE(float &in_value, float &out_value) {
        if (token.lexem() == "+" || token.lexem() == "-") {
            std::string sign = token.lexem();
            token = scanner.next_token();

            float new_in_value;
            float new_out_value;
            bool ret = T(new_in_value);
            ret = ret && EE(new_in_value, new_out_value);
            if (sign == "-") {
                out_value = in_value - new_out_value;
            } else {
                out_value = in_value + new_out_value;
            }
            return ret;
        }
        out_value = in_value;
        return Ok;
    }

    bool T(float &out_value) {
        float in_value;
        bool ret = F(in_value);
        ret = ret && TT(in_value, out_value);
        return ret;
    }

    bool TT(float &in_value, float &out_value) {
        if (token.lexem() == "*" || token.lexem() == "/" || token.lexem() == "^" || token.lexem() == "%") {
            std::string sign = token.lexem();
            token = scanner.next_token();

            float new_in_value;
            float new_out_value;
            bool ret = F(new_in_value);
            ret = ret && TT(new_in_value, new_out_value);

            if (sign == "*") {
                out_value = in_value * new_out_value;
            } else if (sign == "/") {
                out_value = in_value / new_out_value;
            } else if (sign == "^") {
                out_value = pow(in_value, new_out_value);
            } else if (sign == "%") {
                out_value = int(in_value) % int(new_out_value);
            }

            return ret;
        }
        out_value = in_value;
        return Ok;
    }

    bool F(float &out_value) {
        if (token.lexem() == "(") {

            token = scanner.next_token();
            if (!E(out_value)) return Error;

            if (token.lexem() == ")") {

                token = scanner.next_token();
                return Ok;
            } else {
                return Error;
            }
        } else if (token.type() == Token::Float) {
            out_value = std::stof(token.lexem());
            token = scanner.next_token();
            return Ok;
        } else if (token.type() == Token::Identifier) {
            DmsField<float> *field = game->constants->field_scope.get_field<float>(token.lexem());
            if (field) {
                out_value = field->get_value();
                token = scanner.next_token();
                return Ok;
            } else {
                return Error;
            }
        }
        return Error;
    }

private:
    enum Result : bool {
        Ok = true,
        Error = false
    };

    Scanner scanner;
    Token token;
    bool result;

    DmsObject *current;
    DmsObject *scope;
};

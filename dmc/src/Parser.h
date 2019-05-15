#pragma once

#include <istream>

#include "Scanner.h"
#include "DmsGame.h"
#include "DmsObjects/DmsPlayer.h"

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
                std::cout << "lex error: " << token << std::endl;
                return Error;
            } else {
                result = Error;
            }
        }

        // Syntax error
        if (error()) {
            std::cout << "parse error: " << token << " unexpected" << std::endl;
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

            std::string lexem = token.lexem();
            string_E = "";

            token = scanner.next_token();
            if (token.type() == Token::String) {
                game->constants->field_scope.set_field_value(lexem, token.lexem(), true);
                token = scanner.next_token();

                if (token.type() == Token::Identifier) {
                    return CONSTANT();
                } else {
                    return Ok;
                }
            } else {
                if (!E()) return Error;
            }

            game->constants->field_scope.set_field_value(lexem, string_E, false);

            if (token.type() == Token::Identifier) {
                return CONSTANT();
            } else {
                return Ok;
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
            string_OBJECT = token.lexem();

            DmsObject *playersScope = current;
            current = new DmsPlayer();

            token = scanner.next_token();
            if (!STATS()) return Error;

            playersScope->field_scope.set_field_value(string_OBJECT, current, true);
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
            string_OBJECT = token.lexem();

            DmsObject *enemyScope = current;
            current = new DmsPlayer();

            token = scanner.next_token();
            if (!STATS()) return Error;

            enemyScope->field_scope.set_field_value(string_OBJECT, current, true);
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

            string_E = "";
            bool resolved = false;

            if (token.type() == Token::String) {
                string_E = token.lexem();
                token = scanner.next_token();
                resolved = true;
            } else {
                if (!E()) return Error;
            }

            if (token.type() == Token::Identifier) {
                current->field_scope.set_field_value(token.lexem(), string_E, resolved);

                token = scanner.next_token();
                return Ok;
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

            std::string lexem = token.lexem();
            token = scanner.next_token();
            if (token.lexem() == "has") {
                token = scanner.next_token();

                string_THING = "";
                if (!THING()) return Error;

                current->field_scope.set_field_value(lexem, string_THING, false);

                if (token.type() == Token::Identifier) {
                    return HAPPENINGS();
                } else {
                    return Ok;
                }
            }
        }
        return Error;
    }

    bool THING() {
        if (token.type() == Token::Identifier) {
            string_THING += token.lexem();

            token = scanner.next_token();
            if (!OCCURRENCES()) return Error;

            if (token.lexem() == "+") {
                string_THING += token.lexem();

                token = scanner.next_token();
                return THING();
            } else {
                return Ok;
            }
        }

        return Error;
    }

    bool OCCURRENCES() {
        if (token.lexem() == "*") {
            string_THING += token.lexem();

            token = scanner.next_token();

            if (token.type() == Token::Float) {
                string_THING += token.lexem();

                token = scanner.next_token();
                return Ok;
            } else {
                return Error;
            }
        }
        return Ok;
    }

    bool START() {
        if (token.lexem() == "START") {
            token = scanner.next_token();
            if (token.type() == Token::Identifier) {
                token = scanner.next_token();
                return Ok;
            }
        }
        return Error;
    }

    bool E() {
        return T() && EE();
    }

    bool EE() {
        if (token.lexem() == "+" || token.lexem() == "-") {

            string_E += token.lexem();

            token = scanner.next_token();
            return T() && EE();
        }
        return Ok;
    }

    bool T() {
        return F() && TT();
    }

    bool TT() {
        if (token.lexem() == "*" || token.lexem() == "/" || token.lexem() == "^" || token.lexem() == "%") {

            string_E += token.lexem();

            token = scanner.next_token();
            return F() && TT();
        }
        return Ok;
    }

    bool F() {
        if (token.lexem() == "(") {

            string_E += token.lexem();

            token = scanner.next_token();
            if (!E()) return Error;

            if (token.lexem() == ")") {

                string_E += token.lexem();

                token = scanner.next_token();
                return Ok;
            } else {
                return Error;
            }
        } else if (token.type() == Token::Float || token.type() == Token::Identifier) {

            string_E += token.lexem();

            token = scanner.next_token();
            return Ok;
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

    std::string string_E = "";
    std::string string_STAT = "";
    std::string string_OBJECT = "";
    std::string string_THING = "";
    DmsObject *current;
};

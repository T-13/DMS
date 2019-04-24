#pragma once

#include <istream>

#include "scanner.h"

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
                return Ok;
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
        return result;
    }

protected:
    // BNF Grammar
    //
    // DUNGEON ::= CONSTANTS PLAYERS ENEMIES ENCOUNTERS SCENARIOS START
    //
    // CONSTANTS ::= "CONSTANTS:" CONSTANT | ε
    // CONSTANT ::= #identifier E | #identifier E CONSTANT
    //
    // PLAYERS ::= "PLAYERS:" PLAYER
    // PLAYER ::= #identifier STAT | #identifier STAT PLAYER
    //
    // ENEMIES ::= "ENEMIES:" ENEMY
    // ENEMY ::= #identifier STAT | #identifier STAT ENEMY
    //
    // STAT ::= "has" E ATTRIBUTE
    // ATTRIBUTE ::= "hp" | "dmg" | "hit_chance" | ...
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
            token = scanner.next_token();
            if (!E()) return Error;

            if (token.type() == Token::Identifier) {
                return CONSTANT();
            }
        }
        return Error;
    }

    bool PLAYERS() {

    }

    bool PLAYER() {

    }

    bool ENEMIES() {

    }

    bool ENEMY() {

    }

    bool STAT() {

    }

    bool ATTRIBUTE() {

    }

    bool ENCOUNTERS() {

    }

    bool SCENARIOS() {

    }

    bool HAPPENINGS() {

    }

    bool THING() {

    }

    bool OCCURRENCES() {

    }

    bool START() {

    }

    bool E() {
        return T() && EE();
    }

    bool EE() {
        if (token.lexem() == "+" || token.lexem() == "-") {
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
            token = scanner.next_token();
            return F() && TT();
        }
        return Ok;
    }

    bool F() {
        if (token.lexem() == "(") {
            token = scanner.next_token();
            if (!E()) return Error;

            if (token.lexem() == ")") {
                token = scanner.next_token();
                return Ok;
            } else {
                return Error;
            }
        } else if (token.type() == Token::Float || token.type() == Token::Identifier) {
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
};

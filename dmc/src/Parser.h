#pragma once

#include <istream>

#include "Scanner.h"

class Parser {
public:
    Parser(std::istream *input)
            : scanner(input), result(Ok) {
    }

    bool parse() {
        token = scanner.next_token();
        result = S(); // Call top grammar procedure

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
    // TODO DMS
    //
    // S   ::= for I to E S C | #Keyword E C | I C | epsilon    // Statement
    // I   ::= #Identifier := E | #Identifier | epsilon         // Identifier (Assignment)
    // C   ::= ; S                                              // Chain (statements)
    //
    // E   ::= T EE                                             // Expression
    // EE  ::= + T EE | - T EE | epsilon                        // Sub-Expression
    // T   ::= F TT                                             // Term
    // TT  ::= * F TT | / F TT | ^ F TT | % F TT | epsilon      // Sub-Term
    // F   ::= ( E ) | #Float | #Identifier                     // Prioritized Expression

    bool S() {
        if (token.lexem() == "for") {
            token = scanner.next_token();
            if (!I()) return Error;

            if (token.lexem() == "to") {
                token = scanner.next_token();
                return E() && S() && C();
            }

            return Error;
        } else if (token.type() == Token::Keyword && token.lexem() != "to") {
            token = scanner.next_token();
            return E() && C();
        } else {
            return I() && C();
        }
    }

    bool I() {
        if (token.type() == Token::Identifier) {
            token = scanner.next_token();

            if (token.lexem() == ":=") {
                token = scanner.next_token();
                return E();
            }
        }

        return Ok;
    }

    bool C() {
        if (token.lexem() == ";") {
            token = scanner.next_token();
            return S();
        }

        return Ok;
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

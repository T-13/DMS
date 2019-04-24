#pragma once

#include <istream>
#include <string>

#include "Token.h"

class Scanner {
public:
    Scanner(std::istream *input)
            : _input(input) {
        // Initialize in-time (not in initializer list)
        row = 1;
        column = 1;

        init_automata();
    }

    Token next_token() {
        return last_token = next_token_imp();
    }

    Token current_token() {
        return last_token;
    }

protected:
    // Gets next state, knowing current state and next character
    int get_next_state(int state, int ch) const {
        if (ch == -1) return NoEdge;
        return automata[state][ch];
    }

    // Checks if state is finite (final)
    bool is_finite_state(int state) const {
        return finite[state] != Token::LexError;
    }

    Token::Type get_finite_state(int state) const {
        return finite[state];
    }

private:
    // State transition description
    const static int MaxState = 7; // Amount of states
    const static int StartState = 0; // Initial state
    const static int NoEdge = -1; // No state transition

    std::istream *_input;

    Token last_token; // Current token
    int column; // Current column in source
    int row; // Current row in source
    int automata[MaxState + 1][256]; // Transition table
    Token::Type finite[MaxState + 1]; // Finite (final) states table

    void init_automata() {
        // Clear transition table
        for (int i = 0; i <= MaxState; i++) {
            for (int j = 0; j < 256; j++) {
                automata[i][j] = NoEdge;
            }
        }

        /* Float */
        // In state 0, 1 or 2, next is digit, go to state 1
        for (int i = '0'; i <= '9'; i++) {
            automata[0][i] = automata[1][i] = automata[2][i] = 1;
        }
        // In state 1, next is dot, go to state 2
        automata[1]['.'] = 2;

        /* Operator */
        // In state 0, next is '+', '*', '-', '/', '^' or '%', go to state 3
        automata[0]['+'] = automata[0]['*'] = automata[0]['-'] =
        automata[0]['/'] = automata[0]['^'] = automata[0]['%'] = 3;

        /* Separator */
        // In state 0, next is '(', ')' or ';', go to state 4
        automata[0]['('] = automata[0][')'] = automata[0][';'] = 4;

        /* Identifier */
        // In state 0 or 6, next is alphanumeric, go to state 6
        for (int i = 'a'; i <= 'z'; i++) {
            automata[0][i] = automata[6][i] = 6;
        }
        for (int i = 'A'; i <= 'Z'; i++) {
            automata[0][i] = automata[6][i] = 6;
        }
        // In state 6, next is digit or - or _ or :, go to state 6
        for (int i = '0'; i <= '9'; i++) {
            automata[6][i] = 6;
        }
        automata[6]['-'] = automata[6]['_'] = automata[6][':'] = 6;

        /* Ignore */
        // In state 0 or 5, next is white-space, go to state 5
        automata[0]['\n'] = automata[5]['\n'] =
        automata[0][' ']  = automata[5][' ']  =
        automata[0]['\t'] = automata[5]['\t'] =
        automata[0]['\r'] = automata[5]['\r'] = 5;

        // State 0 not finite, returns lexical error
        finite[0] = Token::LexError;
        // State 1 finite, returns lexical symbol float
        finite[1] = Token::Float;
        // State 2 not finite, returns lexical error
        finite[2] = Token::LexError;
        // State 3 finite, returns lexical symbol operator
        finite[3] = Token::Operator;
        // State 4 finite, returns lexical symbol separator
        finite[4] = Token::Separator;
        // State 5 finite, returns lexical ignore
        finite[5] = Token::Ignore;
        // State 6 finite, returns lexical symbol variable
        finite[6] = Token::Identifier;
        // State 7 not finite, returns lexical error
        finite[7] = Token::LexError;
    }

    // Peeks to next character in input
    int peek() {
        return _input->peek();
    }

    // Reads next character in input
    int read() {
        int tmp = _input->get();
        column++;
        if (tmp == '\n') {
            row++;
            column = 1;
        }
        return tmp;
    }

    // Checks if end of file (next character is EOF)
    bool eof() {
        return peek() == EOF;
    }

    // Finds next lexical symbol
    Token next_token_imp() {
        int current_state = StartState;
        std::string lexem;
        int start_column = column;
        int start_row = row;

        do {
            // Go to next state at current state and input character
            int temp_state = get_next_state(current_state, peek());
            if (temp_state != NoEdge) {
                // Transition to new state possible
                current_state = temp_state;
                // Concatenate read character into lexem
                lexem += static_cast<char>(read());
            } else {
                // Transition not possible, is state finite?
                if (is_finite_state(current_state)) {
                    // State is finite, return lexical symbol
                    Token token(lexem, start_column, start_row, get_finite_state(current_state), eof());
                    if (token.type() == Token::Ignore) {
                        // Ignore white-space
                        return next_token();
                    } else {
                        return token;
                    }
                } else {
                    // State is not finite, actually read error character and return lexical error
                    lexem += static_cast<char>(read());
                    return Token(lexem, start_column, start_row, Token::LexError, eof());
                }
            }
        } while (true);
    }

};

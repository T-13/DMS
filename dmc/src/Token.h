#pragma once

#include <ostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

class Token {
public:
    enum Type {
        LexError = -1,
        Ignore = 0,
        Float = 1,
        Operator = 2,
        Separator = 3,
        Identifier = 4,
        Keyword = 5,
        String = 6
    };
    static const std::unordered_map<Type, std::string> TypeNames;
    static const std::unordered_set<std::string> Keywords;

    Token(const std::string &lexem, int column, int row, Type type, bool eof)
            : _lexem(lexem), _column(column), _row(row), _type(type), _eof(eof) {
        // Keyword (is Identifier, but reserved)
        if (_type == Identifier && Keywords.find(_lexem) != Keywords.end()) {
            _type = Keyword;
        }
    }
    Token() : _lexem("") {}

    const std::string lexem() const {
        return _lexem;
    }

    int row() const {
        return _row;
    }

    int column() const {
        return _column;
    }

    Type type() const {
        return _type;
    }

    // Is token end of file
    bool eof() const {
        return _eof;
    }

    // Is invalid token
    bool error() const {
        return _type == LexError;
    }

    friend std::ostream &operator<<(std::ostream &out, const Token &token) {
        out << "" << (token.eof() ? "EOF" : token.lexem());

        if (!token.error()) {
            out << " [" << TypeNames.at(token.type()) << "]";
        }

        out << " (" << token.row() << ", " << token.column() << ")";

        return out;
    }

private:
    std::string _lexem; // Lexical element
    int _column; // Column location of first lexem character in source
    int _row; // Row location of first lexem character in source
    Type _type;
    bool _eof;
};

// Definitions (header-only)
const std::unordered_map<Token::Type, std::string> Token::TypeNames = {
    { Float,      "float"      },
    { Operator,   "operator"   },
    { Separator,  "separator"  },
    { Identifier, "identifier" },
    { Keyword,    "keyword"    },
    { String,     "string"     }
};

const std::unordered_set<std::string> Token::Keywords = {
    "CONSTANTS:", "PLAYERS:", "ENEMIES:", "ENCOUNTERS:", "SCENARIOS:", "START", "has"
};

#include <iostream>
#include <fstream>

#include "Parser.h"
#include "DmsInterpretationModel/Resolver.h"

#include "rang.hpp"

void usage() {
    std::cout << "./dmc <input>" << std::endl << std::endl;
    std::cout << "Run DMS file." << std::endl;
    std::cout << "<input>" << std::endl;
    std::cout << "    File path (string)." << std::endl;
}

int main(int argc, char *argv[]) {
    // Parse options
    if (argc < 2) {
        std::cerr << "Invalid arguments!" << std::endl;
        usage();
        return 1;
    }

    std::string in_fname = "";

    in_fname = argv[1];
    if (in_fname.empty()) {
        std::cerr << "Invalid option '" << argv[1] << "'!" << std::endl;
        usage();
        return 1;
    }

    // Open file
    std::ifstream in_f(in_fname);
    if (!in_f.is_open()) {
        std::cerr << "Failed to open input file '" << in_fname << "'!" << std::endl;
        return 2;
    }

    // Syntax analysis / Parse
    std::cout << rang::style::bold << "Parsing ..." << rang::style::reset << std::endl;
    Parser parser(&in_f);
    bool res = parser.parse();
    if (res) {
        std::cout << "-> " << rang::fgB::green << "Successful!" << rang::fg::reset << std::endl;
    } else {
        std::cout << "-> " << rang::fgB::red << "Error! " << rang::fg::reset << parser.error_str();
    }

    // Cleanup
    in_f.close();

    if (res) {
        std::cout << std::endl << rang::style::bold << "Resolving ..." << rang::style::reset << std::endl;
        Resolver resolver = Resolver(parser.game);
        resolver.resolve();
    }

    return 0;
}

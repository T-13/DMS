#include <iostream>
#include <fstream>

#include "Parser.h"
#include "DmsInterpretationModel/Resolver.h"

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
    std::cout << "Parsing ..." << std::endl;
    Parser parser(&in_f);
    bool res = parser.parse();
    if (res) {
        std::cout << "-> Successful!" << std::endl;
    } else {
        std::cout << "-> Failed!" << std::endl << "-> " << parser.error_str();
    }

    // Cleanup
    in_f.close();

    if (res) {
        Resolver resolver = Resolver(parser.game);
        resolver.resolve();
    }

    return 0;
}

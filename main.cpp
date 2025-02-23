#include <iostream>
#include <fstream>
#include <string>
#include <vector>

import spp.lexical_analysis.lexer;
import spp.lexical_analysis.tokens;


int main() {
    // Read contents of file ../test.spp
    auto file = std::ifstream{"../test.spp"};
    const auto code = std::string{std::istreambuf_iterator(file), std::istreambuf_iterator<char>()};
    const auto lexer = SPP::LexicalAnalysis::Lexer{code};
    const auto tokens = lexer.Lex();

    std::cout << tokens.size() << std::endl;
    return 0;
}

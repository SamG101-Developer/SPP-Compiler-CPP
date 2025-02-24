#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

import spp.lexical_analysis.lexer;
import spp.lexical_analysis.tokens;
import spp.syntactic_analysis.parser;
import spp.semantic_analysis.asts.root_ast;


int main() {
    // Read contents of file ../test.spp
    auto file = std::ifstream{"../test.spp"};
    auto code = std::string{std::istreambuf_iterator(file), std::istreambuf_iterator<char>()};

    const auto lexer = SPP::LexicalAnalysis::Lexer{std::move(code)};
    auto start_time = std::chrono::high_resolution_clock::now();
    auto tokens = lexer.lex();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Lexing: " << time_taken << "ms" << std::endl;

    auto parser = SPP::SyntacticAnalysis::Parser{std::move(tokens)};
    start_time = std::chrono::high_resolution_clock::now();
    auto ast = parser.parse();
    end_time = std::chrono::high_resolution_clock::now();
    time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Parsing: " << time_taken << "ms" << std::endl;

    return 0;
}

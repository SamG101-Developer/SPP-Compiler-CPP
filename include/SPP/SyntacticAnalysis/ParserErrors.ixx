module;
#include <exception>
#include <set>
#include <string>


export module spp.syntactic_analysis.parser_error;
import spp.utils.error_formatter;
import spp.lexical_analysis.tokens;


export namespace SPP::SyntacticAnalysis::Errors {
    struct ParserError;
    struct SyntaxError;
}


struct SPP::SyntacticAnalysis::Errors::SyntaxError final : std::exception {
    std::size_t pos = 0;
    std::set<LexicalAnalysis::RawTokenTypes> expected;

    SyntaxError(
        std::size_t pos,
        std::string &&message);

    auto throw_(Utils::ErrorFormatter const &error_formatter) noexcept(false) -> void;

    auto reset(std::size_t new_pos, std::string &&new_message) -> void;
};

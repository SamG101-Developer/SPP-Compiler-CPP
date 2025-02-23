module;
#include <coroutine>
#include <magic_enum/magic_enum.hpp>


module spp.syntactic_analysis.parser_error;
import spp.lexical_analysis.tokens;

import genex.views.map;
import genex.views.replace;
import genex.views.intersperse;
import genex.views.to;
import genex.generator;


auto SPP::SyntacticAnalysis::Errors::SyntaxError::throw_(Utils::ErrorFormatter const &error_formatter) noexcept(false) -> void {
    // Convert the set of expected tokens into a set of strings.
    const auto all_expected_tokens = expected
        | genex::views::map([](const LexicalAnalysis::RawTokenTypes token) { return std::string{magic_enum::enum_name(token).data()}; })
        // | genex::views::replace("\n", "\\n")
        // | genex::views::intersperse(", ")
        | genex::views::to<std::string>();

    // Replace the "£" in the string with the set of expected tokens.
    auto error_message = std::string{what()};
    error_message = error_message
        // | genex::views::replace(static_cast<const char*>("£"), all_expected_tokens.c_str())
        | genex::views::to<std::string>();

    // Throw the error.
    throw SyntaxError(pos, error_message.c_str());
}

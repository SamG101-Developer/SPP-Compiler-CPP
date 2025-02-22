module;
#include <magic_enum/magic_enum.hpp>


module spp.syntactic_analysis.parser_error;
import spp.lexical_analysis.tokens;

import genex.views.map;
import genex.views.join;
import genex.views.replace;
import genex.views.to;
import genex.generator;


auto SPP::SyntacticAnalysis::Errors::SyntaxError::throw_(Utils::ErrorFormatter const &error_formatter) noexcept(false) -> void {
    // Convert the set of expected tokens into a set of strings.
    const auto all_expected_tokens = expected
        | genex::views::map([](const auto token) { return magic_enum::enum_name(token); })
        | genex::views::replace("\n", "\\n")
        | genex::views::join(", ")
        | genex::views::to<std::string>();

    // Replace the "£" in the string with the set of expected tokens.
    auto error_message = std::string{what()};
    error_message = error_message
        | genex::views::replace("£", all_expected_tokens.c_str())
        | genex::views::to<std::string>();

    // Throw the error.
    throw SyntaxError(error_message.c_str());
}

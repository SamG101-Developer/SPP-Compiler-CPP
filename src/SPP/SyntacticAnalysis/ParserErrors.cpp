module spp.syntactic_analysis.parser_error;
import spp.lexical_analysis.tokens;


auto SPP::SyntacticAnalysis::Errors::SyntaxError::throw_(Utils::ErrorFormatter const &error_formatter) noexcept(false) -> void {
    // Convert the set of expected tokens into a set of strings.
    const auto all_expected_tokens = expected
        | ranges::views::transform([](const auto token) { return LexicalAnalysis::TOKEN_TYPES_MAP.at(token); })
        | ranges::views::replace("\n", "\\n")
        | ranges::views::join(", ")
        | ranges::to<std::string>();

    // Replace the "£" in the string with the set of expected tokens.
    auto error_message = std::string{what()};
    // error_message = error_message
    //     | ranges::views::replace("£", all_expected_tokens.c_str())
    //     | ranges::to<std::string>();

    // Throw the error.
    throw SyntaxError(error_message.c_str());
}

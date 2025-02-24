module;
#include <magic_enum/magic_enum.hpp>
#include <ranges>


module spp.syntactic_analysis.parser_error;
import spp.lexical_analysis.tokens;

// import genex.views.chunk;
// import genex.views.map;
// import genex.views.replace;
// import genex.views.flat;
// import genex.views.intersperse;
// import genex.views.to;
// import genex.generator;


SPP::SyntacticAnalysis::Errors::SyntaxError::SyntaxError(const std::size_t pos, std::string &&message): std::exception{message.c_str()}, pos(pos) {
}


auto SPP::SyntacticAnalysis::Errors::SyntaxError::throw_(Utils::ErrorFormatter const &error_formatter) noexcept(false) -> void {
    const auto all_expected_tokens = expected
        | std::ranges::views::transform([](const LexicalAnalysis::RawTokenTypes token) -> std::string { return std::string{magic_enum::enum_name(token).data()}; })
        | std::ranges::views::join_with(std::string{", "})
        | std::ranges::to<std::string>();

    auto error_message = std::string{what()};
    error_message.replace(error_message.find("£"), 1, all_expected_tokens);
    throw SyntaxError(pos, error_message.c_str());
}

auto SPP::SyntacticAnalysis::Errors::SyntaxError::reset(const std::size_t new_pos, std::string &&new_message) -> void {
    pos = new_pos;
    std::exception::operator=(std::exception{new_message.c_str()});
}

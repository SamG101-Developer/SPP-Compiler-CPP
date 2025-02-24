module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.array_literal_n_elements_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::ArrayLiteralNElementsAst::ArrayLiteralNElementsAst(
    const std::size_t pos,
    decltype(tok_left_bracket) &&tok_left_bracket,
    decltype(elements) &&elements,
    decltype(tok_right_bracket) &&tok_right_bracket):
    Ast{pos},
    tok_left_bracket{std::move(tok_left_bracket)},
    elements{std::move(elements)},
    tok_right_bracket{std::move(tok_right_bracket)} {
}

SPP::SemanticAnalysis::Asts::ArrayLiteralNElementsAst::~ArrayLiteralNElementsAst() = default;

auto SPP::SemanticAnalysis::Asts::ArrayLiteralNElementsAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto elements_string_1 = elements | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto elements_string_2 = std::string{elements_string_1.begin(), elements_string_1.end()};

    auto string = std::format(
        "{}{}{}",
        tok_left_bracket->print(printer),
        std::move(elements_string_2),
        tok_right_bracket->print(printer));
    return string;
}

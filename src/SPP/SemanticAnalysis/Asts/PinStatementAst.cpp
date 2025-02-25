module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.pin_statement_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PinStatementAst::PinStatementAst(
    const std::size_t pos,
    decltype(tok_pin) &&tok_pin,
    decltype(pins) &&pins):
    Ast{pos},
    tok_pin{std::move(tok_pin)},
    pins{std::move(pins)} {
}

SPP::SemanticAnalysis::Asts::PinStatementAst::~PinStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::PinStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto pins_string_1 = pins | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto pins_string_2 = std::string{pins_string_1.begin(), pins_string_1.end()};

    auto string = std::format(
        "{}{}",
        tok_pin->print(printer),
        std::move(pins_string_2));
    return string;
}

module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.where_constraints_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::WhereConstraintsAst::WhereConstraintsAst(
    const std::size_t pos,
    decltype(types) &&types,
    decltype(tok_colon) &&tok_colon,
    decltype(constraint) &&constraint):
    Ast{pos},
    types{std::move(types)},
    tok_colon{std::move(tok_colon)},
    constraint{std::move(constraint)} {
}

SPP::SemanticAnalysis::Asts::WhereConstraintsAst::~WhereConstraintsAst() = default;

auto SPP::SemanticAnalysis::Asts::WhereConstraintsAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto types_string_1 = types | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto types_string_2 = std::string{types_string_1.begin(), types_string_1.end()};

    auto string = std::format(
        "{}{}{}",
        std::move(types_string_2),
        tok_colon->print(printer),
        constraint->print(printer));
    return string;
}

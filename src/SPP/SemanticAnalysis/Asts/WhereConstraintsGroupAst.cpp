module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.where_constraints_group_ast;
import spp.semantic_analysis.asts.where_constraints_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::WhereConstraintsGroupAst::WhereConstraintsGroupAst(
    const std::size_t pos,
    decltype(tok_left_bracket) &&tok_left_bracket,
    decltype(constraints) &&constraints,
    decltype(tok_right_bracket) &&tok_right_bracket):
    Ast{pos},
    tok_left_bracket{std::move(tok_left_bracket)},
    constraints{std::move(constraints)},
    tok_right_bracket{std::move(tok_right_bracket)} {
}

SPP::SemanticAnalysis::Asts::WhereConstraintsGroupAst::~WhereConstraintsGroupAst() = default;

auto SPP::SemanticAnalysis::Asts::WhereConstraintsGroupAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto constraints_string_1 = constraints | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto constraints_string_2 = std::accumulate(constraints_string_1.begin(), constraints_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}{}",
        tok_left_bracket->print(printer),
        std::move(constraints_string_2),
        tok_right_bracket->print(printer));
    return string;
}

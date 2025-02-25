module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.assignment_statement_ast;
import spp.semantic_analysis.asts.token_ast;

SPP::SemanticAnalysis::Asts::AssignmentStatementAst::AssignmentStatementAst(
    const std::size_t pos,
    decltype(lhs) &&lhs,
    decltype(tok_assign) &&tok_assign,
    decltype(rhs) &&rhs) :
    Ast{pos},
    lhs{std::move(lhs)},
    tok_assign{std::move(tok_assign)},
    rhs{std::move(rhs)} {
}

SPP::SemanticAnalysis::Asts::AssignmentStatementAst::~AssignmentStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::AssignmentStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto lhs_string_1 = lhs | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto lhs_string_2 = std::accumulate(lhs_string_1.begin(), lhs_string_1.end(), std::string{});

    auto rhs_string_1 = rhs | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto rhs_string_2 = std::accumulate(rhs_string_1.begin(), rhs_string_1.end(), std::string{});

    auto string = std::format(
        "{} {} {}",
        std::move(lhs_string_2),
        tok_assign->print(printer),
        std::move(rhs_string_2));
    return string;
}

module;
#include <format>
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
    auto string = std::format(
        "{} {} {}",
        lhs | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); }) | std::ranges::to<std::string>,
        tok_assign->print(printer),
        rhs | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); }) | std::ranges::to<std::string>);
    return string;
}

module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.loop_control_flow_statement_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LoopControlFlowStatementAst::LoopControlFlowStatementAst(
    const std::size_t pos,
    decltype(tok_exit_or_skip) &&tok_loop,
    decltype(skip_or_expr) &&skip_or_expr):
    Ast{pos},
    tok_exit_or_skip{std::move(tok_loop)},
    skip_or_expr{std::move(skip_or_expr)} {
}

SPP::SemanticAnalysis::Asts::LoopControlFlowStatementAst::~LoopControlFlowStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::LoopControlFlowStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto tok_exit_or_skip_string_1 = tok_exit_or_skip | std::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto tok_exit_or_skip_string_2 = std::accumulate(tok_exit_or_skip_string_1.begin(), tok_exit_or_skip_string_1.end(), std::string{});

    auto string = std::format(
        "{}{}",
        std::move(tok_exit_or_skip_string_2),
        skip_or_expr.has_value() ? skip_or_expr.value()->print(printer) : "");
    return string;
}

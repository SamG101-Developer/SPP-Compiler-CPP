module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.loop_expression_ast;
import spp.semantic_analysis.asts.inner_scope_ast;
import spp.semantic_analysis.asts.loop_else_statement_ast;
import spp.semantic_analysis.asts.token_ast;

SPP::SemanticAnalysis::Asts::LoopExpressionAst::LoopExpressionAst(
    const std::size_t pos,
    decltype(tok_loop) &&tok_loop,
    decltype(expr) &&expr,
    decltype(inner_scope) &&inner_scope,
    decltype(else_statement) &&else_statement):
    Ast{pos},
    tok_loop{std::move(tok_loop)},
    expr{std::move(expr)},
    inner_scope{std::move(inner_scope)},
    else_statement{std::move(else_statement)} {
}

SPP::SemanticAnalysis::Asts::LoopExpressionAst::~LoopExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::LoopExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}",
        tok_loop->print(printer),
        expr->print(printer),
        inner_scope->print(printer),
        else_statement.has_value() ? else_statement.value()->print(printer) : "");
    return string;
}

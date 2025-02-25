module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.ret_statement_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::RetStatementAst::RetStatementAst(
    const std::size_t pos,
    decltype(tok_ret) &&tok_ret,
    decltype(expr) &&expr):
    Ast{pos},
    tok_ret{std::move(tok_ret)},
    expr{std::move(expr)} {
}

SPP::SemanticAnalysis::Asts::RetStatementAst::~RetStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::RetStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_ret->print(printer),
        expr.has_value() ? expr.value()->print(printer) : "");
    return string;
}

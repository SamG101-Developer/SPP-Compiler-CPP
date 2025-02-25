module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.loop_else_statement_ast;
import spp.semantic_analysis.asts.inner_scope_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LoopElseStatementAst::LoopElseStatementAst(
    const std::size_t pos,
    decltype(tok_else) &&tok_else,
    decltype(body) &&body):
    Ast{pos},
    tok_else{std::move(tok_else)},
    body{std::move(body)} {
}

SPP::SemanticAnalysis::Asts::LoopElseStatementAst::~LoopElseStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::LoopElseStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_else->print(printer),
        body->print(printer));
    return string;
}

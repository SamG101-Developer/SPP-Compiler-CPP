module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.let_statement_initialized_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LetStatementInitializedAst::LetStatementInitializedAst(
    const std::size_t pos,
    decltype(tok_let) &&tok_let,
    decltype(variable) &&variable,
    decltype(tok_assign) &&tok_assign,
    decltype(value) &&value):
    Ast{pos},
    tok_let{std::move(tok_let)},
    variable{std::move(variable)},
    tok_assign{std::move(tok_assign)},
    value{std::move(value)} {
}

SPP::SemanticAnalysis::Asts::LetStatementInitializedAst::~LetStatementInitializedAst() = default;

auto SPP::SemanticAnalysis::Asts::LetStatementInitializedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}",
        tok_let->print(printer),
        variable->print(printer),
        tok_assign->print(printer),
        value->print(printer));
    return string;
}

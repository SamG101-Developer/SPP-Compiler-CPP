module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_postfix_operator_indexed_type_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypePostfixOperatorIndexedTypeAst::TypePostfixOperatorIndexedTypeAst(
    const std::size_t pos,
    decltype(tok_sep) &&tok_sep,
    decltype(index) &&index):
    Ast{pos},
    tok_sep{std::move(tok_sep)},
    index{std::move(index)} {
}

SPP::SemanticAnalysis::Asts::TypePostfixOperatorIndexedTypeAst::~TypePostfixOperatorIndexedTypeAst() = default;

auto SPP::SemanticAnalysis::Asts::TypePostfixOperatorIndexedTypeAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_sep->print(printer),
        index->print(printer));
    return string;
}

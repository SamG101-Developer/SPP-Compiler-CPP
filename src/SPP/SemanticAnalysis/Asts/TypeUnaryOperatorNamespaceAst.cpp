module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_unary_operator_namespace_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypeUnaryOperatorNamespaceAst::TypeUnaryOperatorNamespaceAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(tok_sep) &&tok_sep):
    Ast{pos},
    name{std::move(name)},
    tok_sep{std::move(tok_sep)} {
}

SPP::SemanticAnalysis::Asts::TypeUnaryOperatorNamespaceAst::~TypeUnaryOperatorNamespaceAst() = default;

auto SPP::SemanticAnalysis::Asts::TypeUnaryOperatorNamespaceAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        name->print(printer),
        tok_sep->print(printer));
    return string;
}

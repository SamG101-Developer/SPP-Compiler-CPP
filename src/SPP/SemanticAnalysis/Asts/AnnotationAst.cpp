module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::AnnotationAst::AnnotationAst(
    const std::size_t pos,
    decltype(tok_ast) &&tok_ast,
    decltype(name) &&name):
    Ast{pos},
    tok_ast{std::move(tok_ast)},
    name{std::move(name)} {
}

SPP::SemanticAnalysis::Asts::AnnotationAst::~AnnotationAst() = default;

auto SPP::SemanticAnalysis::Asts::AnnotationAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_ast->print(printer),
        name->print(printer));
    return string;
}

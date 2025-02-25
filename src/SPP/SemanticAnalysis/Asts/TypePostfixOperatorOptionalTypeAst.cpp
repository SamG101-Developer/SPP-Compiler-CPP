module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_postfix_operator_optional_type_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypePostfixOperatorOptionalTypeAst::TypePostfixOperatorOptionalTypeAst(
    const std::size_t pos,
    decltype(tok_question_mark) &&tok_question_mark):
    Ast{pos},
    tok_question_mark{std::move(tok_question_mark)} {
}

SPP::SemanticAnalysis::Asts::TypePostfixOperatorOptionalTypeAst::~TypePostfixOperatorOptionalTypeAst() = default;

auto SPP::SemanticAnalysis::Asts::TypePostfixOperatorOptionalTypeAst::print(Meta::AstPrinter &printer) const -> std::string {
    return tok_question_mark->print(printer);
}

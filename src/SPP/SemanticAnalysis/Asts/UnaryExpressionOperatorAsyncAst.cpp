module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.unary_expression_operator_async_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::UnaryExpressionOperatorAsyncAst::UnaryExpressionOperatorAsyncAst(
    const std::size_t pos,
    decltype(tok_async) &&tok_async):
    Ast{pos},
    tok_async{std::move(tok_async)} {
}

SPP::SemanticAnalysis::Asts::UnaryExpressionOperatorAsyncAst::~UnaryExpressionOperatorAsyncAst() = default;

auto SPP::SemanticAnalysis::Asts::UnaryExpressionOperatorAsyncAst::print(Meta::AstPrinter &printer) const -> std::string {
    return tok_async->print(printer);
}

module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.gen_expression_ast;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenExpressionAst::GenExpressionAst(
    const std::size_t pos,
    decltype(tok_gen) &&tok_gen,
    decltype(tok_with) &&tok_with,
    decltype(conv) &&conv,
    decltype(expr) &&expr):
    Ast{pos},
    tok_gen{std::move(tok_gen)},
    tok_with{std::move(tok_with)},
    conv{std::move(conv)},
    expr{std::move(expr)} {
}

SPP::SemanticAnalysis::Asts::GenExpressionAst::~GenExpressionAst() = default;

auto SPP::SemanticAnalysis::Asts::GenExpressionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}",
        tok_gen->print(printer),
        tok_with.has_value() ? tok_with.value()->print(printer) : "",
        conv->print(printer),
        expr.has_value() ? expr.value()->print(printer) : "");
    return string;
}

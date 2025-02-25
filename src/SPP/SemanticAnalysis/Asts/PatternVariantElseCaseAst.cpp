module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_variant_else_case_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.case_expression_ast;


SPP::SemanticAnalysis::Asts::PatternVariantElseCaseAst::PatternVariantElseCaseAst(
    const std::size_t pos,
    decltype(tok_else) &&tok_else,
    decltype(case_expr) &&case_expr):
    Ast{pos},
    tok_else{std::move(tok_else)},
    case_expr{std::move(case_expr)} {
}

SPP::SemanticAnalysis::Asts::PatternVariantElseCaseAst::~PatternVariantElseCaseAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternVariantElseCaseAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_else->print(printer),
        case_expr->print(printer));
    return string;
}

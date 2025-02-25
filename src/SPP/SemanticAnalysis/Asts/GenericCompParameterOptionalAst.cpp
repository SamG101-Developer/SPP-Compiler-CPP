module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_comp_parameter_optional_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericCompParameterOptionalAst::GenericCompParameterOptionalAst(
    const std::size_t pos,
    decltype(tok_cmp) &&tok_cmp,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(type) &&type,
    decltype(tok_assign) &&tok_assign,
    decltype(default_expr) &&default_expr):
    Ast{pos},
    tok_cmp{std::move(tok_cmp)},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    type{std::move(type)},
    tok_assign{std::move(tok_assign)},
    default_expr{std::move(default_expr)} {
}

SPP::SemanticAnalysis::Asts::GenericCompParameterOptionalAst::~GenericCompParameterOptionalAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericCompParameterOptionalAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}{}",
        tok_cmp->print(printer),
        name->print(printer),
        tok_colon->print(printer),
        type->print(printer),
        tok_assign->print(printer),
        default_expr->print(printer));
    return string;
}

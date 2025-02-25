module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.function_parameter_optional_ast;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::FunctionParameterOptionalAst::FunctionParameterOptionalAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(convention) &&convention,
    decltype(type) &&type,
    decltype(tok_assign) &&tok_assign,
    decltype(default_value) &&default_value):
    Ast{pos},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    convention{std::move(convention)},
    type{std::move(type)},
    tok_assign{std::move(tok_assign)},
    default_value{std::move(default_value)} {
}

SPP::SemanticAnalysis::Asts::FunctionParameterOptionalAst::~FunctionParameterOptionalAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionParameterOptionalAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}{}",
        name->print(printer),
        tok_colon->print(printer),
        convention->print(printer),
        type->print(printer),
        tok_assign->print(printer),
        default_value->print(printer));
    return string;
}

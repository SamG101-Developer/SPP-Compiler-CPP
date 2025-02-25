module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.function_parameter_variadic_ast;


SPP::SemanticAnalysis::Asts::FunctionParameterVariadicAst::FunctionParameterVariadicAst(
    const std::size_t pos,
    decltype(tok_variadic) &&tok_variadic,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(convention) &&convention,
    decltype(type) &&type):
    Ast{pos},
    tok_variadic{std::move(tok_variadic)},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    convention{std::move(convention)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::FunctionParameterVariadicAst::~FunctionParameterVariadicAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionParameterVariadicAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}",
        tok_variadic->print(printer),
        name->print(printer),
        tok_colon->print(printer),
        convention->print(printer),
        type->print(printer));
    return string;
}

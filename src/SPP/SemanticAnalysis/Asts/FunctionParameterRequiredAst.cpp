module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.function_parameter_required_ast;


SPP::SemanticAnalysis::Asts::FunctionParameterRequiredAst::FunctionParameterRequiredAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(convention) &&convention,
    decltype(type) &&type):
    Ast{pos},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    convention{std::move(convention)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::FunctionParameterRequiredAst::~FunctionParameterRequiredAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionParameterRequiredAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{} {}{}",
        name->print(printer),
        tok_colon->print(printer),
        convention->print(printer),
        type->print(printer));
    return string;
}

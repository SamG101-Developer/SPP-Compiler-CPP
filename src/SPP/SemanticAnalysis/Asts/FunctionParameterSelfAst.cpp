module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.function_parameter_self_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::FunctionParameterSelfAst::FunctionParameterSelfAst(
    const std::size_t pos,
    decltype(tok_mut) &&tok_mut,
    decltype(convention) &&convention,
    decltype(tok_self) &&tok_self):
    Ast{pos},
    tok_mut{std::move(tok_mut)},
    convention{std::move(convention)},
    tok_self{std::move(tok_self)} {
}

SPP::SemanticAnalysis::Asts::FunctionParameterSelfAst::~FunctionParameterSelfAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionParameterSelfAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        tok_mut.has_value() ? tok_mut.value()->print(printer) + " " : "",
        convention->print(printer),
        tok_self->print(printer));
    return string;
}

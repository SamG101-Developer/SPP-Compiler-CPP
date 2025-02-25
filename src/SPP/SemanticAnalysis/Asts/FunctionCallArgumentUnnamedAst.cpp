module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.function_call_argument_unnamed_ast;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::FunctionCallArgumentUnnamedAst::FunctionCallArgumentUnnamedAst(
    const std::size_t pos,
    decltype(convention) &&convention,
    decltype(tok_unpack) &&tok_unpack,
    decltype(expression) &&expression):
    Ast{pos},
    convention{std::move(convention)},
    tok_unpack{std::move(tok_unpack)},
    expression{std::move(expression)} {
}

SPP::SemanticAnalysis::Asts::FunctionCallArgumentUnnamedAst::~FunctionCallArgumentUnnamedAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionCallArgumentUnnamedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        convention->print(printer),
        tok_unpack.has_value() ? tok_unpack.value()->print(printer) : "",
        expression->print(printer));
    return string;
}

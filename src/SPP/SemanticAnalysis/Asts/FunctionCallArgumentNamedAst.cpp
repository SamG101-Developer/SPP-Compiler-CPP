module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.function_call_argument_named_ast;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::FunctionCallArgumentNamedAst::FunctionCallArgumentNamedAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(tok_assign) &&tok_assign,
    decltype(convention) &&convention,
    decltype(expression) &&expression):
    Ast{pos},
    name{std::move(name)},
    tok_assign{std::move(tok_assign)},
    convention{std::move(convention)},
    expression{std::move(expression)} {
}

SPP::SemanticAnalysis::Asts::FunctionCallArgumentNamedAst::~FunctionCallArgumentNamedAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionCallArgumentNamedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}",
        name->print(printer),
        tok_assign->print(printer),
        convention->print(printer),
        expression->print(printer));
    return string;
}

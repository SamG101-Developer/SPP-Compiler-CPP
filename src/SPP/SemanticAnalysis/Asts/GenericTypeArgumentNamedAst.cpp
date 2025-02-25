module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.generic_type_argument_named_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::GenericTypeArgumentNamedAst::GenericTypeArgumentNamedAst(
    const std::size_t pos,
    decltype(name) &&name,
    decltype(tok_assign) &&tok_assign,
    decltype(type) &&type):
    Ast{pos},
    name{std::move(name)},
    tok_assign{std::move(tok_assign)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::GenericTypeArgumentNamedAst::~GenericTypeArgumentNamedAst() = default;

auto SPP::SemanticAnalysis::Asts::GenericTypeArgumentNamedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        name->print(printer),
        tok_assign->print(printer),
        type->print(printer));
    return string;
}

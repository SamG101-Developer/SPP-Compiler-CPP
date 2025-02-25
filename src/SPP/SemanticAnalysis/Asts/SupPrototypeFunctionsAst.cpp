module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.sup_prototype_functions_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.where_block_ast;
import spp.semantic_analysis.asts.sup_implementation_ast;


SPP::SemanticAnalysis::Asts::SupPrototypeFunctionsAst::SupPrototypeFunctionsAst(
    const std::size_t pos,
    decltype(tok_sup) &&tok_sup,
    decltype(generic_params) &&generic_params,
    decltype(name) &&name,
    decltype(where_block) &&where_block,
    decltype(body) &&body):
    Ast{pos},
    tok_sup{std::move(tok_sup)},
    generic_params{std::move(generic_params)},
    name{std::move(name)},
    where_block{std::move(where_block)},
    body{std::move(body)} {
}

SPP::SemanticAnalysis::Asts::SupPrototypeFunctionsAst::~SupPrototypeFunctionsAst() = default;

auto SPP::SemanticAnalysis::Asts::SupPrototypeFunctionsAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}",
        tok_sup->print(printer),
        generic_params->print(printer),
        name->print(printer),
        where_block->print(printer),
        body->print(printer));
    return string;
}

module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.sup_prototype_extension_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.sup_implementation_ast;
import spp.semantic_analysis.asts.where_block_ast;


SPP::SemanticAnalysis::Asts::SupPrototypeExtensionAst::SupPrototypeExtensionAst(
    const std::size_t pos,
    decltype(tok_sup) &&tok_sup,
    decltype(generic_params) &&generic_params,
    decltype(name) &&name,
    decltype(tok_ext) &&tok_ext,
    decltype(superclass) &&superclass,
    decltype(where_block) &&where_block,
    decltype(body) &&body):
    Ast{pos},
    tok_sup{std::move(tok_sup)},
    generic_params{std::move(generic_params)},
    name{std::move(name)},
    tok_ext{std::move(tok_ext)},
    superclass{std::move(superclass)},
    where_block{std::move(where_block)},
    body{std::move(body)} {
}

SPP::SemanticAnalysis::Asts::SupPrototypeExtensionAst::~SupPrototypeExtensionAst() = default;

auto SPP::SemanticAnalysis::Asts::SupPrototypeExtensionAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}{}{}",
        tok_sup->print(printer),
        generic_params->print(printer),
        name->print(printer),
        tok_ext->print(printer),
        superclass->print(printer),
        where_block->print(printer),
        body->print(printer));
    return string;
}

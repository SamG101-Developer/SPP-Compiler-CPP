module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.object_initializer_ast;
import spp.semantic_analysis.asts.object_initializer_argument_group_ast;


SPP::SemanticAnalysis::Asts::ObjectInitializerAst::ObjectInitializerAst(
    const std::size_t pos,
    decltype(type) &&type,
    decltype(obj_args_group) &&obj_args_group):
    Ast{pos},
    type{std::move(type)},
    obj_args_group{std::move(obj_args_group)} {
}

SPP::SemanticAnalysis::Asts::ObjectInitializerAst::~ObjectInitializerAst() = default;

auto SPP::SemanticAnalysis::Asts::ObjectInitializerAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        type->print(printer),
        obj_args_group->print(printer));
    return string;
}

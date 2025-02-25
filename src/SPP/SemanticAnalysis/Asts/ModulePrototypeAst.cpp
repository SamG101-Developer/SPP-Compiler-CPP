module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.module_prototype_ast;
import spp.semantic_analysis.asts.module_implementation_ast;


SPP::SemanticAnalysis::Asts::ModulePrototypeAst::ModulePrototypeAst(
    const std::size_t pos,
    decltype(body) &&body):
    Ast{pos},
    body{std::move(body)} {
}

SPP::SemanticAnalysis::Asts::ModulePrototypeAst::~ModulePrototypeAst() = default;

auto SPP::SemanticAnalysis::Asts::ModulePrototypeAst::print(Meta::AstPrinter &printer) const -> std::string {
    return body->print(printer);
}

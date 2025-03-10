module;
#include <string>

module spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;


SPP::SemanticAnalysis::Asts::Ast::Ast(
    const std::size_t pos)
    : pos(pos) {
}

SPP::SemanticAnalysis::Asts::Ast::~Ast() = default;

auto SPP::SemanticAnalysis::Asts::Ast::operator==(const Ast &that) const -> bool {
    return this == &that;
}

auto SPP::SemanticAnalysis::Asts::Ast::to_string() const -> std::string {
    auto printer = Meta::AstPrinter();
    return print(printer);
}

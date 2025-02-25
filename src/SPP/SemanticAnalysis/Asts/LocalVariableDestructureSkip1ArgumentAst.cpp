module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.local_variable_destructure_skip_1_argument_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkip1ArgumentAst::LocalVariableDestructureSkip1ArgumentAst(
    const std::size_t pos,
    decltype(tok_underscore) &&tok_underscore):
    Ast{pos},
    tok_underscore{std::move(tok_underscore)} {
}

SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkip1ArgumentAst::~LocalVariableDestructureSkip1ArgumentAst() = default;

auto SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkip1ArgumentAst::print(Meta::AstPrinter &printer) const -> std::string {
    return tok_underscore->print(printer);
}

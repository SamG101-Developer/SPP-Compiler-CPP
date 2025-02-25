module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.root_ast;
import spp.semantic_analysis.asts.module_prototype_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::RootAst::RootAst(
    const std::size_t pos,
    decltype(root_ast) &&root_ast,
    decltype(tok_eof) &&tok_eof):
    Ast{pos},
    root_ast{std::move(root_ast)},
    tok_eof{std::move(tok_eof)} {
}

SPP::SemanticAnalysis::Asts::RootAst::~RootAst() = default;

auto SPP::SemanticAnalysis::Asts::RootAst::print(Meta::AstPrinter &printer) const -> std::string {
    return root_ast->print(printer);
}

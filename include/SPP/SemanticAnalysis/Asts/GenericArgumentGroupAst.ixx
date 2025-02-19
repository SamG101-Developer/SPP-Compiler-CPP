module;
#include <string>

export module spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericArgumentGroupAst;
}


struct SPP::SemanticAnalysis::Asts::GenericArgumentGroupAst final : Ast, Compiler::CompilerStages {
    // TODO

    GenericArgumentGroupAst(std::size_t pos);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

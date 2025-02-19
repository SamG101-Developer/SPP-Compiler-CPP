module;
#include <string>

export module spp.semantic_analysis.asts.generic_argument_type_unnamed_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericArgumentTypeUnnamedAst;
}


struct SPP::SemanticAnalysis::Asts::GenericArgumentTypeUnnamedAst final : Ast, Compiler::CompilerStages {
    AstMemberType<TypeAst> type;

    GenericArgumentTypeUnnamedAst(std::size_t pos, decltype(type) &&type);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.generic_identifier_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct GenericIdentifierAst;
}


struct SPP::SemanticAnalysis::Asts::GenericIdentifierAst final : Ast, Compiler::CompilerStages {
    std::string value;
    AstMemberType<GenericArgumentGroupAst> generic_argument_group;

    GenericIdentifierAst(std::size_t pos, decltype(value) &&value, decltype(generic_argument_group) &&generic_argument_group);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

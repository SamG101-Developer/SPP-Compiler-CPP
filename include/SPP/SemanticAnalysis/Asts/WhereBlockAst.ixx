module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.where_block_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.where_constraints_group_ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct WhereBlockAst;
}


struct SPP::SemanticAnalysis::Asts::WhereBlockAst final : Ast, Compiler::CompilerStages {
    AstMemberType<TokenAst> tok_where;
    AstMemberType<WhereConstraintsGroupAst> constraint_group;

    WhereBlockAst(std::size_t pos, decltype(tok_where) &&tok_where, decltype(constraint_group) &&constraint_group);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

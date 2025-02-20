module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.sup_prototype_functions_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.sup_implementation_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.where_block_ast;


export namespace SPP::SemanticAnalysis::Asts {
    struct SupPrototypeFunctionsAst;
}


struct SPP::SemanticAnalysis::Asts::SupPrototypeFunctionsAst final : Ast {
    AstMemberType<TokenAst> tok_sup;
    AstMemberTypeOpt<GenericParameterGroupAst> generic_params;
    AstMemberType<TypeAst> name;
    AstMemberTypeOpt<WhereBlockAst> where_block;
    AstMemberType<SupImplementationAst> body;

    SupPrototypeFunctionsAst(
        std::size_t pos, decltype(tok_sup) &&tok_sup, decltype(generic_params) &&generic_params, decltype(name) &&name,
        decltype(where_block) &&where_block, decltype(body) &&body);
    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

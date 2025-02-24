module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.sup_prototype_functions_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


export namespace SPP::SemanticAnalysis::Asts {
    struct SupPrototypeFunctionsAst;
}


struct SPP::SemanticAnalysis::Asts::SupPrototypeFunctionsAst final : Ast {
    AstMemberType<TokenAst> tok_sup;
    AstMemberType<GenericParameterGroupAst> generic_params;
    AstMemberType<Ast> name;
    AstMemberType<WhereBlockAst> where_block;
    AstMemberType<SupImplementationAst> body;

    SupPrototypeFunctionsAst(
        std::size_t pos,
        decltype(tok_sup) &&tok_sup,
        decltype(generic_params) &&generic_params,
        decltype(name) &&name,
        decltype(where_block) &&where_block,
        decltype(body) &&body);

    ~SupPrototypeFunctionsAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

module;
#include <string>

export module spp.semantic_analysis.asts.sup_prototype_extension_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


export namespace SPP::SemanticAnalysis::Asts {
    struct SupPrototypeExtensionAst;
}


struct SPP::SemanticAnalysis::Asts::SupPrototypeExtensionAst final : Ast {
    AstMemberType<TokenAst> tok_sup;
    AstMemberType<GenericParameterGroupAst> generic_params;
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_ext;
    AstMemberType<Ast> superclass;
    AstMemberType<WhereBlockAst> where_block;
    AstMemberType<SupImplementationAst> body;

    SupPrototypeExtensionAst(
        std::size_t pos,
        decltype(tok_sup) &&tok_sup,
        decltype(generic_params) &&generic_params,
        decltype(name) &&name,
        decltype(tok_ext) &&tok_ext,
        decltype(superclass) &&superclass,
        decltype(where_block) &&where_block,
        decltype(body) &&body);

    ~SupPrototypeExtensionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

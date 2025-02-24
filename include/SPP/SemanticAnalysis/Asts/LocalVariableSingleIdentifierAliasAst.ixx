module;
#include <string>

export module spp.semantic_analysis.asts.local_variable_single_identifier_alias_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LocalVariableSingleIdentifierAliasAst;
}


struct SPP::SemanticAnalysis::Asts::LocalVariableSingleIdentifierAliasAst final : Ast {
    AstMemberType<TokenAst> tok_as;
    AstMemberType<IdentifierAst> name;

    LocalVariableSingleIdentifierAliasAst(
        std::size_t pos,
        decltype(tok_as) &&tok_as,
        decltype(name) &&name);

    ~LocalVariableSingleIdentifierAliasAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

module;
#include <string>

export module spp.semantic_analysis.asts.local_variable_attribute_binding_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LocalVariableAttributeBindingAst;
}


struct SPP::SemanticAnalysis::Asts::LocalVariableAttributeBindingAst final : Ast {
    AstMemberType<IdentifierAst> name;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> value;

    LocalVariableAttributeBindingAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_assign) &&tok_assign,
        decltype(value) &&value);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

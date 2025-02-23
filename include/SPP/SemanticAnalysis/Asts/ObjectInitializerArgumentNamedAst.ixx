module;
#include <string>

export module spp.semantic_analysis.asts.object_initializer_argument_named_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ObjectInitializerArgumentNamedAst;
}


struct SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentNamedAst final : Ast {
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> value;

    ObjectInitializerArgumentNamedAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_assign) &&tok_assign,
        decltype(value) &&value);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.generic_comp_argument_named_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericCompArgumentNamedAst;
}


struct SPP::SemanticAnalysis::Asts::GenericCompArgumentNamedAst final : Ast {
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> value;

    GenericCompArgumentNamedAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_assign) &&tok_assign,
        decltype(value) &&value);

    ~GenericCompArgumentNamedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

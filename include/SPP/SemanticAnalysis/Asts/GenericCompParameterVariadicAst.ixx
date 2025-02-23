module;
#include <string>

export module spp.semantic_analysis.asts.generic_comp_parameter_variadic_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericCompParameterVariadicAst;
}


struct SPP::SemanticAnalysis::Asts::GenericCompParameterVariadicAst final : Ast {
    AstMemberType<TokenAst> tok_cmp;
    AstMemberType<TokenAst> tok_variadic;
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> type;

    GenericCompParameterVariadicAst(
        std::size_t pos,
        decltype(tok_cmp) &&tok_cmp,
        decltype(tok_variadic) &&tok_variadic,
        decltype(name) &&name,
        decltype(tok_colon) &&tok_colon,
        decltype(type) &&type);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

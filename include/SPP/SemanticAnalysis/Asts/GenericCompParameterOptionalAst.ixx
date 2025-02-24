module;
#include <string>

export module spp.semantic_analysis.asts.generic_comp_parameter_optional_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct GenericCompParameterOptionalAst;
}


struct SPP::SemanticAnalysis::Asts::GenericCompParameterOptionalAst final : Ast {
    AstMemberType<TokenAst> tok_cmp;
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> type;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> default_expr;

    GenericCompParameterOptionalAst(
        std::size_t pos,
        decltype(tok_cmp) &&tok_cmp,
        decltype(name) &&name,
        decltype(tok_colon) &&tok_colon,
        decltype(type) &&type,
        decltype(tok_assign) &&tok_assign,
        decltype(default_expr) &&default_expr);

    ~GenericCompParameterOptionalAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

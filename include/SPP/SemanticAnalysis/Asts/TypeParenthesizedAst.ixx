module;
#include <string>

export module spp.semantic_analysis.asts.type_parenthesized_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypeParenthesizedAst;
}


struct SPP::SemanticAnalysis::Asts::TypeParenthesizedAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<Ast> type;
    AstMemberType<TokenAst> tok_right_parenthesis;

    TypeParenthesizedAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(type) &&type,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    ~TypeParenthesizedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;

    auto convert() -> AstMemberType<Ast>;
};

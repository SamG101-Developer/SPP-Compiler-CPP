module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.tuple_literal_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TupleLiteralAst;
}


struct SPP::SemanticAnalysis::Asts::TupleLiteralAst final : Ast {
    AstMemberType<TokenAst> tok_left_parenthesis;
    AstMemberType<std::vector<Ast>> tuple_list;
    AstMemberType<TokenAst> tok_right_parenthesis;

    TupleLiteralAst(
        std::size_t pos,
        decltype(tok_left_parenthesis) &&tok_left_parenthesis,
        decltype(tuple_list) &&tuple_list,
        decltype(tok_right_parenthesis) &&tok_right_parenthesis);

    ~TupleLiteralAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

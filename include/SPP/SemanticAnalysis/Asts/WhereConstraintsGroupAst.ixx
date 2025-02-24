module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.where_constraints_group_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct WhereConstraintsGroupAst;
}


struct SPP::SemanticAnalysis::Asts::WhereConstraintsGroupAst final : Ast {
    AstMemberType<TokenAst> tok_left_bracket;
    AstMemberType<std::vector<WhereConstraintsAst>> constraints;
    AstMemberType<TokenAst> tok_right_bracket;

    WhereConstraintsGroupAst(
        std::size_t pos,
        decltype(tok_left_bracket) &&tok_left_bracket,
        decltype(constraints) &&constraints,
        decltype(tok_right_bracket) &&tok_right_bracket);

    ~WhereConstraintsGroupAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

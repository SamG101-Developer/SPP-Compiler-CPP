module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.where_constraints_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct WhereConstraintsAst;
}


struct SPP::SemanticAnalysis::Asts::WhereConstraintsAst final : Ast {
    AstMemberType<std::vector<Ast>> types;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> constraint;

    WhereConstraintsAst(
        std::size_t pos,
        decltype(types) &&types,
        decltype(tok_colon) &&tok_colon,
        decltype(constraint) &&constraint);

    ~WhereConstraintsAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

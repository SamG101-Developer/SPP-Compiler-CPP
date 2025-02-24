module;
#include <string>
#include <memory>
#include <vector>

export module spp.semantic_analysis.asts.case_expression_branch_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct CaseExpressionBranchAst;
}


struct SPP::SemanticAnalysis::Asts::CaseExpressionBranchAst final : Ast {
    AstMemberTypeOpt<TokenAst> comp_op;
    AstMemberType<std::vector<Ast>> patterns;
    AstMemberTypeOpt<PatternGuardAst> guard;
    AstMemberType<InnerScopeAst> body;

    CaseExpressionBranchAst(
        std::size_t pos,
        decltype(comp_op) &&comp_op,
        decltype(patterns) &&patterns,
        decltype(guard) &&guard,
        decltype(body) &&body);

    static auto from_else_case(
        std::size_t pos,
        std::unique_ptr<PatternVariantElseCaseAst> &&else_case) -> std::unique_ptr<CaseExpressionBranchAst>;

    ~CaseExpressionBranchAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

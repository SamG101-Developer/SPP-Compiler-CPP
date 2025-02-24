module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.case_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct CaseExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::CaseExpressionAst final : Ast {
    AstMemberType<TokenAst> tok_case;
    AstMemberType<Ast> expr;
    AstMemberTypeOpt<TokenAst> tok_of;
    AstMemberType<std::vector<CaseExpressionBranchAst>> branches;

    CaseExpressionAst(
        std::size_t pos,
        decltype(tok_case) &&tok_case,
        decltype(expr) &&expr,
        decltype(tok_of) &&tok_of,
        decltype(branches) &&branches);

    static auto from_simple(
        std::size_t pos,
        decltype(tok_case) &&tok_case,
        decltype(expr) &&expr,
        AstMemberType<InnerScopeAst> &&inner_scope,
        decltype(branches) &&branches) -> std::unique_ptr<CaseExpressionAst>;

    ~CaseExpressionAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

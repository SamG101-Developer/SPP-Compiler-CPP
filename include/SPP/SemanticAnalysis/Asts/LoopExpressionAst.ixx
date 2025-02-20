module;
#include <memory>
#include <string>
#include <map>

export module spp.semantic_analysis.asts.loop_expression_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LoopExpressionAst;
}


struct SPP::SemanticAnalysis::Asts::LoopExpressionAst final : Ast {
    AstMemberType<TokenAst> tok_loop;
    AstMemberType<LoopConditionAst> expr;
    AstMemberType<InnerScopeAst> inner_scope;
    AstMemberTypeOpt<LoopElseStatementAst> else_statement;

    std::map<std::size_t, TypeAst*> _loop_type_info;
    std::size_t _loop_level;

    LoopExpressionAst(
        std::size_t pos,
        decltype(tok_loop) &&tok_loop,
        decltype(expr) &&expr,
        decltype(inner_scope) &&inner_scope,
        decltype(else_statement) &&else_statement);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

module;
#include <memory>
#include <optional>
#include <string>

export module spp.semantic_analysis.asts.ret_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct RetStatementAst;
}


struct SPP::SemanticAnalysis::Asts::RetStatementAst final : Ast {
    AstMemberType<TokenAst> tok_ret;
    AstMemberTypeOpt<ExpressionAst> expr;

    std::optional<TypeAst*> _fun_ret_type;

    RetStatementAst(
        std::size_t pos,
        decltype(tok_ret) &&tok_ret,
        decltype(expr) &&expr);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

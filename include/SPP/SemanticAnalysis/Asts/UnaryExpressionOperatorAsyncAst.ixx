module;
#include <string>

export module spp.semantic_analysis.asts.unary_expression_operator_async_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct UnaryExpressionOperatorAsyncAst;
}


struct SPP::SemanticAnalysis::Asts::UnaryExpressionOperatorAsyncAst final : Ast {
    AstMemberType<TokenAst> tok_async;

    UnaryExpressionOperatorAsyncAst(
        std::size_t pos,
        decltype(tok_async) &&tok_async);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

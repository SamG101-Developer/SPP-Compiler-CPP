module;
#include <optional>
#include <string>
#include <tuple>

export module spp.semantic_analysis.asts.postfix_expression_operator_function_call_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.scoping.scope;


export namespace SPP::SemanticAnalysis::Asts {
    struct PostfixExpressionOperatorFunctionCallAst;
}


struct SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorFunctionCallAst final : Ast {
    AstMemberType<GenericArgumentGroupAst> generic_args_group;
    AstMemberType<Ast> function_args_group;
    AstMemberTypeOpt<TokenAst> tok_fold;

    std::optional<std::tuple<Scoping::Scope*, FunctionPrototypeAst*>> _overload;
    std::optional<Ast*> _is_async;

    PostfixExpressionOperatorFunctionCallAst(
        std::size_t pos,
        decltype(generic_args_group) &&generic_args_group,
        decltype(function_args_group) &&function_args_group,
        decltype(tok_fold) &&tok_fold);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

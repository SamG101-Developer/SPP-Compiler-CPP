module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.postfix_expression_operator_function_call_ast;
import spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorFunctionCallAst::PostfixExpressionOperatorFunctionCallAst(
    const std::size_t pos,
    decltype(generic_args_group) &&generic_args_group,
    decltype(function_args_group) &&function_args_group,
    decltype(tok_fold) &&tok_fold):
    Ast{pos},
    generic_args_group{std::move(generic_args_group)},
    function_args_group{std::move(function_args_group)},
    tok_fold{std::move(tok_fold)} {
}

SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorFunctionCallAst::~PostfixExpressionOperatorFunctionCallAst() = default;

auto SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorFunctionCallAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}",
        generic_args_group->print(printer),
        function_args_group->print(printer),
        tok_fold.has_value() ? tok_fold.value()->print(printer) : "");
    return string;
}

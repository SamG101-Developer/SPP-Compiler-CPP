module;
#include <format>
#include <string>
#include <ranges>

module spp.semantic_analysis.asts.postfix_expression_operator_member_access_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorMemberAccessAst::PostfixExpressionOperatorMemberAccessAst(
    const std::size_t pos,
    decltype(tok_access) &&tok_access,
    decltype(field) &&field):
    Ast{pos},
    tok_access{std::move(tok_access)},
    field{std::move(field)} {
}

SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorMemberAccessAst::~PostfixExpressionOperatorMemberAccessAst() = default;

auto SPP::SemanticAnalysis::Asts::PostfixExpressionOperatorMemberAccessAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_access->print(printer),
        field->print(printer));
    return string;
}

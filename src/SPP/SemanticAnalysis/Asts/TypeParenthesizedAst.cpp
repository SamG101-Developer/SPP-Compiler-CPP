module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_parenthesized_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypeParenthesizedAst::TypeParenthesizedAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(type) &&type,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    type{std::move(type)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::TypeParenthesizedAst::~TypeParenthesizedAst() = default;

auto SPP::SemanticAnalysis::Asts::TypeParenthesizedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        type->print(printer),
        tok_right_parenthesis->print(printer));
    return string;
}

auto SPP::SemanticAnalysis::Asts::TypeParenthesizedAst::convert() -> AstMemberType<Ast> {
    return std::move(type);
}

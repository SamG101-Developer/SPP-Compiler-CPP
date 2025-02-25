module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.integer_literal_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::IntegerLiteralAst::IntegerLiteralAst(
    const std::size_t pos,
    decltype(tok_sign) &&tok_sign,
    decltype(val) &&val,
    decltype(type) &&type):
    Ast{pos},
    tok_sign{std::move(tok_sign)},
    val{std::move(val)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::IntegerLiteralAst::~IntegerLiteralAst() = default;

auto SPP::SemanticAnalysis::Asts::IntegerLiteralAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}",
        tok_sign.has_value() ? tok_sign.value()->print(printer) : "",
        val->print(printer),
        type.has_value() ? type.value()->print(printer) : "");
    return string;
}

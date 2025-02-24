module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.float_literal_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::FloatLiteralAst::FloatLiteralAst(
    const std::size_t pos,
    decltype(tok_sign) &&tok_sign,
    decltype(integer_part) &&integer_part,
    decltype(tok_dot) &&tok_dot,
    decltype(decimal_part) &&decimal_part,
    decltype(type) &&type):
    Ast{pos},
    tok_sign{std::move(tok_sign)},
    integer_part{std::move(integer_part)},
    tok_dot{std::move(tok_dot)},
    decimal_part{std::move(decimal_part)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::FloatLiteralAst::~FloatLiteralAst() = default;

auto SPP::SemanticAnalysis::Asts::FloatLiteralAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}",
        tok_sign.has_value() ? tok_sign.value()->print(printer) : "",
        integer_part->print(printer),
        tok_dot->print(printer),
        decimal_part->print(printer),
        type.has_value() ? type.value()->print(printer) : "");
    return string;
}

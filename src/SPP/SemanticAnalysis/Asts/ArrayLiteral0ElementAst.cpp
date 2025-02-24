module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.array_literal_0_element_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::ArrayLiteral0ElementAst::ArrayLiteral0ElementAst(
    const std::size_t pos,
    decltype(tok_left_bracket) &&tok_left_bracket,
    decltype(elem_type) &&elem_type,
    decltype(tok_comma) &&tok_comma,
    decltype(size) &&size,
    decltype(tok_right_bracket) &&tok_right_bracket):
    Ast{pos},
    tok_left_bracket{std::move(tok_left_bracket)},
    elem_type{std::move(elem_type)},
    tok_comma{std::move(tok_comma)},
    size{std::move(size)},
    tok_right_bracket{std::move(tok_right_bracket)} {
}

SPP::SemanticAnalysis::Asts::ArrayLiteral0ElementAst::~ArrayLiteral0ElementAst() = default;

auto SPP::SemanticAnalysis::Asts::ArrayLiteral0ElementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{} {}{}",
        tok_left_bracket->print(printer),
        elem_type->print(printer),
        tok_comma->print(printer),
        size->print(printer),
        tok_right_bracket->print(printer));
    return string;
}

module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.type_array_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::TypeArrayAst::TypeArrayAst(
    const std::size_t pos,
    decltype(tok_left_bracket) &&tok_left_bracket,
    decltype(type) &&type,
    decltype(tok_comma) &&tok_comma,
    decltype(size) &&size,
    decltype(tok_right_bracket) &&tok_right_bracket):
    Ast{pos},
    tok_left_bracket{std::move(tok_left_bracket)},
    type{std::move(type)},
    tok_comma{std::move(tok_comma)},
    size{std::move(size)},
    tok_right_bracket{std::move(tok_right_bracket)} {
}

SPP::SemanticAnalysis::Asts::TypeArrayAst::~TypeArrayAst() = default;

auto SPP::SemanticAnalysis::Asts::TypeArrayAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}",
        tok_left_bracket->print(printer),
        type->print(printer),
        tok_comma->print(printer),
        size->print(printer),
        tok_right_bracket->print(printer));
    return string;
}

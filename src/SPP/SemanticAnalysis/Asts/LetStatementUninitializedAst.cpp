module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.let_statement_uninitialized_ast;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LetStatementUninitializedAst::LetStatementUninitializedAst(
    const std::size_t pos,
    decltype(tok_let) &&tok_let,
    decltype(variable) &&variable,
    decltype(tok_colon) &&tok_colon,
    decltype(conv) &&conv,
    decltype(type) &&type):
    Ast{pos},
    tok_let{std::move(tok_let)},
    variable{std::move(variable)},
    tok_colon{std::move(tok_colon)},
    conv{std::move(conv)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::LetStatementUninitializedAst::~LetStatementUninitializedAst() = default;

auto SPP::SemanticAnalysis::Asts::LetStatementUninitializedAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}{}{}{}",
        tok_let->print(printer),
        variable->print(printer),
        tok_colon->print(printer),
        conv->print(printer),
        type->print(printer));
    return string;
}

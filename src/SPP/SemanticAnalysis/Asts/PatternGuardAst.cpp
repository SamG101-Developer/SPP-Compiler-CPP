module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.pattern_guard_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::PatternGuardAst::PatternGuardAst(
    const std::size_t pos,
    decltype(tok_guard) &&tok_guard,
    decltype(expr) &&expr):
    Ast{pos},
    tok_guard{std::move(tok_guard)},
    expr{std::move(expr)} {
}

SPP::SemanticAnalysis::Asts::PatternGuardAst::~PatternGuardAst() = default;

auto SPP::SemanticAnalysis::Asts::PatternGuardAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_guard->print(printer),
        expr->print(printer));
    return string;
}

module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.rel_statement_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::RelStatementAst::RelStatementAst(
    const std::size_t pos,
    decltype(tok_rel) &&tok_rel,
    decltype(rels) &&rels):
    Ast{pos},
    tok_rel{std::move(tok_rel)},
    rels{std::move(rels)} {
}

SPP::SemanticAnalysis::Asts::RelStatementAst::~RelStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::RelStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto rels_string_1 = rels | std::views::transform([&printer](auto const &rel) { return rel->print(printer); });
    auto rels_string_2 = std::string{rels_string_1.begin(), rels_string_1.end()};

    auto string = std::format(
        "{}{}",
        tok_rel->print(printer),
        std::move(rels_string_2));
    return string;
}

module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.where_block_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.where_constraints_group_ast;


SPP::SemanticAnalysis::Asts::WhereBlockAst::WhereBlockAst(
    const std::size_t pos,
    decltype(tok_where) &&tok_where,
    decltype(constraint_group) &&constraint_group):
    Ast{pos},
    tok_where{std::move(tok_where)},
    constraint_group{std::move(constraint_group)} {
}

auto SPP::SemanticAnalysis::Asts::WhereBlockAst::from_empty() -> std::unique_ptr<WhereBlockAst> {
    return std::make_unique<WhereBlockAst>(0, nullptr, nullptr); // todo
}

SPP::SemanticAnalysis::Asts::WhereBlockAst::~WhereBlockAst() = default;

auto SPP::SemanticAnalysis::Asts::WhereBlockAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_where->print(printer),
        constraint_group->print(printer));
    return string;
}

module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.use_statement_ast;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::UseStatementAst::UseStatementAst(
    const std::size_t pos,
    decltype(annotations) &&annotations,
    decltype(tok_use) &&tok_use,
    decltype(new_type) &&new_type,
    decltype(generic_params) &&generic_params,
    decltype(tok_assign) &&tok_assign,
    decltype(old_type) &&old_type):
    Ast{pos},
    annotations{std::move(annotations)},
    tok_use{std::move(tok_use)},
    new_type{std::move(new_type)},
    generic_params{std::move(generic_params)},
    tok_assign{std::move(tok_assign)},
    old_type{std::move(old_type)} {
}

SPP::SemanticAnalysis::Asts::UseStatementAst::~UseStatementAst() = default;

auto SPP::SemanticAnalysis::Asts::UseStatementAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto annotations_string_1 = annotations | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto annotations_string_2 = std::string{annotations_string_1.begin(), annotations_string_1.end()};

    auto string = std::format(
        "{}{}{}{}{}{}",
        std::move(annotations_string_2),
        tok_use->print(printer),
        new_type->print(printer),
        generic_params->print(printer),
        tok_assign->print(printer),
        old_type->print(printer));
    return string;
}

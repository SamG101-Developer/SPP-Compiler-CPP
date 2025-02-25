module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.global_constant_ast;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;

SPP::SemanticAnalysis::Asts::GlobalConstantAst::GlobalConstantAst(
    const std::size_t pos,
    decltype(annotations) &&annotations,
    decltype(tok_cmp) &&tok_cmp,
    decltype(name) &&name,
    decltype(tok_colon) &&tok_colon,
    decltype(type) &&type,
    decltype(tok_assign) &&tok_assign,
    decltype(value) &&value):
    Ast{pos},
    annotations{std::move(annotations)},
    tok_cmp{std::move(tok_cmp)},
    name{std::move(name)},
    tok_colon{std::move(tok_colon)},
    type{std::move(type)},
    tok_assign{std::move(tok_assign)},
    value{std::move(value)} {
}

SPP::SemanticAnalysis::Asts::GlobalConstantAst::~GlobalConstantAst() = default;

auto SPP::SemanticAnalysis::Asts::GlobalConstantAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto annotations_string_1 = annotations | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto annotations_string_2 = std::string{annotations_string_1.begin(), annotations_string_1.end()};

    auto string = std::format(
        "{}{}{}{}{}{}{}",
        std::move(annotations_string_2),
        tok_cmp->print(printer),
        name->print(printer),
        tok_colon->print(printer),
        type->print(printer),
        tok_assign->print(printer),
        value->print(printer));
    return string;
}

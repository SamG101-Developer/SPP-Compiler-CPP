module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.class_attribute_ast;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::ClassAttributeAst::ClassAttributeAst(
    const std::size_t pos,
    decltype(annotations) &&annotations,
    decltype(identifier) &&identifier,
    decltype(tok_colon) &&tok_colon,
    decltype(type) &&type):
    Ast{pos},
    annotations{std::move(annotations)},
    identifier{std::move(identifier)},
    tok_colon{std::move(tok_colon)},
    type{std::move(type)} {
}

SPP::SemanticAnalysis::Asts::ClassAttributeAst::~ClassAttributeAst() = default;

auto SPP::SemanticAnalysis::Asts::ClassAttributeAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto annotations_string_1 = annotations | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto annotations_string_2 = std::accumulate(annotations_string_1.begin(), annotations_string_1.end(), std::string{});

    auto string = std::format(
        "{}\n{}{}{}\n",
        std::move(annotations_string_2),
        identifier->print(printer),
        tok_colon->print(printer),
        type->print(printer));
    return string;
}

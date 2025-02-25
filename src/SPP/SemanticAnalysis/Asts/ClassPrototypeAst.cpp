module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.class_prototype_ast;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.class_implementation_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.type_single_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.where_block_ast;


SPP::SemanticAnalysis::Asts::ClassPrototypeAst::ClassPrototypeAst(
    const std::size_t pos,
    decltype(annotations) &&annotations,
    decltype(tok_cls) &&tok_cls,
    decltype(name) &&name,
    decltype(generic_params) &&generic_args,
    decltype(where_block) &&where_block,
    decltype(class_impl) &&class_impl):
    Ast{pos},
    annotations{std::move(annotations)},
    tok_cls{std::move(tok_cls)},
    name{std::move(name)},
    generic_params{std::move(generic_args)},
    where_block{std::move(where_block)},
    class_impl{std::move(class_impl)} {
}

SPP::SemanticAnalysis::Asts::ClassPrototypeAst::~ClassPrototypeAst() = default;

auto SPP::SemanticAnalysis::Asts::ClassPrototypeAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto annotations_string_1 = annotations | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto annotations_string_2 = std::accumulate(annotations_string_1.begin(), annotations_string_1.end(), std::string{});

    auto string = std::format(
        "{}\n{}{}{}{}{}",
        std::move(annotations_string_2),
        tok_cls->print(printer),
        name->print(printer),
        generic_params->print(printer),
        where_block->print(printer),
        class_impl->print(printer));
    return string;
}


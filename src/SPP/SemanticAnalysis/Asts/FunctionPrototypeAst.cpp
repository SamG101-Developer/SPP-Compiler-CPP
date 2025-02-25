module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.function_prototype_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.function_parameter_group_ast;
import spp.semantic_analysis.asts.where_block_ast;
import spp.semantic_analysis.asts.function_implementation_ast;


SPP::SemanticAnalysis::Asts::FunctionPrototypeAst::FunctionPrototypeAst(
    const std::size_t pos,
    decltype(annotations) &&annotations,
    decltype(tok_fun) &&tok_fun,
    decltype(name) &&name,
    decltype(generic_params) &&generic_params,
    decltype(function_params) &&function_params,
    decltype(tok_arrow) &&tok_arrow,
    decltype(return_type) &&return_type,
    decltype(where_block) &&where_block,
    decltype(body) &&body):
    Ast{pos},
    annotations{std::move(annotations)},
    tok_fun{std::move(tok_fun)},
    name{std::move(name)},
    generic_params{std::move(generic_params)},
    function_params{std::move(function_params)},
    tok_arrow{std::move(tok_arrow)},
    return_type{std::move(return_type)},
    where_block{std::move(where_block)},
    body{std::move(body)} {
}

SPP::SemanticAnalysis::Asts::FunctionPrototypeAst::~FunctionPrototypeAst() = default;

auto SPP::SemanticAnalysis::Asts::FunctionPrototypeAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto annotations_string_1 = annotations | std::ranges::views::transform([&printer](const auto &element) { return element->print(printer); });
    auto annotations_string_2 = std::string{annotations_string_1.begin(), annotations_string_1.end()};

    auto string = std::format(
        "{}\n{}{}{}{}{}{}{}\n{}",
        std::move(annotations_string_2),
        tok_fun->print(printer),
        name->print(printer),
        generic_params->print(printer),
        function_params->print(printer),
        tok_arrow->print(printer),
        return_type->print(printer),
        where_block->print(printer),
        body->print(printer));
    return string;
}

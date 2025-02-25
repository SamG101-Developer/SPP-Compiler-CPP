module;
#include <format>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.object_initializer_argument_group_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentGroupAst::ObjectInitializerArgumentGroupAst(
    const std::size_t pos,
    decltype(tok_left_parenthesis) &&tok_left_parenthesis,
    decltype(obj_args_group) &&obj_args_group,
    decltype(tok_right_parenthesis) &&tok_right_parenthesis):
    Ast{pos},
    tok_left_parenthesis{std::move(tok_left_parenthesis)},
    obj_args_group{std::move(obj_args_group)},
    tok_right_parenthesis{std::move(tok_right_parenthesis)} {
}

SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentGroupAst::~ObjectInitializerArgumentGroupAst() = default;

auto SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentGroupAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto args_string_1 = obj_args_group | std::views::transform([&printer](auto const &arg) { return arg->print(printer); });
    auto args_string_2 = std::string{args_string_1.begin(), args_string_1.end()};

    auto string = std::format(
        "{}{}{}",
        tok_left_parenthesis->print(printer),
        std::move(args_string_2),
        tok_right_parenthesis->print(printer));
    return string;
}

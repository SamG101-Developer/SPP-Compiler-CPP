module;
#include <format>
#include <numeric>
#include <ranges>
#include <string>

module spp.semantic_analysis.asts.module_implementation_ast;


SPP::SemanticAnalysis::Asts::ModuleImplementationAst::ModuleImplementationAst(
    const std::size_t pos,
    decltype(members) &&members):
    Ast{pos},
    members{std::move(members)} {
}

SPP::SemanticAnalysis::Asts::ModuleImplementationAst::~ModuleImplementationAst() = default;

auto SPP::SemanticAnalysis::Asts::ModuleImplementationAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto members_string_1 = members | std::views::transform([&printer](const auto &member) { return member->print(printer); });
    auto members_string_2 = std::accumulate(members_string_1.begin(), members_string_1.end(), std::string{});

    auto string = std::format(
        "{}",
        std::move(members_string_2));
    return string;
}

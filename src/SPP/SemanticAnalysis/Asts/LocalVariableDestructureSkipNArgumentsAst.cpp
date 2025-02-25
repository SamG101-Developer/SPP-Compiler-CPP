module;
#include <format>
#include <string>

module spp.semantic_analysis.asts.local_variable_destructure_skip_n_arguments_ast;
import spp.semantic_analysis.asts.local_variable_single_identifier_ast;
import spp.semantic_analysis.asts.token_ast;


SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkipNArgumentsAst::LocalVariableDestructureSkipNArgumentsAst(
    const std::size_t pos,
    decltype(tok_variadic) &&tok_variadic,
    decltype(binding) &&binding):
    Ast{pos},
    tok_variadic{std::move(tok_variadic)},
    binding{std::move(binding)} {
}

SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkipNArgumentsAst::~LocalVariableDestructureSkipNArgumentsAst() = default;

auto SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkipNArgumentsAst::print(Meta::AstPrinter &printer) const -> std::string {
    auto string = std::format(
        "{}{}",
        tok_variadic->print(printer),
        binding.has_value() ? binding.value()->print(printer) : "");
    return string;
}

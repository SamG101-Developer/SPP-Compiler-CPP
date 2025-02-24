module;
#include <string>

export module spp.semantic_analysis.asts.local_variable_destructure_skip_n_arguments_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LocalVariableDestructureSkipNArgumentsAst;
}


struct SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkipNArgumentsAst final : Ast {
    AstMemberType<TokenAst> tok_variadic;
    AstMemberTypeOpt<LocalVariableSingleIdentifierAst> binding;

    LocalVariableDestructureSkipNArgumentsAst(
        std::size_t pos,
        decltype(tok_variadic) &&tok_variadic,
        decltype(binding) &&binding);

    ~LocalVariableDestructureSkipNArgumentsAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

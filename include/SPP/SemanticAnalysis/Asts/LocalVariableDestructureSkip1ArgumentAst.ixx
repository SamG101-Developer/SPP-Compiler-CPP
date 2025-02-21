module;
#include <string>

export module spp.semantic_analysis.asts.local_variable_destructure_skip_1_argument_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct LocalVariableDestructureSkip1ArgumentAst;
}


struct SPP::SemanticAnalysis::Asts::LocalVariableDestructureSkip1ArgumentAst final : Ast {
    AstMemberType<TokenAst> tok_underscore;

    LocalVariableDestructureSkip1ArgumentAst(
        std::size_t pos,
        decltype(tok_underscore) &&tok_underscore);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

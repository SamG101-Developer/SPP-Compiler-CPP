module;
#include <string>

export module spp.semantic_analysis.asts.object_initializer_argument_unnamed_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ObjectInitializerArgumentUnnamedAst;
}


struct SPP::SemanticAnalysis::Asts::ObjectInitializerArgumentUnnamedAst final : Ast {
    AstMemberTypeOpt<TokenAst> tok_default;
    AstMemberType<IdentifierAst> name;

    ObjectInitializerArgumentUnnamedAst(
        std::size_t pos,
        decltype(tok_default) &&tok_default,
        decltype(name) &&name);

    ~ObjectInitializerArgumentUnnamedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

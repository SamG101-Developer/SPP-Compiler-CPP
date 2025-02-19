module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.annotation_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export enum class AnnotationIdentifier;
    export struct AnnotationAst;
}


enum class SPP::SemanticAnalysis::Asts::AnnotationIdentifier {
    VIRTUAL_METHOD,
    ABSTRACT_METHOD,
    NON_IMPLEMENTED_METHOD,
    PUBLIC,
    PROTECTED,
    PRIVATE,
    HIDDEN,
    COLD,
    HOT
};


struct SPP::SemanticAnalysis::Asts::AnnotationAst final : Ast, Compiler::CompilerStages {
    AstMemberType<TokenAst> tok_ast;
    AstMemberType<IdentifierAst> name;

    AnnotationAst(std::size_t pos, decltype(tok_ast) &&tok_ast, decltype(name) &&name);
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

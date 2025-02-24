module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.class_attribute_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct ClassAttributeAst;
}


struct SPP::SemanticAnalysis::Asts::ClassAttributeAst final : Ast {
    AstMemberType<std::vector<AnnotationAst>> annotations;
    AstMemberType<IdentifierAst> identifier;
    AstMemberType<TokenAst> tok_colon;
    AstMemberType<Ast> type;

    ClassAttributeAst(
        std::size_t pos,
        decltype(annotations) &&annotations,
        decltype(identifier) &&identifier,
        decltype(tok_colon) &&tok_colon,
        decltype(type) &&type);

    ~ClassAttributeAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

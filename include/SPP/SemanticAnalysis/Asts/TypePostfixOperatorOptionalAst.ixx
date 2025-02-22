module;
#include <string>

export module spp.semantic_analysis.asts.type_postfix_operator_optional_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypePostfixOperatorOptionalAst;
}


struct SPP::SemanticAnalysis::Asts::TypePostfixOperatorOptionalAst final : Ast {
    AstMemberType<TokenAst> tok_question_mark;

    TypePostfixOperatorOptionalAst(
        std::size_t pos,
        decltype(tok_question_mark) &&tok_question_mark);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

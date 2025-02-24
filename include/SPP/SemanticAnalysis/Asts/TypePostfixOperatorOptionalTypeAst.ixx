module;
#include <string>

export module spp.semantic_analysis.asts.type_postfix_operator_optional_type_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct TypePostfixOperatorOptionalTypeAst;
}


struct SPP::SemanticAnalysis::Asts::TypePostfixOperatorOptionalTypeAst final : Ast {
    AstMemberType<TokenAst> tok_question_mark;

    TypePostfixOperatorOptionalTypeAst(
        std::size_t pos,
        decltype(tok_question_mark) &&tok_question_mark);

    ~TypePostfixOperatorOptionalTypeAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

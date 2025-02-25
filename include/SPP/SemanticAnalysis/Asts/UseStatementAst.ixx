module;
#include <string>
#include <vector>

export module spp.semantic_analysis.asts.use_statement_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct UseStatementAst;
}


struct SPP::SemanticAnalysis::Asts::UseStatementAst final : Ast {
    AstMemberType<std::vector<AnnotationAst>> annotations;
    AstMemberType<TokenAst> tok_use;
    AstMemberType<Ast> new_type;
    AstMemberType<GenericParameterGroupAst> generic_params;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> old_type;

    bool _generated = false;

    UseStatementAst(
        std::size_t pos,
        decltype(annotations) &&annotations,
        decltype(tok_use) &&tok_use,
        decltype(new_type) &&new_type,
        decltype(generic_params) &&generic_params,
        decltype(tok_assign) &&tok_assign,
        decltype(old_type) &&old_type);

    ~UseStatementAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

module;
#include <string>

export module spp.semantic_analysis.asts.generic_type_argument_named_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;

namespace SPP::SemanticAnalysis::Asts {
    export struct GenericTypeArgumentNamedAst;
}


struct SPP::SemanticAnalysis::Asts::GenericTypeArgumentNamedAst final : Ast {
    AstMemberType<Ast> name;
    AstMemberType<TokenAst> tok_assign;
    AstMemberType<Ast> type;

    GenericTypeArgumentNamedAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_assign) &&tok_assign,
        decltype(type) &&type);

    ~GenericTypeArgumentNamedAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

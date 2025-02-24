module;
#include <string>

export module spp.semantic_analysis.asts.root_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct RootAst;
}


struct SPP::SemanticAnalysis::Asts::RootAst final : Ast {
    AstMemberType<ModulePrototypeAst> root_ast;
    AstMemberType<TokenAst> tok_eof;

    RootAst(
        std::size_t pos,
        decltype(root_ast) &&root_ast,
        decltype(tok_eof) &&tok_eof);

    ~RootAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

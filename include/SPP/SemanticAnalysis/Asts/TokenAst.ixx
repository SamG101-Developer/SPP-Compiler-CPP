module;
#include <string>

export module spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;
import spp.lexical_analysis.tokens;


namespace SPP::SemanticAnalysis::Asts {
    export struct TokenAst;
}


struct SPP::SemanticAnalysis::Asts::TokenAst final : Ast {
    LexicalAnalysis::TokenTypes token_type;
    std::string token_data;

    TokenAst(
        std::size_t pos,
        decltype(token_type) token_type,
        decltype(token_data) &&token_data);

    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

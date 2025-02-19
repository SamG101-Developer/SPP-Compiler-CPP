module;
#include <string>

export module spp.semantic_analysis.asts.token_ast;
import spp.compiler.compiler_stages;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;
import spp.lexical_analysis.tokens;


namespace SPP::SemanticAnalysis::Asts {
    export struct TokenAst;
}


struct SPP::SemanticAnalysis::Asts::TokenAst final : Ast, Compiler::CompilerStages {
    LexicalAnalysis::TokenTypes token_type;
    std::string token_data;

    TokenAst(const std::size_t pos, const decltype(token_type) token_type, decltype(token_data) &&token_data) : Ast(pos), token_type(token_type), token_data(std::move(token_data)) {
    }

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;


namespace SPP::SemanticAnalysis::Asts {
    export struct ConventionAst;
    enum class ConventionType;
}


enum class SPP::SemanticAnalysis::Asts::ConventionType {
    MOV, MUT, REF
};


struct SPP::SemanticAnalysis::Asts::ConventionAst final : Ast {
    ConventionType type;

    ConventionAst(std::size_t pos, decltype(type) &&type);
    auto print(Meta::AstPrinter &printer) const -> std::string override;

    static auto mov(std::size_t pos) -> std::unique_ptr<ConventionAst>;
    static auto mut(std::size_t pos) -> std::unique_ptr<ConventionAst>;
    static auto ref(std::size_t pos) -> std::unique_ptr<ConventionAst>;
};

module;
#include <memory>
#include <string>

module spp.semantic_analysis.asts.convention_ast;


SPP::SemanticAnalysis::Asts::ConventionAst::ConventionAst(
    const std::size_t pos,
    const decltype(type) type):
    Ast{pos},
    type{type} {
}

SPP::SemanticAnalysis::Asts::ConventionAst::~ConventionAst() = default;

auto SPP::SemanticAnalysis::Asts::ConventionAst::mov(const std::size_t pos) -> std::unique_ptr<ConventionAst> {
    return std::make_unique<ConventionAst>(pos, ConventionType::MOV);
}

auto SPP::SemanticAnalysis::Asts::ConventionAst::mut(const std::size_t pos) -> std::unique_ptr<ConventionAst> {
    return std::make_unique<ConventionAst>(pos, ConventionType::MUT);
}

auto SPP::SemanticAnalysis::Asts::ConventionAst::ref(const std::size_t pos) -> std::unique_ptr<ConventionAst> {
    return std::make_unique<ConventionAst>(pos, ConventionType::REF);
}

auto SPP::SemanticAnalysis::Asts::ConventionAst::print(Meta::AstPrinter &printer) const -> std::string {
    return type == ConventionType::MOV ? "" : type == ConventionType::MUT ? "&mut " : "&";
}

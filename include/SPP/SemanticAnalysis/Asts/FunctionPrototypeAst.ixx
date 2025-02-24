module;
#include <memory>
#include <string>
#include <vector>
#include <optional>

export module spp.semantic_analysis.asts.function_prototype_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionPrototypeAst;
}


struct SPP::SemanticAnalysis::Asts::FunctionPrototypeAst : Ast {
    AstMemberType<std::vector<AnnotationAst>> annotations;
    AstMemberType<TokenAst> tok_fun;
    AstMemberType<IdentifierAst> name;
    AstMemberType<GenericParameterGroupAst> generic_params;
    AstMemberType<FunctionParameterGroupAst> function_params;
    AstMemberType<TokenAst> tok_arrow;
    AstMemberType<Ast> return_type;
    AstMemberType<WhereBlockAst> where_block;
    AstMemberType<FunctionImplementationAst> body;

    std::optional<IdentifierAst*> _orig = std::nullopt;
    std::optional<AnnotationAst*> _abstract = std::nullopt;
    std::optional<AnnotationAst*> _virtual = std::nullopt;
    std::optional<AnnotationAst*> _no_impl = std::nullopt;
    std::optional<AnnotationAst*> _cold = std::nullopt;
    std::optional<AnnotationAst*> _hot = std::nullopt;

    FunctionPrototypeAst(
        std::size_t pos,
        decltype(annotations) &&annotations,
        decltype(tok_fun) &&tok_fun,
        decltype(name) &&name,
        decltype(generic_params) &&generic_params,
        decltype(function_params) &&function_params,
        decltype(tok_arrow) &&tok_arrow,
        decltype(return_type) &&return_type,
        decltype(where_block) &&where_block,
        decltype(body) &&body);

    ~FunctionPrototypeAst() override;

    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

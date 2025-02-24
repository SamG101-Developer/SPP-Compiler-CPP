module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.function_parameter_self_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionParameterSelfAst;
}


/**
 * The FunctionParameterSelfAst is an Ast that represents a parameter in a class method, referring to the instance of
 * the class. The term "self" is a keyword, not an identifier like in Python. Only 1 "self" parameter, as the first
 * parameter, may exist in a sup-method prototype.
 *
 * The mutability of the parameter is required when the move convention is given. With a borrow convention, either & or
 * &mut, the "mut" will not be given. This is because the "self" object cannot be replaced anyway, and in a move
 * convention, "mut" refers to attribute re-assignment. The convention "&mut" covers this. Separately, "mut &mut self"
 * doesn't work like "mut param: &mut Type" does.
 */
struct SPP::SemanticAnalysis::Asts::FunctionParameterSelfAst final : Ast {
    /**
     * The token, which may be given in the self parameter, by move convention, is mutable, ie can have its attributes
     * re-assigned whilst being consumed.
     */
    AstMemberTypeOpt<TokenAst> tok_mut;

    /**
     * The convention of the self parameter. If the self parameter is given by the move convention, then the object who
     * the method belongs to is consumed on this function call and cannot be referred to again from the caller context.
     */
    AstMemberType<ConventionAst> convention;

    /**
     * The token representing the "self" part of the parameter. Required for all non-static methods, as "self" is
     * explicit in S++, like in Rust and unlike "this" in C++.
     */
    AstMemberType<IdentifierAst> tok_self;

    /**
     * Create a new FunctionParameterSelfAst with the given mutability token, convention and self token.
     * @param pos Position of the AST.
     * @param tok_mut If the "self" parameter is mutable.
     * @param convention The convention of the self parameter.
     * @param tok_self The "self" keyword token.
     */
    FunctionParameterSelfAst(
        std::size_t pos,
        decltype(tok_mut) &&tok_mut,
        decltype(convention) &&convention,
        decltype(tok_self) &&tok_self);

    ~FunctionParameterSelfAst() override;

    /**
     * A convenience function to convert the AST node to a string representation. This calls the print function with a
     * new printer object rooted at this node.
     * @return A string representation of the AST node.
     */
    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

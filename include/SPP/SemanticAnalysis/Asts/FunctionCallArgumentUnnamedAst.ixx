module;
#include <memory>
#include <optional>
#include <string>

export module spp.semantic_analysis.asts.function_call_argument_unnamed_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionCallArgumentUnnamedAst;
}


/**
 * The FunctionCallArgumentUnnamedAst is an AST that represents an argument to a function, that has a value but no name.
 * The position of the argument will map to the name of a parameter in an overload of target function prototype. If no
 * matches are made, then an error is thrown.
 *
 * The convention of the argument determines how it is passed to a function - either moved, borrowed mutably, or
 * borrowed immutably. See the ConventionAst class for more information.
 */
struct SPP::SemanticAnalysis::Asts::FunctionCallArgumentUnnamedAst final : Ast {
    /**
     * The convention of the value. This convention must match the convention of the parameter identified by the
     * position.
     */
    AstMemberType<ConventionAst> convention;

    /**
     * The optional unpacking token. If the token is present, then the arguments in the tuple are unpacked into
     * consecutive parameters in the target.
     */
    AstMemberTypeOpt<TokenAst> tok_unpack;

    /**
     * The value of the argument that is passed to the parameter of the target function. This value must match the type
     * of the parameter identified by the position.
     */
    AstMemberType<Ast> expression;

    /**
     * Create a new FunctionCallArgumentUnnamedAst with the given name, assign token, convention and expression.
     * @param pos Position of the AST.
     * @param convention The convention of the value.
     * @param tok_unpack The optional unpacking token.
     * @param expression The value of the argument.
     */
    FunctionCallArgumentUnnamedAst(
        std::size_t pos,
        decltype(convention) &&convention,
        decltype(tok_unpack) &&tok_unpack,
        decltype(expression) &&expression);

    ~FunctionCallArgumentUnnamedAst() override;

    /**
     * Print the AST node in the context of its parent and children nodes - this takes the indentation into account from
     * the scopes.
     * @param printer The printer object that maintains the current code context for indentation.
     * @return A string representation of the AST node.
     */
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

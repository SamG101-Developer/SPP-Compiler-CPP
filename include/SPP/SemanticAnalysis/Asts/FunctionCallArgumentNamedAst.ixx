module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.function_call_argument_named_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.meta.ast_printer;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionCallArgumentNamedAst;
}


/**
 * The FunctionCallArgumentNamedAst is an AST that represents an argument to a function, that has a name and a value.
 * The name of the argument will map to the name of a parameter in an overload of target function prototype. If no
 * matches are made, then an error is thrown.
 *
 * In the same way as a FunctionCallArgumentUnnamedAst, there is a convention and value. Named arguments must always
 * come after all the unnamed arguments.
 */
struct SPP::SemanticAnalysis::Asts::FunctionCallArgumentNamedAst final : Ast {
    /**
     * The name of the argument. This is the name of a parameter of the target function prototype that this argument
     * will be matched to.
     */
    AstMemberType<IdentifierAst> name;

    /**
     * The token that attaches the covention/expression to the name. Given there is a name, this token must be an assign
     * token.
     */
    AstMemberType<TokenAst> tok_assign;

    /**
     * The convention of the value. This convention must match the convention of the parameter identified by the name.
     */
    AstMemberType<ConventionAst> convention;

    /**
     * The value of the argument that is passed to the parameter of the target function. This value must match the type
     * of the parameter identified by the name.
     */
    AstMemberType<ExpressionAst> expression;

    /**
     * Create a new FunctionCallArgumentNamedAst with the given name, assign token, convention and expression.
     * @param pos Position of the AST.
     * @param name The name of the argument.
     * @param tok_assign Joins the name to the convention/expression.
     * @param convention The convention of the value.
     * @param expression The value of the argument.
     */
    FunctionCallArgumentNamedAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_assign) &&tok_assign,
        decltype(convention) &&convention,
        decltype(expression) &&expression);

    /**
     * Print the AST node in the context of its parent and children nodes - this takes the indentation into account from
     * the scopes.
     * @param printer The printer object that maintains the current code context for indentation.
     * @return A string representation of the AST node.
     */
    auto print(Meta::AstPrinter &printer) const -> std::string override;
};

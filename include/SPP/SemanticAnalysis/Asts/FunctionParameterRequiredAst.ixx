module;
#include <memory>
#include <string>

export module spp.semantic_analysis.asts.function_parameter_required_ast;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.ast_members;
import spp.semantic_analysis.meta.ast_printer;
import spp.semantic_analysis.asts.ast_types;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.token_ast;


export namespace SPP::SemanticAnalysis::Asts {
    struct FunctionParameterRequiredAst;
}


/**
 * The FunctionParameterRequiredAst is an Ast that represents a parameter in a function or class method, where any
 * function call expression must provide an argument for this parameter. The name of the parameter can be any type of
 * local variable ast, including a destructure. For example, "fun f(Point(mut x, mut y): Point) ... " is valid.
 */
struct SPP::SemanticAnalysis::Asts::FunctionParameterRequiredAst final : Ast {
    /**
     * The name of this parameter. It can be an identifier or some local variable destructure. It is identical to a
     * "let" statement, just without the "let" keyword, which is implied by the parameter being a parameter.
     */
    AstMemberType<Ast> name;

    /**
     * The colon token separating the parameter's name from the convention/type.
     */
    AstMemberType<TokenAst> tok_colon;

    /**
     * The convention of the required parameter: either a move, mutable borrow, or immutable borrow. The convention
     * determines how the argument is passed to this parameter.
     */
    AstMemberType<ConventionAst> convention;

    /**
     * The type of the required parameter. This is the type that the argument must match when calling the function.
     */
    AstMemberType<Ast> type;

    /**
     * Create a new FunctionParameterRequiredAst with the given name, colon token, convention and type.
     * @param pos Position of the AST.
     * @param name The name(s) of the parameter.
     * @param tok_colon The colon token.
     * @param convention The convention of the parameter.
     * @param type The type of the parameter.
     */
    FunctionParameterRequiredAst(
        std::size_t pos,
        decltype(name) &&name,
        decltype(tok_colon) &&tok_colon,
        decltype(convention) &&convention,
        decltype(type) &&type);

    ~FunctionParameterRequiredAst() override;

    /**
     * A convenience function to convert the AST node to a string representation. This calls the print function with a
     * new printer object rooted at this node.
     * @return A string representation of the AST node.
     */
    auto print(Meta::AstPrinter &printer) const -> std::u8string override;
};

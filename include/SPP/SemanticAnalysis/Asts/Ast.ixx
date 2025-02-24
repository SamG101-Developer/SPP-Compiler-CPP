module;
#include <string>

export module spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.meta.ast_printer;
import spp.utils.converter;


export namespace SPP::SemanticAnalysis::Asts {
    struct Ast;
}


/**
 * Default AST object that all other ASTs will inherit from. It maintains the position of the AST in the source code.
 * There are virtual functions for printing and equality checks that must be implemented by subclassed AST nodes.
 */
struct SPP::SemanticAnalysis::Asts::Ast : Utils::StringConverter {
    std::size_t pos;

    Ast(const Ast &that) = delete;
    Ast(Ast &&that) = delete;
    ~Ast() override;

    auto operator=(const Ast &that) -> Ast & = delete;
    auto operator=(Ast &&that) -> Ast & = delete;

    explicit Ast(std::size_t pos);

    /**
     * Print the AST node in the context of its parent and children nodes - this takes the indentation into account from
     * the scopes.
     * @param printer The printer object that maintains the current code context for indentation.
     * @return A string representation of the AST node.
     */
    virtual auto print(Meta::AstPrinter &printer) const -> std::string = 0;

    /**
     * All nodes will have equality checks, mostly with themselves only, but sometimes different node types will be
     * compared against each other. The default implementation is to check, by pointer, if the two nodes are the same.
     * @param that The other AST node to compare against.
     * @return Whether the two AST nodes are equal.
     */
    virtual auto operator==(const Ast &that) const -> bool;

    /**
     * A convenience function to convert the AST node to a string representation. This calls the print function with a
     * new printer object rooted at this node.
     * @return A string representation of the AST node.
     */
    [[nodiscard]] auto to_string() const -> std::string override;
};

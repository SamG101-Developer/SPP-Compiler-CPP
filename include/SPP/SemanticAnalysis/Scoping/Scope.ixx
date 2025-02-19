module;
#include <memory>
#include <string>
#include <vector>

export module spp.semantic_analysis.scoping.scope;
import spp.semantic_analysis.scoping.symbol_table;
import spp.semantic_analysis.scoping.symbol;

namespace SPP::SemanticAnalysis::Asts {
    struct Ast;
}

namespace SPP::SemanticAnalysis::Scoping {
    export struct Scope;
}


struct SPP::SemanticAnalysis::Scoping::Scope {
    std::string name;
    Scope *parent = nullptr;
    std::vector<std::unique_ptr<Scope>> children;
    SymbolTable symbol_table;
    Asts::Ast *ast = nullptr;

    std::vector<Scope*> direct_sup_scopes;
    std::vector<Scope*> direct_sub_scopes;
    TypeSymbol *type_symbol = nullptr;
    Scope *non_generic_scope = nullptr;
};

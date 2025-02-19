module;
#include <memory>
#include <optional>
#include <string>
#include <vector>


export module spp.compiler.compiler_module_tree;
import spp.utils.error_formatter;


namespace SPP::Compiler {
    export struct CompilerModule;
    class CompilerModuleTree;
}

namespace SPP::SemanticAnalysis::Asts {
    struct ModulePrototypeAst;
}

namespace SPP::LexicalAnalysis {
    struct RawToken;
}


struct SPP::Compiler::CompilerModule {
    std::string path;
    std::string code;
    std::vector<LexicalAnalysis::RawToken> token_stream;
    std::unique_ptr<SemanticAnalysis::Asts::ModulePrototypeAst> module_prototype;
    std::optional<Utils::ErrorFormatter> error;
};

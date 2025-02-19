module;
#include <any>
#include <map>
#include <string>

export module spp.compiler.compiler_stages;


export namespace SPP::Compiler {
    struct CompilerStages;
}

namespace SPP::SemanticAnalysis::Asts {
    struct Ast;
}

namespace SPP::SemanticAnalysis::Scoping {
    struct Scope;
    struct ScopeManager;
}


struct SPP::Compiler::CompilerStages {
    SemanticAnalysis::Asts::Ast* context = nullptr;
    SemanticAnalysis::Scoping::Scope* scope;

    /**
     * The preprocessor stage performs mutations on ASTs, introduces new ASTs, and remove some ASTs. This allows for
     * single-method processing of multiple ASTs, such as functions vs types with function classes superimposed over
     * them. This stage directly affects what symbols are generated.
     * @param context The context that the AST being processed belongs to (enclosing class for example).
     */
    auto pre_process(SemanticAnalysis::Asts::Ast* context) -> void;

    /**
     * The generate top-level scopes stage generates all module and superimposition level scopes and symbols. This
     * includes classes, attributes, functions, sup-methods, aliases and global constants. No generation is done for
     * symbols inside functions. The symbols are generated here so that they can be used in any module, allowing for
     * circular imports.
     * @param scope_manager The scope manager that contains all the scopes.
     */
    auto generate_top_level_scopes(SemanticAnalysis::Scoping::ScopeManager *scope_manager) -> void;

    /**
     * The generate top-level aliases stage generates all aliases at the module/sup level. This must come after the
     * symbol generation stage, as it requires symbol knowledge to attach the correct "old types". It must also come
     * before the load sup scopes stage, because superimposing over aliases requires the alias to exist beforehand, in
     * any order of compilation.
     * @param scope_manager The scope manager that contains all the scopes.
     * @param meta Meta information shared between ASTs.
     */
    auto generate_top_level_aliases(SemanticAnalysis::Scoping::ScopeManager *scope_manager, std::map<std::string, std::any> &meta) -> void;

    /**
     * The load super scopes stage links all super scopes to classes. This allows a type to know what attributes and
     * methods are on its superclasses, and is requires for symbol resolution.
     * @param scope_manager The scope manager that contains all the scopes.
     */
    auto load_super_scopes(SemanticAnalysis::Scoping::ScopeManager *scope_manager) -> void;

    /**
     * The postprocess super scopes stage performs checks that must happen after the super scopes have been injected,
     * but that are separate from the next stage (type-regeneration). This includes things that require knowledge of
     * all the super scopes.
     * @param scope_manager The scope manager that contains all the scopes.
     */
    auto postprocess_super_scopes(SemanticAnalysis::Scoping::ScopeManager *scope_manager) -> void;

    /**
     * The regenerate generic aliases stage is the generic type regeneration stage exclusive to type-aliases. This is to
     * ensure the aliases' old type has been generically substituted correctly, and is required before the rest of the
     * regular type's generic substitution is regenerated. This is because regular type regeneration may rely on aliased
     * types.
     * @param scope_manager The scope manager that contains all the scopes.
     */
    auto regenerate_generic_aliases(SemanticAnalysis::Scoping::ScopeManager *scope_manager) -> void;

    /**
     * The regenerate generic types stage takes all the pruned generic types, and regenerated them with full knowledge
     * of substitutions and inference. This is required as the generic types were placeholders earlier in the
     * compilation stages.
     * @param scope_manager The scope manager that contains all the scopes.
     */
    auto regenerate_generic_types(SemanticAnalysis::Scoping::ScopeManager *scope_manager) -> void;

    /**
     * The semantic analysis stage is the most complex, and final analysis, stage of the semantic pipeline. This stage
     * performs all the semantic checks, type inference, and type checking. This stage requires all symbols to be
     * generated, and all types to be aliased, loaded, and post-processed. All functions scopes are inspected.
     * @param scope_manager The scope manager that contains all the scopes.
     * @param meta Meta information shared between ASTs.
     */
    auto analyse_semantics(SemanticAnalysis::Scoping::ScopeManager *scope_manager, std::map<std::string, std::any> &meta) -> void;
};

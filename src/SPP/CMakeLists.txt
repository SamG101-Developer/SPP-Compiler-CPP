add_library(_SPP INTERFACE)

add_subdirectory(Compiler)
add_subdirectory(LexicalAnalysis)
add_subdirectory(SemanticAnalysis)
add_subdirectory(SyntacticAnalysis)
add_subdirectory(Utils)

target_link_libraries(_SPP INTERFACE
        SPP::Compiler
        SPP::LexicalAnalysis
        SPP::SemanticAnalysis
        SPP::SyntacticAnalysis
        SPP::Utils)

add_library(SPP::Modules ALIAS _SPP)

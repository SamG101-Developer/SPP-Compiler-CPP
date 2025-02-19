add_library(SPP_SemanticAnalysis INTERFACE)

add_subdirectory(Asts)
add_subdirectory(Meta)
add_subdirectory(Mixins)
add_subdirectory(Scoping)

target_link_libraries(SPP_SemanticAnalysis INTERFACE
        SPP::SemanticAnalysis::Asts
        SPP::SemanticAnalysis::Meta
        SPP::SemanticAnalysis::Mixins
        SPP::SemanticAnalysis::Scoping)

add_library(SPP::SemanticAnalysis ALIAS SPP_SemanticAnalysis)

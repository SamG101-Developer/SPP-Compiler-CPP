add_library(SPP_SemanticAnalysis_Scoping STATIC)

target_sources(SPP_SemanticAnalysis_Scoping PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Scoping FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Scoping/Scope.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Scoping/ScopeManager.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Scoping/Symbol.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Scoping/SymbolTable.ixx)

target_sources(SPP_SemanticAnalysis_Scoping PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Scope.cpp)

target_include_directories(SPP_SemanticAnalysis_Scoping PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_SemanticAnalysis_Scoping PRIVATE
        SPP::SemanticAnalysis::Asts)

add_library(SPP::SemanticAnalysis::Scoping ALIAS SPP_SemanticAnalysis_Scoping)

add_library(SPP_SyntacticAnalysis STATIC)

target_sources(SPP_SyntacticAnalysis PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SyntacticAnalysis FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SyntacticAnalysis/Parser.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SyntacticAnalysis/ParserErrors.ixx)

target_sources(SPP_SyntacticAnalysis PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Parser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ParserErrors.cpp)

target_include_directories(SPP_SyntacticAnalysis PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_SyntacticAnalysis PRIVATE
        SPP::LexicalAnalysis
        SPP::SemanticAnalysis::Asts
        SPP::Utils
        GenEx::GenEx Boost::boost)

add_library(SPP::SyntacticAnalysis ALIAS SPP_SyntacticAnalysis)

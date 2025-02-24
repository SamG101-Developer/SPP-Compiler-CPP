add_library(SPP_LexicalAnalysis STATIC)

target_sources(SPP_LexicalAnalysis PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/LexicalAnalysis FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/LexicalAnalysis/Lexer.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/LexicalAnalysis/Tokens.ixx)

target_sources(SPP_LexicalAnalysis PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Lexer.cpp)

target_include_directories(SPP_LexicalAnalysis PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_LexicalAnalysis PRIVATE
        magic_enum::magic_enum)

add_library(SPP::LexicalAnalysis ALIAS SPP_LexicalAnalysis)

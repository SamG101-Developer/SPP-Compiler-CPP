add_library(SPP_SemanticAnalysis_Meta STATIC)

target_sources(SPP_SemanticAnalysis_Meta PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Meta FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Meta/AstPrinter.ixx)

target_sources(SPP_SemanticAnalysis_Meta PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AstPrinter.cpp)

target_include_directories(SPP_SemanticAnalysis_Meta PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_SemanticAnalysis_Meta PRIVATE
        re2::re2)

add_library(SPP::SemanticAnalysis::Meta ALIAS SPP_SemanticAnalysis_Meta)

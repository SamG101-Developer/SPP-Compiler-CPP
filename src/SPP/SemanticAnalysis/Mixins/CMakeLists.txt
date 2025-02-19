add_library(SPP_SemanticAnalysis_Mixins STATIC)

target_sources(SPP_SemanticAnalysis_Mixins PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Mixins FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Mixins/TypeInfer.ixx)

target_sources(SPP_SemanticAnalysis_Mixins PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/TypeInfer.cpp)

target_include_directories(SPP_SemanticAnalysis_Mixins PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_SemanticAnalysis_Mixins PRIVATE
        SPP::SemanticAnalysis::Asts
        SPP::SemanticAnalysis::Scoping
        SPP::Utils)

add_library(SPP::SemanticAnalysis::Mixins ALIAS SPP_SemanticAnalysis_Mixins)

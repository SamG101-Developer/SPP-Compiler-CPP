add_library(SPP_SemanticAnalysis_Asts STATIC)

target_sources(SPP_SemanticAnalysis_Asts PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/_ast_members.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/_ast_types.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/AnnotationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ArrayLiteral0ElementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ArrayLiteralNElementsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/AssignmentStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/Ast.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/BinaryExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/BooleanLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CaseExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CaseExpressionBranchAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ClassAttributeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ClassImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ClassPrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ConventionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CoroutinePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FloatLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionCallArgumentGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionCallArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionCallArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterOptionalAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterRequiredAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterSelfAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterVariadicAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionPrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericArgumentGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompParameterOptionalAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompParameterRequiredAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompParameterVariadicAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterInlineConstraintsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterOptionalAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterRequiredAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterVariadicAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericParameterGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GlobalConstantAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/IdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/InnerScopeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/IntegerLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LetStatementInitializedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LetStatementUninitializedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableAttributeBindingAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureArrayAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureObjectAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureSkip1ArgumentAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureSkipNArgumentsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureTupleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableSingleIdentifierAliasAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableSingleIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopConditionBooleanAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopConditionIterableAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopControlFlowStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopElseStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ModuleImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ModulePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerArgumentGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ParenthesizedExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternGuardAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantAttributeBindingAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureArrayAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureObjectAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureSkip1ArgumentAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureSkipNArgumentsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureTupleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantElseAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantElseCaseAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantSingleIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorEarlyReturnAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorFunctionCallAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorMemberAccessAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorNotKeywordAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorStepKeywordAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PinStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RelStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RetStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RootAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/StringLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SubroutinePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupPrototypeExtensionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupPrototypeFunctionsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TokenAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TupleLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeArrayAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeBinaryExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeParenthesizedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypePostfixExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypePostfixOperatorIndexedTypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypePostfixOperatorNestedTypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypePostfixOperatorOptionalTypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeSingleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeTupleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeUnaryExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeUnaryOperatorNamespaceAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/UnaryExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/UnaryExpressionOperatorAsyncAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/UseStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereBlockAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereConstraintsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereConstraintsGroupAst.ixx)

target_sources(SPP_SemanticAnalysis_Asts PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/AnnotationAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArrayLiteral0ElementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ArrayLiteralNElementsAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/AssignmentStatementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Ast.cpp
        ${CMAKE_CURRENT_LIST_DIR}/BinaryExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/BooleanLiteralAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CaseExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CaseExpressionBranchAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClassAttributeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClassImplementationAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClassPrototypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ConventionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CoroutinePrototypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FloatLiteralAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/FunctionCallArgumentGroupAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/FunctionCallArgumentNamedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FunctionCallArgumentUnnamedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FunctionImplementationAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/FunctionParameterGroupAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/FunctionParameterOptionalAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/FunctionParameterRequiredAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FunctionParameterSelfAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/FunctionParameterVariadicAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/FunctionPrototypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericArgumentGroupAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/GenericCompArgumentNamedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericCompArgumentUnnamedAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/GenericCompParameterOptionalAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericCompParameterRequiredAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericCompParameterVariadicAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/GenericTypeArgumentNamedAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/GenericTypeArgumentUnnamedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericTypeParameterInlineConstraintsAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/GenericTypeParameterOptionalAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericTypeParameterRequiredAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericTypeParameterVariadicAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/GenericIdentifierAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenericParameterGroupAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GenExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GlobalConstantAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IdentifierAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/InnerScopeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/IntegerLiteralAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LetStatementInitializedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LetStatementUninitializedAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableAttributeBindingAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableDestructureArrayAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableDestructureObjectAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableDestructureSkip1ArgumentAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableDestructureSkipNArgumentsAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableDestructureTupleAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableSingleIdentifierAliasAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LocalVariableSingleIdentifierAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LoopConditionBooleanAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LoopConditionIterableAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LoopControlFlowStatementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LoopElseStatementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LoopExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModuleImplementationAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ModulePrototypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObjectInitializerAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObjectInitializerArgumentGroupAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObjectInitializerArgumentNamedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObjectInitializerArgumentUnnamedAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ParenthesizedExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternGuardAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantAttributeBindingAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantDestructureArrayAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantDestructureObjectAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantDestructureSkip1ArgumentAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantDestructureSkipNArgumentsAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantDestructureTupleAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantElseAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantElseCaseAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantExpressionAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantLiteralAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PatternVariantSingleIdentifierAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PostfixExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PostfixExpressionOperatorEarlyReturnAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PostfixExpressionOperatorFunctionCallAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PostfixExpressionOperatorMemberAccessAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/PostfixExpressionOperatorNotKeywordAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PostfixExpressionOperatorStepKeywordAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/PinStatementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RelStatementAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/RetStatementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RootAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/StringLiteralAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SubroutinePrototypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SupImplementationAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SupPrototypeExtensionAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/SupPrototypeFunctionsAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TokenAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/TupleLiteralAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TypeArrayAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/TypeBinaryExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TypeParenthesizedAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/TypePostfixExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TypePostfixOperatorIndexedTypeAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/TypePostfixOperatorNestedTypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TypePostfixOperatorOptionalTypeAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TypeSingleAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/TypeTupleAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/TypeUnaryExpressionAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TypeUnaryOperatorNamespaceAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UnaryExpressionAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/UnaryExpressionOperatorAsyncAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/UseStatementAst.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WhereBlockAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/WhereConstraintsAst.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/WhereConstraintsGroupAst.cpp
)

target_include_directories(SPP_SemanticAnalysis_Asts PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts)

target_link_libraries(SPP_SemanticAnalysis_Asts PRIVATE
        magic_enum::magic_enum
        SPP::Compiler
        SPP::SemanticAnalysis::Meta
        SPP::SemanticAnalysis::Mixins)

add_library(SPP::SemanticAnalysis::Asts ALIAS SPP_SemanticAnalysis_Asts)

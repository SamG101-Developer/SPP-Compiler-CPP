export module spp.semantic_analysis.asts.ast_types;
import spp.utils.variant_intrinsics;

using namespace SPP::Utils;


export namespace SPP::SemanticAnalysis::Asts {
    struct Ast;
    struct AnnotationAst;
    struct ArrayLiteral0ElementAst;
    struct ArrayLiteralNElementsAst;
    struct AssignmentStatementAst;
    struct BinaryExpressionAst;
    struct BooleanLiteralAst;
    struct CaseExpressionAst;
    struct ClassAttributeAst;
    struct ClassImplementationAst;
    struct ClassPrototypeAst;
    struct ConventionAst;
    struct CoroutinePrototypeAst;
    struct FloatLiteralAst;
    struct FunctionCallArgumentGroupAst;
    struct FunctionCallArgumentNamedAst;
    struct FunctionCallArgumentUnnamedAst;
    struct FunctionImplementationAst;
    struct FunctionParameterGroupAst;
    struct FunctionParameterOptionalAst;
    struct FunctionParameterRequiredAst;
    struct FunctionParameterSelfAst;
    struct FunctionParameterVariadicAst;
    struct FunctionPrototypeAst;
    struct GenericArgumentGroupAst;
    struct GenericCompArgumentNamedAst;
    struct GenericCompArgumentUnnamedAst;
    struct GenericTypeArgumentNamedAst;
    struct GenericTypeArgumentUnnamedAst;
    struct GenericParameterGroupAst;
    struct GenericTypeParameterInlineConstraintsAst;
    struct GenericCompParameterOptionalAst;
    struct GenericCompParameterRequiredAst;
    struct GenericCompParameterVariadicAst;
    struct GenericTypeParameterOptionalAst;
    struct GenericTypeParameterRequiredAst;
    struct GenericTypeParameterVariadicAst;
    struct GenericIdentifierAst;
    struct GenExpressionAst;
    struct GlobalConstantAst;
    struct IdentifierAst;
    struct InnerScopeAst;
    struct IntegerLiteralAst;
    struct LetStatementInitializedAst;
    struct LetStatementInitializedAst;
    struct LetStatementUninitializedAst;
    struct LocalVariableAttributeBindingAst;
    struct LocalVariableDestructureArrayAst;
    struct LocalVariableDestructureObjectAst;
    struct LocalVariableDestructureSkip1ArgumentAst;
    struct LocalVariableDestructureSkipNArgumentsAst;
    struct LocalVariableDestructureTupleAst;
    struct LocalVariableSingleIdentifierAliasAst;
    struct LocalVariableSingleIdentifierAst;
    struct LoopConditionBooleanAst;
    struct LoopConditionIterableAst;
    struct LoopControlFlowStatementAst;
    struct LoopElseStatementAst;
    struct LoopExpressionAst;
    struct ModuleImplementationAst;
    struct ModulePrototypeAst;
    struct ObjectInitializerAst;
    struct ObjectInitializerArgumentGroupAst;
    struct ObjectInitializerArgumentNamedAst;
    struct ObjectInitializerArgumentUnnamedAst;
    struct ParenthesizedExpressionAst;
    struct CaseExpressionBranchAst;
    struct PatternGuardAst;
    struct PatternVariantAttributeBindingAst;
    struct PatternVariantDestructureArrayAst;
    struct PatternVariantDestructureObjectAst;
    struct PatternVariantDestructureSkip1ArgumentAst;
    struct PatternVariantDestructureSkipNArgumentsAst;
    struct PatternVariantDestructureTupleAst;
    struct PatternVariantElseAst;
    struct PatternVariantElseCaseAst;
    struct PatternVariantExpressionAst;
    struct PatternVariantLiteralAst;
    struct PatternVariantSingleIdentifierAst;
    struct PinStatementAst;
    struct PostfixExpressionAst;
    struct PostfixExpressionOperatorEarlyReturnAst;
    struct PostfixExpressionOperatorFunctionCallAst;
    struct PostfixExpressionOperatorMemberAccessAst;
    struct PostfixExpressionOperatorStepKeywordAst;
    struct PostfixExpressionOperatorNotKeywordAst;
    struct RelStatementAst;
    struct RetStatementAst;
    struct RootAst;
    struct StringLiteralAst;
    struct SubroutinePrototypeAst;
    struct SupImplementationAst;
    struct SupPrototypeAst;
    struct SupPrototypeFunctionsAst;
    struct SupPrototypeExtensionAst;
    struct TokenAst;
    struct TupleLiteralAst;
    struct TypeSingleAst;
    struct TypeTupleAst;
    struct TypeArrayAst;
    struct TypeParenthesizedAst;
    struct TypeUnaryExpressionAst;
    struct TypeUnaryOperatorNamespaceAst;
    struct TypePostfixExpressionAst;
    struct TypePostfixOperatorNestedTypeAst;
    struct TypePostfixOperatorIndexedTypeAst;
    struct TypePostfixOperatorOptionalTypeAst;
    struct TypeBinaryExpressionAst;
    struct UnaryExpressionAst;
    struct UnaryExpressionOperatorAsyncAst;
    struct UseStatementAst;
    struct WhereBlockAst;
    struct WhereConstraintsAst;
    struct WhereConstraintsGroupAst;

    using ArrayLiteralAst = CollapsingVariant<
        ArrayLiteral0ElementAst,
        ArrayLiteralNElementsAst>;

    using ClassMemberAst = CollapsingVariant<
        ClassAttributeAst>;

    using FunctionCallArgumentAst = CollapsingVariant<
        FunctionCallArgumentNamedAst,
        FunctionCallArgumentUnnamedAst>;

    using FunctionParameterAst = CollapsingVariant<
        FunctionParameterSelfAst,
        FunctionParameterVariadicAst,
        FunctionParameterOptionalAst,
        FunctionParameterRequiredAst>;

    using GenericArgumentAst = CollapsingVariant<
        GenericTypeArgumentNamedAst,
        GenericTypeArgumentUnnamedAst,
        GenericCompArgumentNamedAst,
        GenericCompArgumentUnnamedAst>;

    using GenericParameterAst = CollapsingVariant<
        GenericTypeParameterVariadicAst,
        GenericTypeParameterOptionalAst,
        GenericTypeParameterRequiredAst,
        GenericCompParameterVariadicAst,
        GenericCompParameterOptionalAst,
        GenericCompParameterRequiredAst>;

    using LetStatementAst = CollapsingVariant<
        LetStatementInitializedAst,
        LetStatementUninitializedAst>;

    using LocalVariableAst = CollapsingVariant<
        LocalVariableDestructureArrayAst,
        LocalVariableDestructureTupleAst,
        LocalVariableDestructureObjectAst,
        LocalVariableSingleIdentifierAst>;

    using LocalVariableNestedForDestructureArrayAst = CollapsingVariant<
        LocalVariableDestructureArrayAst,
        LocalVariableDestructureTupleAst,
        LocalVariableDestructureObjectAst,
        LocalVariableSingleIdentifierAst,
        LocalVariableDestructureSkip1ArgumentAst,
        LocalVariableDestructureSkipNArgumentsAst>;

    using LocalVariableNestedForDestructureTupleAst = CollapsingVariant<
        LocalVariableDestructureArrayAst,
        LocalVariableDestructureTupleAst,
        LocalVariableDestructureObjectAst,
        LocalVariableSingleIdentifierAst,
        LocalVariableDestructureSkip1ArgumentAst,
        LocalVariableDestructureSkipNArgumentsAst>;

    using LocalVariableNestedForDestructureObjectAst = CollapsingVariant<
        LocalVariableAttributeBindingAst,
        LocalVariableSingleIdentifierAst,
        LocalVariableDestructureSkipNArgumentsAst>;

    using LocalVariableNestedForAttributeBindingAst = CollapsingVariant<
        LocalVariableDestructureArrayAst,
        LocalVariableDestructureTupleAst,
        LocalVariableDestructureObjectAst,
        LocalVariableSingleIdentifierAst>;

    using LoopConditionAst = CollapsingVariant<
        LoopConditionIterableAst,
        LoopConditionBooleanAst>;

    using SupUseStatementAst = UseStatementAst;

    using ModuleMemberAst = CollapsingVariant<
        CoroutinePrototypeAst,
        SubroutinePrototypeAst,
        ClassPrototypeAst,
        SupPrototypeFunctionsAst,
        SupPrototypeExtensionAst,
        UseStatementAst,
        GlobalConstantAst>;

    using ObjectInitializerArgumentAst = CollapsingVariant<
        ObjectInitializerArgumentNamedAst,
        ObjectInitializerArgumentUnnamedAst>;

    using PatternVariantAst = CollapsingVariant<
        PatternVariantElseAst,
        PatternVariantExpressionAst,
        PatternVariantLiteralAst,
        PatternVariantDestructureArrayAst,
        PatternVariantDestructureObjectAst,
        PatternVariantDestructureTupleAst,
        PatternVariantDestructureSkip1ArgumentAst,
        PatternVariantSingleIdentifierAst>;

    using PatternGroupDestructureAst = CollapsingVariant<
        PatternVariantDestructureArrayAst,
        PatternVariantDestructureObjectAst,
        PatternVariantDestructureTupleAst>;

    using PatternVariantNestedForDestructureArrayAst = CollapsingVariant<
        PatternVariantDestructureArrayAst,
        PatternVariantDestructureObjectAst,
        PatternVariantDestructureTupleAst,
        PatternVariantDestructureSkipNArgumentsAst,
        PatternVariantDestructureSkip1ArgumentAst,
        PatternVariantLiteralAst,
        PatternVariantSingleIdentifierAst>;

    using PatternVariantNestedForDestructureObjectAst = CollapsingVariant<
        PatternVariantAttributeBindingAst,
        PatternVariantDestructureSkipNArgumentsAst,
        PatternVariantSingleIdentifierAst>;

    using PatternVariantNestedForDestructureTupleAst = CollapsingVariant<
        PatternVariantDestructureArrayAst,
        PatternVariantDestructureObjectAst,
        PatternVariantDestructureTupleAst,
        PatternVariantDestructureSkipNArgumentsAst,
        PatternVariantDestructureSkip1ArgumentAst,
        PatternVariantLiteralAst,
        PatternVariantSingleIdentifierAst>;

    using PatternVariantNestedForAttributeBindingAst = CollapsingVariant<
        PatternVariantDestructureArrayAst,
        PatternVariantDestructureObjectAst,
        PatternVariantDestructureTupleAst,
        PatternVariantLiteralAst>;

    using PostfixExpressionOperatorAst = CollapsingVariant<
        PostfixExpressionOperatorEarlyReturnAst,
        PostfixExpressionOperatorFunctionCallAst,
        PostfixExpressionOperatorMemberAccessAst,
        PostfixExpressionOperatorStepKeywordAst,
        PostfixExpressionOperatorNotKeywordAst>;

    using TypePostfixOperatorAst = CollapsingVariant<
        TypePostfixOperatorNestedTypeAst,
        TypePostfixOperatorIndexedTypeAst,
        TypePostfixOperatorOptionalTypeAst>;

    using TypeAst = CollapsingVariant<
        TypeSingleAst,
        TypeUnaryExpressionAst,
        TypeBinaryExpressionAst,
        TypePostfixExpressionAst>;

    using TypePrimaryExpressionAst = CollapsingVariant<
        TypeArrayAst,
        TypeTupleAst,
        TypeParenthesizedAst,
        TypeSingleAst>;

    using TypeUnaryOperatorAst = CollapsingVariant<
        TypeUnaryOperatorNamespaceAst>;

    using LiteralAst = CollapsingVariant<
        FloatLiteralAst,
        IntegerLiteralAst,
        StringLiteralAst,
        BooleanLiteralAst,
        ArrayLiteralAst,
        TupleLiteralAst>;

    using PrimaryExpressionAst = CollapsingVariant<
        LiteralAst,
        ObjectInitializerAst,
        ParenthesizedExpressionAst,
        TypeAst,
        CaseExpressionAst,
        LoopExpressionAst,
        GenExpressionAst,
        InnerScopeAst,
        IdentifierAst,
        TokenAst>;

    using ExpressionAst = CollapsingVariant<
        BinaryExpressionAst,
        PostfixExpressionAst,
        UnaryExpressionAst,
        PrimaryExpressionAst>;

    using StatementAst = CollapsingVariant<
        UseStatementAst,
        LetStatementAst,
        RetStatementAst,
        LoopControlFlowStatementAst,
        PinStatementAst,
        RelStatementAst,
        AssignmentStatementAst,
        ExpressionAst>;

    using FunctionMemberAst = StatementAst;

    using SupMemberAst = CollapsingVariant<
        SubroutinePrototypeAst,
        CoroutinePrototypeAst,
        // SupPrototypeExtensionAst,
        SupUseStatementAst>;

    using UnaryExpressionOperatorAst = UnaryExpressionOperatorAsyncAst;

    using LoopControlFlowFinalActionAst = CollapsingVariant<
        TokenAst,
        ExpressionAst>;

    using PostfixExpressionOperatorMemberAccessFieldIdentifierAst = CollapsingVariant<
        IdentifierAst,
        TokenAst>;

    using ObjectInitializerArgumentNameAst = CollapsingVariant<
        IdentifierAst,
        TokenAst>;
}

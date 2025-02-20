module;

#include <format>
#include <utility>
#include <memory>
#include <functional>
#include <locale>
#include <variant>
#include <magic_enum/magic_enum.hpp>

module spp.syntactic_analysis.parser;
import spp.lexical_analysis.tokens;
import spp.semantic_analysis.asts.ast;
import spp.semantic_analysis.asts.annotation_ast;
import spp.semantic_analysis.asts.case_expression_ast;
import spp.semantic_analysis.asts.class_attribute_ast;
import spp.semantic_analysis.asts.class_prototype_ast;
import spp.semantic_analysis.asts.class_implementation_ast;
import spp.semantic_analysis.asts.convention_ast;
import spp.semantic_analysis.asts.coroutine_prototype_ast;
import spp.semantic_analysis.asts.function_call_argument_group_ast;
import spp.semantic_analysis.asts.function_call_argument_named_ast;
import spp.semantic_analysis.asts.function_call_argument_unnamed_ast;
import spp.semantic_analysis.asts.function_implementation_ast;
import spp.semantic_analysis.asts.function_parameter_group_ast;
import spp.semantic_analysis.asts.function_parameter_optional_ast;
import spp.semantic_analysis.asts.function_parameter_required_ast;
import spp.semantic_analysis.asts.function_parameter_self_ast;
import spp.semantic_analysis.asts.function_parameter_variadic_ast;
import spp.semantic_analysis.asts.function_prototype_ast;
import spp.semantic_analysis.asts.generic_argument_group_ast;
import spp.semantic_analysis.asts.generic_type_argument_named_ast;
import spp.semantic_analysis.asts.generic_type_argument_unnamed_ast;
import spp.semantic_analysis.asts.generic_comp_argument_named_ast;
import spp.semantic_analysis.asts.generic_comp_argument_unnamed_ast;
import spp.semantic_analysis.asts.generic_parameter_group_ast;
import spp.semantic_analysis.asts.identifier_ast;
import spp.semantic_analysis.asts.loop_expression_ast;
import spp.semantic_analysis.asts.module_prototype_ast;
import spp.semantic_analysis.asts.module_implementation_ast;
import spp.semantic_analysis.asts.parenthesized_expression_ast;
import spp.semantic_analysis.asts.root_ast;
import spp.semantic_analysis.asts.subroutine_prototype_ast;
import spp.semantic_analysis.asts.sup_prototype_functions_ast;
import spp.semantic_analysis.asts.sup_prototype_extension_ast;
import spp.semantic_analysis.asts.sup_implementation_ast;
import spp.semantic_analysis.asts.token_ast;
import spp.semantic_analysis.asts.type_single_ast;
import spp.syntactic_analysis.parser_error;
import genex.algorithms.accumulate;
import genex.views.reverse;
import genex.generator;


using namespace SPP::SemanticAnalysis;
using namespace SPP::LexicalAnalysis;


auto SPP::SyntacticAnalysis::Parser::parse() -> Asts::RootAst {
    try {
        using namespace SemanticAnalysis;
        const auto c0 = get_current_pos();
        auto p1 = parse_once(&Parser::parse_root);
        auto p2 = parse_once(&Parser::parse_eof);
        return {c0, std::move(p1), std::move(p2)};
    }

    catch (Errors::SyntaxError &e) {
        e.throw_(error_formatter);
    }
}


template <typename... Args, std::invocable<SPP::SyntacticAnalysis::Parser*, Args...> F>
auto SPP::SyntacticAnalysis::Parser::parse_once(F &&parser_rule, Args &&... args) -> std::invoke_result_t<F, Parser*, Args...> {
    return std::invoke(std::forward<F>(parser_rule), this, std::forward<Args>(args)...);
}

auto SPP::SyntacticAnalysis::Parser::parse_root() -> std::unique_ptr<Asts::ModulePrototypeAst> {
    auto p1 = parse_once(&Parser::parse_module_prototype);
    auto _a = parse_once(&Parser::parse_eof);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_module_prototype() -> std::unique_ptr<Asts::ModulePrototypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_module_implementation);
    return std::make_unique<Asts::ModulePrototypeAst>(c1, std::move(p1));
}

auto SPP::SyntacticAnalysis::Parser::parse_module_implementation() -> std::unique_ptr<Asts::ModuleImplementationAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_0_or_more(&Parser::parse_module_member, &Parser::parse_nothing);
    return std::make_unique<Asts::ModuleImplementationAst>(c1, std::move(p1));
}

auto SPP::SyntacticAnalysis::Parser::parse_module_member() -> UniqueVariant<Asts::ModuleMemberAst> {
    auto p1 = parse_alternate(
        &Parser::parse_coroutine_prototype,
        &Parser::parse_subroutine_prototype,
        &Parser::parse_class_prototype,
        &Parser::parse_sup_prototype_functions,
        &Parser::parse_sup_prototype_extension,
        &Parser::parse_global_use_statement,
        &Parser::parse_comp_global_constant);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_class_prototype() -> std::unique_ptr<Asts::ClassPrototypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_keyword_cls);
    auto p3 = parse_once(&Parser::parse_upper_identifier);
    auto p4 = parse_optional(&Parser::parse_generic_parameters);
    auto p5 = parse_optional(&Parser::parse_where_block);
    auto p6 = parse_once(&Parser::parse_class_implementation);
    return std::make_unique<Asts::ClassPrototypeAst>(c1, std::move(p1), std::move(p2), Asts::TypeSingleAst::from(*p3), std::move(p4), std::move(p5), std::move(p6));
}

auto SPP::SyntacticAnalysis::Parser::parse_class_implementation() -> std::unique_ptr<Asts::ClassImplementationAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_curly_brace);
    auto p2 = parse_0_or_more(&Parser::parse_class_member, &Parser::parse_nothing);
    auto p3 = parse_once(&Parser::parse_token_right_curly_brace);
    return std::make_unique<Asts::ClassImplementationAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_class_member() -> UniqueVariant<Asts::ClassMemberAst> {
    auto p1 = parse_alternate(
        &Parser::parse_class_attribute);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_class_attribute() -> std::unique_ptr<Asts::ClassAttributeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_identifier);
    auto p3 = parse_once(&Parser::parse_token_colon);
    auto p4 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::ClassAttributeAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4));
}

auto SPP::SyntacticAnalysis::Parser::parse_sup_prototype_extension() -> std::unique_ptr<Asts::SupPrototypeExtensionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_sup);
    auto p2 = parse_optional(&Parser::parse_generic_parameters);
    auto p3 = parse_once(&Parser::parse_type);
    auto p4 = parse_once(&Parser::parse_keyword_ext);
    auto p5 = parse_once(&Parser::parse_type);
    auto p6 = parse_optional(&Parser::parse_where_block);
    auto p7 = parse_once(&Parser::parse_sup_implementation);
    return std::make_unique<Asts::SupPrototypeExtensionAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5), std::move(p6), std::move(p7));
}

auto SPP::SyntacticAnalysis::Parser::parse_sup_prototype_functions() -> std::unique_ptr<Asts::SupPrototypeFunctionsAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_sup);
    auto p2 = parse_optional(&Parser::parse_generic_parameters);
    auto p3 = parse_once(&Parser::parse_type);
    auto p4 = parse_optional(&Parser::parse_where_block);
    auto p5 = parse_once(&Parser::parse_sup_implementation);
    return std::make_unique<Asts::SupPrototypeFunctionsAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5));
}

auto SPP::SyntacticAnalysis::Parser::parse_sup_implementation() -> std::unique_ptr<Asts::SupImplementationAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_curly_brace);
    auto p2 = parse_0_or_more(&Parser::parse_sup_member, &Parser::parse_nothing);
    auto p3 = parse_once(&Parser::parse_token_right_curly_brace);
    return std::make_unique<Asts::SupImplementationAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_sup_member() -> UniqueVariant<Asts::SupMemberAst> {
    auto p1 = parse_alternate(
        &Parser::parse_sup_subroutine_prototype,
        &Parser::parse_sup_coroutine_prototype,
        &Parser::parse_sup_use_statement);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_sup_subroutine_prototype() -> std::unique_ptr<Asts::SubroutinePrototypeAst> {
    auto p1 = parse_once(&Parser::parse_subroutine_prototype);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_sup_coroutine_prototype() -> std::unique_ptr<Asts::CoroutinePrototypeAst> {
    auto p1 = parse_once(&Parser::parse_coroutine_prototype);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_sup_use_statement() -> std::unique_ptr<Asts::SupUseStatementAst> {
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_use_statement);
    p2->annotations = p1;
    return p2;
}

auto SPP::SyntacticAnalysis::Parser::parse_subroutine_prototype() -> std::unique_ptr<Asts::SubroutinePrototypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_keyword_fun);
    auto p3 = parse_once(&Parser::parse_identifier);
    auto p4 = parse_optional(&Parser::parse_generic_parameters);
    auto p5 = parse_once(&Parser::parse_function_parameters);
    auto p6 = parse_once(&Parser::parse_token_rightward_arrow);
    auto p7 = parse_once(&Parser::parse_type);
    auto p8 = parse_optional(&Parser::parse_where_block);
    auto p9 = parse_once(&Parser::parse_function_implementation);
    return std::make_unique<Asts::FunctionPrototypeAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5), std::move(p6), std::move(p7), std::move(p8), std::move(p9));
}

auto SPP::SyntacticAnalysis::Parser::parse_coroutine_prototype() -> std::unique_ptr<Asts::CoroutinePrototypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_keyword_cor);
    auto p3 = parse_once(&Parser::parse_identifier);
    auto p4 = parse_optional(&Parser::parse_generic_parameters);
    auto p5 = parse_once(&Parser::parse_function_parameters);
    auto p6 = parse_once(&Parser::parse_token_rightward_arrow);
    auto p7 = parse_once(&Parser::parse_type);
    auto p8 = parse_optional(&Parser::parse_where_block);
    auto p9 = parse_once(&Parser::parse_function_implementation);
    return std::make_unique<Asts::FunctionPrototypeAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5), std::move(p6), std::move(p7), std::move(p8), std::move(p9));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_implementation() -> std::unique_ptr<Asts::FunctionImplementationAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_curly_brace);
    auto p2 = parse_0_or_more(&Parser::parse_function_member, &Parser::parse_nothing);
    auto p3 = parse_once(&Parser::parse_token_right_curly_brace);
    return std::make_unique<Asts::FunctionImplementationAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_member() -> UniqueVariant<Asts::FunctionMemberAst> {
    auto p1 = parse_once(&Parser::parse_statement);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_function_call_arguments() -> std::unique_ptr<Asts::FunctionCallArgumentGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_0_or_more(&Parser::parse_function_call_argument, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::FunctionCallArgumentGroupAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_call_argument() -> UniqueVariant<Asts::FunctionCallArgumentAst> {
    auto p1 = parse_alternate(
        &Parser::parse_function_call_argument_named,
        &Parser::parse_function_call_argument_unnamed);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_function_call_argument_unnamed() -> std::unique_ptr<Asts::FunctionCallArgumentUnnamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_convention);
    auto p2 = parse_optional(&Parser::parse_token_double_dot);
    auto p3 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::FunctionCallArgumentUnnamedAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_call_argument_named() -> std::unique_ptr<Asts::FunctionCallArgumentNamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_convention);
    auto p4 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::FunctionCallArgumentNamedAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_parameters() -> std::unique_ptr<Asts::FunctionParameterGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_0_or_more(&Parser::parse_function_parameter, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::FunctionParameterGroupAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_parameter() -> UniqueVariant<Asts::FunctionParameterAst> {
    auto p1 = parse_alternate(
        &Parser::parse_function_parameter_self,
        &Parser::parse_function_parameter_variadic,
        &Parser::parse_function_parameter_optional,
        &Parser::parse_function_parameter_required);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_function_parameter_self() -> std::unique_ptr<Asts::FunctionParameterSelfAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_keyword_mut);
    auto p2 = parse_once(&Parser::parse_convention);
    auto p3 = parse_once(&Parser::parse_self_identifier);
    return std::make_unique<Asts::FunctionParameterSelfAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_parameter_required() -> std::unique_ptr<Asts::FunctionParameterRequiredAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_local_variable);
    auto p2 = parse_once(&Parser::parse_token_colon);
    auto p3 = parse_once(&Parser::parse_convention);
    auto p4 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::FunctionParameterRequiredAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_parameter_optional() -> std::unique_ptr<Asts::FunctionParameterOptionalAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_local_variable);
    auto p2 = parse_once(&Parser::parse_token_colon);
    auto p3 = parse_once(&Parser::parse_convention);
    auto p4 = parse_once(&Parser::parse_type);
    auto p5 = parse_once(&Parser::parse_token_assign);
    auto p6 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::FunctionParameterOptionalAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5), std::move(p6));
}

auto SPP::SyntacticAnalysis::Parser::parse_function_parameter_variadic() -> std::unique_ptr<Asts::FunctionParameterVariadicAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_double_dot);
    auto p2 = parse_once(&Parser::parse_local_variable);
    auto p3 = parse_once(&Parser::parse_token_colon);
    auto p4 = parse_once(&Parser::parse_convention);
    auto p5 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::FunctionParameterVariadicAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_arguments() -> std::unique_ptr<Asts::GenericArgumentGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_0_or_more(&Parser::parse_generic_argument, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::GenericArgumentGroupAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_argument() -> UniqueVariant<Asts::GenericArgumentAst> {
    auto p1 = parse_alternate(
        &Parser::parse_generic_argument_type_named,
        &Parser::parse_generic_argument_type_unnamed,
        &Parser::parse_generic_argument_comp_named,
        &Parser::parse_generic_argument_comp_unnamed);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_argument_type_named() -> std::unique_ptr<Asts::GenericTypeArgumentNamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_upper_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::GenericTypeArgumentNamedAst>(c1, Asts::TypeSingleAst::from(*p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_argument_type_unnamed() -> std::unique_ptr<Asts::GenericTypeArgumentUnnamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::GenericTypeArgumentUnnamedAst>(c1, std::move(p1));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_argument_comp_named() -> std::unique_ptr<Asts::GenericCompArgumentNamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_comp_value);
    return std::make_unique<Asts::GenericCompArgumentNamedAst>(c1, Asts::TypeSingleAst::from(*p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_argument_comp_unnamed() -> std::unique_ptr<Asts::GenericCompArgumentUnnamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_comp_value);
    return std::make_unique<Asts::GenericCompArgumentUnnamedAst>(c1, std::move(p1));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameters() -> std::unique_ptr<Asts::GenericParameterGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_0_or_more(&Parser::parse_generic_parameter, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::GenericParameterGroupAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter() -> UniqueVariant<Asts::GenericParameterAst> {
    auto p1 = parse_alternate(
        &Parser::parse_generic_parameter_type_variadic,
        &Parser::parse_generic_parameter_type_optional,
        &Parser::parse_generic_parameter_type_required,
        &Parser::parse_generic_parameter_comp_variadic,
        &Parser::parse_generic_parameter_comp_optional,
        &Parser::parse_generic_parameter_comp_required);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter_type_required() -> std::unique_ptr<Asts::GenericTypeParameterRequiredAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_upper_identifier);
    auto p2 = parse_optional(&Parser::parse_generic_inline_constraints);
    return std::make_unique<Asts::GenericTypeParameterRequiredAst>(c1, Asts::TypeSingleAst::from(*p1), p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter_type_optional() -> std::unique_ptr<Asts::GenericTypeParameterOptionalAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_upper_identifier);
    auto p2 = parse_optional(&Parser::parse_generic_inline_constraints);
    auto p3 = parse_once(&Parser::parse_token_assign);
    auto p4 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::GenericTypeParameterOptionalAst>(c1, Asts::TypeSingleAst::from(*p1), p2, p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter_type_variadic() -> std::unique_ptr<Asts::GenericTypeParameterVariadicAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_double_dot);
    auto p2 = parse_once(&Parser::parse_upper_identifier);
    auto p3 = parse_optional(&Parser::parse_generic_inline_constraints);
    return std::make_unique<Asts::GenericTypeParameterVariadicAst>(c1, p1, Asts::TypeSingleAst::from(*p2), p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter_comp_required() -> std::unique_ptr<Asts::GenericCompParameterRequiredAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_cmp);
    auto p2 = parse_once(&Parser::parse_identifier);
    auto p3 = parse_once(&Parser::parse_token_colon);
    auto p4 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::GenericCompParameterRequiredAst>(c1, p1, Asts::TypeSingleAst::from(*p2), p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter_comp_optional() -> std::unique_ptr<Asts::GenericCompParameterOptionalAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_cmp);
    auto p2 = parse_once(&Parser::parse_identifier);
    auto p3 = parse_once(&Parser::parse_token_colon);
    auto p4 = parse_once(&Parser::parse_type);
    auto p5 = parse_once(&Parser::parse_token_assign);
    auto p6 = parse_once(&Parser::parse_comp_value);
    return std::make_unique<Asts::GenericCompParameterOptionalAst>(c1, p1, Asts::TypeSingleAst::from(*p2), p3, p4, p5, p6);
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_parameter_comp_variadic() -> std::unique_ptr<Asts::GenericCompParameterVariadicAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_cmp);
    auto p2 = parse_once(&Parser::parse_token_double_dot);
    auto p3 = parse_once(&Parser::parse_identifier);
    auto p4 = parse_once(&Parser::parse_token_colon);
    auto p5 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::GenericCompParameterVariadicAst>(c1, p1, p2, Asts::TypeSingleAst::from(*p3), p4, p5);
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_inline_constraints() -> std::unique_ptr<Asts::GenericTypeParameterInlineConstraintsAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_colon);
    auto p2 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::GenericTypeParameterInlineConstraintsAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_where_block() -> std::unique_ptr<Asts::WhereBlockAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_where);
    auto p2 = parse_once(&Parser::parse_where_block_constraints_group);
    return std::make_unique<Asts::WhereBlockAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_where_block_constraints_group() -> std::unique_ptr<Asts::WhereConstraintsGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_1_or_more(&Parser::parse_where_block_constraints, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::WhereConstraintsGroupAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_where_block_constraints() -> std::unique_ptr<Asts::WhereConstraintsAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_1_or_more(&Parser::parse_type, Parser::parse_token_comma);
    auto p2 = parse_once(&Parser::parse_token_colon);
    auto p3 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::WhereConstraintsAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_annotation() -> std::unique_ptr<Asts::AnnotationAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_at);
    auto p2 = parse_once(&Parser::parse_identifier);
    return std::make_unique<Asts::AnnotationAst>(c1, std::move(p1), std::move(p2));
}

auto SPP::SyntacticAnalysis::Parser::parse_expression() -> UniqueVariant<Asts::ExpressionAst> {
    auto p1 = parse_once(&Parser::parse_binary_expression_precedence_level_1);
    return p1;
}

template <std::invocable<SPP::SyntacticAnalysis::Parser*> A1, std::invocable<SPP::SyntacticAnalysis::Parser*> A2>
auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_n_rhs(A1&& op, A2&& rhs) -> std::pair<std::unique_ptr<Asts::TokenAst>, UniqueVariant<Asts::ExpressionAst>> {
    auto p1 = parse_once(op);
    auto p2 = parse_once(rhs);
    return std::make_pair(p1, p2);
}

template <std::invocable<SPP::SyntacticAnalysis::Parser*> A1, std::invocable<SPP::SyntacticAnalysis::Parser*> A2, std::invocable<SPP::SyntacticAnalysis::Parser*> A3>
auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_n(A1 &&lhs, A2 &&op, A3 &&rhs) -> UniqueVariant<Asts::ExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(lhs);
    auto p2 = parse_optional([op, rhs]<typename T>(T&& s) { Parser::parse_binary_expression_precedence_level_n_rhs(s, op, rhs); });
    return p2 ? std::make_unique<Asts::BinaryExpressionAst>(c1, p1, p2.first, p2.second) : p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_1() -> UniqueVariant<Asts::ExpressionAst> {
    return parse_binary_expression_precedence_level_n(&Parser::parse_binary_expression_precedence_level_2, &Parser::parse_binary_op_precedence_level_1, &Parser::parse_binary_expression_precedence_level_1);
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_2() -> UniqueVariant<Asts::ExpressionAst> {
    return parse_binary_expression_precedence_level_n(&Parser::parse_binary_expression_precedence_level_3, &Parser::parse_binary_op_precedence_level_2, &Parser::parse_binary_expression_precedence_level_2);
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_3() -> UniqueVariant<Asts::ExpressionAst> {
    return parse_binary_expression_precedence_level_n(&Parser::parse_binary_expression_precedence_level_4, &Parser::parse_binary_op_precedence_level_3, &Parser::parse_pattern_group_destructure);
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_4() -> UniqueVariant<Asts::ExpressionAst> {
    return parse_binary_expression_precedence_level_n(&Parser::parse_binary_expression_precedence_level_5, &Parser::parse_binary_op_precedence_level_4, &Parser::parse_binary_expression_precedence_level_4);
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_5() -> UniqueVariant<Asts::ExpressionAst> {
    return parse_binary_expression_precedence_level_n(&Parser::parse_binary_expression_precedence_level_6, &Parser::parse_binary_op_precedence_level_5, &Parser::parse_binary_expression_precedence_level_5);
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_expression_precedence_level_6() -> UniqueVariant<Asts::ExpressionAst> {
    return parse_binary_expression_precedence_level_n(&Parser::parse_unary_expression, &Parser::parse_binary_op_precedence_level_6, &Parser::parse_binary_expression_precedence_level_6);
}

auto SPP::SyntacticAnalysis::Parser::parse_unary_expression() -> UniqueVariant<Asts::ExpressionAst> {
    auto p1 = parse_0_or_more(&Parser::parse_unary_op, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_postfix_expression);
    return std::move(genex::algorithms::accumulate(p1 | genex::views::reverse, p2, []<typename A, typename T>(A &&acc, T &&elem) -> std::unique_ptr<Asts::UnaryExpressionAst> {
        return std::make_unique<Asts::UnaryExpressionAst>(acc->pos, std::forward<T>(elem), std::forward<A>(acc));
    }));
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_expression() -> UniqueVariant<Asts::ExpressionAst> {
    auto p1 = parse_once(&Parser::parse_primary_expression);
    auto p2 = parse_0_or_more(&Parser::parse_postfix_op, &Parser::parse_nothing);
    return std::move(genex::algorithms::accumulate(p2, p1, []<typename A, typename T>(A &&acc, T &&elem) -> std::unique_ptr<Asts::PostfixExpressionAst> {
        return std::make_unique<Asts::PostfixExpressionAst>(acc->pos, std::forward<T>(elem), std::forward<A>(acc));
    }));
}

auto SPP::SyntacticAnalysis::Parser::parse_primary_expression() -> UniqueVariant<Asts::ExpressionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal,
        &Parser::parse_object_initializer,
        &Parser::parse_parenthesized_expression,
        &Parser::parse_type,
        &Parser::parse_case_expression,
        &Parser::parse_loop_expression,
        &Parser::parse_gen_expression,
        &Parser::parse_inner_scope,
        &Parser::parse_self_identifier,
        &Parser::parse_identifier,
        &Parser::parse_fold_expression);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_parenthesized_expression() -> std::unique_ptr<Asts::ParenthesizedExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_once(&Parser::parse_expression);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::ParenthesizedExpressionAst>(c1, std::move(p1), std::move(p2), std::move(p3));
}

auto SPP::SyntacticAnalysis::Parser::parse_self_identifier() -> std::unique_ptr<Asts::IdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_self_val);
    return std::make_unique<Asts::IdentifierAst>(c1, std::move(p1->token_data));
}

auto SPP::SyntacticAnalysis::Parser::parse_fold_expression() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_once(&Parser::parse_token_double_dot);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_case_expression() -> std::unique_ptr<Asts::CaseExpressionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_case_expression_patterns,
        &Parser::parse_case_expression_simple);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_case_expression_patterns() -> std::unique_ptr<Asts::CaseExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_case);
    auto p2 = parse_once(&Parser::parse_expression);
    auto p3 = parse_once(&Parser::parse_keyword_of);
    auto p4 = parse_1_or_more(&Parser::parse_case_expression_branch, &Parser::parse_nothing);
    return std::make_unique<Asts::CaseExpressionAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4));
}

auto SPP::SyntacticAnalysis::Parser::parse_case_expression_simple() -> std::unique_ptr<Asts::CaseExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_case);
    auto p2 = parse_once(&Parser::parse_expression);
    auto p3 = parse_once(&Parser::parse_inner_scope);
    auto p4 = parse_0_or_more(&Parser::parse_case_expression_branch_simple, &Parser::parse_nothing);
    return Asts::CaseExpressionAst::from_simple(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4));
}

auto SPP::SyntacticAnalysis::Parser::parse_loop_expression() -> std::unique_ptr<Asts::LoopExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_loop);
    auto p2 = parse_once(&Parser::parse_loop_expression_condition);
    auto p3 = parse_once(&Parser::parse_inner_scope);
    auto p4 = parse_optional(&Parser::parse_loop_else_statement);
    return std::make_unique<Asts::LoopExpressionAst>(c1, std::move(p1), std::move(p2), std::move(p3), std::move(p4));
}

auto SPP::SyntacticAnalysis::Parser::parse_loop_expression_condition() -> UniqueVariant<Asts::LoopConditionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_loop_expression_condition_iterable,
        &Parser::parse_loop_expression_condition_boolean);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_loop_expression_condition_boolean() -> std::unique_ptr<Asts::LoopConditionBooleanAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::LoopConditionBooleanAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_loop_expression_condition_iterable() -> std::unique_ptr<Asts::LoopConditionIterableAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_local_variable);
    auto p2 = parse_once(&Parser::parse_keyword_in);
    auto p3 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::LoopConditionIterableAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_loop_else_statement() -> std::unique_ptr<Asts::LoopElseStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_else);
    auto p2 = parse_once(&Parser::parse_inner_scope);
    return std::make_unique<Asts::LoopElseStatementAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_gen_expression() -> std::unique_ptr<Asts::GenExpressionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_gen_expression_unroll,
        &Parser::parse_gen_expression_normal);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_gen_expression_normal() -> std::unique_ptr<Asts::GenExpressionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_gen_expression_normal_with_expression,
        &Parser::parse_gen_expression_normal_no_expression);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_gen_expression_normal_no_expression() -> std::unique_ptr<Asts::GenExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_gen);
    return std::make_unique<Asts::GenExpressionAst>(c1, p1, std::nullopt, Asts::ConventionAst::mov(c1), std::nullopt);
}

auto SPP::SyntacticAnalysis::Parser::parse_gen_expression_normal_with_expression() -> std::unique_ptr<Asts::GenExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_gen);
    auto p2 = parse_once(&Parser::parse_convention);
    auto p3 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::GenExpressionAst>(c1, p1, std::nullopt, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_gen_expression_unroll() -> std::unique_ptr<Asts::GenExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_gen);
    auto p2 = parse_once(&Parser::parse_keyword_with);
    auto p3 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::GenExpressionAst>(c1, p1, p2, Asts::ConventionAst::mov(c1), p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_ret_statement() -> std::unique_ptr<Asts::RetStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_ret);
    auto p2 = parse_optional(&Parser::parse_expression);
    return std::make_unique<Asts::RetStatementAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_exit_statement() -> std::unique_ptr<Asts::LoopControlFlowStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_1_or_more(&Parser::parse_keyword_exit, &Parser::parse_nothing);
    auto p2 = parse_optional(&Parser::parse_exit_statement_final_action);
    return std::make_unique<Asts::LoopControlFlowStatementAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_exit_statement_final_action() -> std::unique_ptr<Asts::LoopControlFlowFinalActionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_keyword_skip,
        &Parser::parse_expression);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_skip_statement() -> std::unique_ptr<Asts::LoopControlFlowStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_1_or_more(&Parser::parse_keyword_skip, &Parser::parse_nothing);
    return std::make_unique<Asts::LoopControlFlowStatementAst>(c1, p1, std::nullopt);
}

auto SPP::SyntacticAnalysis::Parser::parse_pin_statement() -> std::unique_ptr<Asts::PinStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_pin);
    auto p2 = parse_1_or_more(&Parser::parse_expression, &Parser::parse_token_comma);
    return std::make_unique<Asts::PinStatementAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_rel_statement() -> std::unique_ptr<Asts::RelStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_rel);
    auto p2 = parse_1_or_more(&Parser::parse_expression, &Parser::parse_token_comma);
    return std::make_unique<Asts::RelStatementAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_inner_scope() -> std::unique_ptr<Asts::InnerScopeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_curly_brace);
    auto p2 = parse_0_or_more(&Parser::parse_statement, &Parser::parse_nothing);
    auto p3 = parse_once(&Parser::parse_token_right_curly_brace);
    return std::make_unique<Asts::InnerScopeAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_statement() -> UniqueVariant<Asts::StatementAst> {
    auto p1 = parse_alternate(
        &Parser::parse_use_statement,
        &Parser::parse_let_statement,
        &Parser::parse_ret_statement,
        &Parser::parse_exit_statement,
        &Parser::parse_skip_statement,
        &Parser::parse_pin_statement,
        &Parser::parse_rel_statement,
        &Parser::parse_assignment_statement,
        &Parser::parse_expression);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_global_use_statement() -> std::unique_ptr<Asts::UseStatementAst> {
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_use_statement);
    p2->annotations = p1;
    return p2;
}

auto SPP::SyntacticAnalysis::Parser::parse_use_statement() -> std::unique_ptr<Asts::UseStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_use);
    auto p2 = parse_once(&Parser::parse_upper_identifier);
    auto p3 = parse_optional(&Parser::parse_generic_parameters);
    auto p4 = parse_once(&Parser::parse_token_assign);
    auto p5 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::UseStatementAst>(c1, {}, p1, Asts::TypeSingleAst::from(*p2), p3, p4, p5);
}

auto SPP::SyntacticAnalysis::Parser::parse_comp_global_constant() -> std::unique_ptr<Asts::GlobalConstantAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_0_or_more(&Parser::parse_annotation, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_keyword_cmp);
    auto p3 = parse_once(&Parser::parse_identifier);
    auto p4 = parse_once(&Parser::parse_token_colon);
    auto p5 = parse_once(&Parser::parse_type);
    auto p6 = parse_once(&Parser::parse_token_assign);
    auto p7 = parse_once(&Parser::parse_comp_value);
    return std::make_unique<Asts::GlobalConstantAst>(c1, p1, p2, p3, p4, p5, p6, p7);
}

auto SPP::SyntacticAnalysis::Parser::parse_let_statement() -> UniqueVariant<Asts::LetStatementAst> {
    auto p1 = parse_alternate(
        &Parser::parse_let_statement_initialized,
        &Parser::parse_let_statement_uninitialized);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_let_statement_initialized() -> std::unique_ptr<Asts::LetStatementInitializedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_let);
    auto p2 = parse_once(&Parser::parse_local_variable);
    auto p3 = parse_once(&Parser::parse_token_assign);
    auto p4 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::LetStatementInitializedAst>(c1, p1, p2, p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_let_statement_uninitialized() -> std::unique_ptr<Asts::LetStatementUninitializedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_let);
    auto p2 = parse_once(&Parser::parse_local_variable);
    auto p3 = parse_once(&Parser::parse_token_colon);
    auto p4 = parse_once(&Parser::parse_type);
    return std::make_unique<Asts::LetStatementUninitializedAst>(c1, p1, p2, p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable() -> UniqueVariant<Asts::LocalVariableAst> {
    auto p1 = parse_alternate(
        &Parser::parse_local_variable_destructure_array,
        &Parser::parse_local_variable_destructure_tuple,
        &Parser::parse_local_variable_destructure_object,
        &Parser::parse_local_variable_single_identifier);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_destructure_skip_1_argument() -> std::unique_ptr<Asts::LocalVariableDestructureSkip1ArgumentAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_underscore);
    return std::make_unique<Asts::LocalVariableDestructureSkip1ArgumentAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_destructure_skip_n_arguments() -> std::unique_ptr<Asts::LocalVariableDestructureSkipNArgumentsAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_double_dot);
    auto p2 = parse_optional(&Parser::parse_local_variable_single_identifier);
    return std::make_unique<Asts::LocalVariableDestructureSkipNArgumentsAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_single_identifier() -> std::unique_ptr<Asts::LocalVariableSingleIdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_keyword_mut);
    auto p2 = parse_once(&Parser::parse_identifier);
    auto p3 = parse_optional(&Parser::parse_local_variable_single_identifier_alias);
    return std::make_unique<Asts::LocalVariableSingleIdentifierAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_single_identifier_alias() -> std::unique_ptr<Asts::LocalVariableSingleIdentifierAliasAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_as);
    auto p2 = parse_once(&Parser::parse_identifier);
    return std::make_unique<Asts::LocalVariableSingleIdentifierAliasAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_destructure_array() -> std::unique_ptr<Asts::LocalVariableDestructureArrayAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_curly_brace);
    auto p2 = parse_1_or_more(&Parser::parse_local_variable_nested_for_destructure_array, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_curly_brace);
    return std::make_unique<Asts::LocalVariableDestructureArrayAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_destructure_tuple() -> std::unique_ptr<Asts::LocalVariableDestructureTupleAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_1_or_more(&Parser::parse_local_variable_nested_for_destructure_tuple, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::LocalVariableDestructureTupleAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_destructure_object() -> std::unique_ptr<Asts::LocalVariableDestructureObjectAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_type_single);
    auto p2 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p3 = parse_0_or_more(&Parser::parse_local_variable_nested_for_destructure_object, Parser::parse_token_comma);
    auto p4 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::LocalVariableDestructureObjectAst>(c1, p1, p2, p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_attribute_binding() -> std::unique_ptr<Asts::LocalVariableAttributeBindingAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_local_variable_nested_for_attribute_binding);
    return std::make_unique<Asts::LocalVariableAttributeBindingAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_nested_for_destructure_array() -> std::unique_ptr<Asts::LocalVariableNestedForDestructureArrayAst> {
    auto p1 = parse_alternate(
        &Parser::parse_local_variable_destructure_array,
        &Parser::parse_local_variable_destructure_tuple,
        &Parser::parse_local_variable_destructure_object,
        &Parser::parse_local_variable_single_identifier,
        &Parser::parse_local_variable_destructure_skip_n_arguments,
        &Parser::parse_local_variable_destructure_skip_1_argument);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_nested_for_destructure_tuple() -> std::unique_ptr<Asts::LocalVariableNestedForDestructureTupleAst> {
    auto p1 = parse_alternate(
        &Parser::parse_local_variable_destructure_array,
        &Parser::parse_local_variable_destructure_tuple,
        &Parser::parse_local_variable_destructure_object,
        &Parser::parse_local_variable_single_identifier,
        &Parser::parse_local_variable_destructure_skip_n_arguments,
        &Parser::parse_local_variable_destructure_skip_1_argument);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_local_variable_nested_for_destructure_object() -> std::unique_ptr<Asts::LocalVariableNestedForDestructureObjectAst> {
    auto p1 = parse_alternate(
        &Parser::parse_local_variable_attribute_binding,
        &Parser::parse_local_variable_single_identifier,
        &Parser::parse_local_variable_destructure_skip_n_arguments);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_local_variable_nested_for_attribute_binding() -> std::unique_ptr<Asts::LocalVariableNestedForAttributeBindingAst> {
    auto p1 = parse_alternate(
        &Parser::parse_local_variable_destructure_array,
        &Parser::parse_local_variable_destructure_tuple,
        &Parser::parse_local_variable_destructure_object,
        &Parser::parse_local_variable_single_identifier);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_assignment_statement() -> std::unique_ptr<Asts::AssignmentStatementAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_1_or_more(&Parser::parse_expression, &Parser::parse_token_comma);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_1_or_more(&Parser::parse_expression, &Parser::parse_token_comma);
    return std::make_unique<Asts::AssignmentStatementAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_case_expression_branch_simple() -> std::unique_ptr<Asts::CaseExpressionBranchAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_flavour_else_case,
        &Parser::parse_pattern_flavour_else);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_case_expression_branch() -> std::unique_ptr<Asts::CaseExpressionBranchAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_flavour_destructuring,
        &Parser::parse_pattern_flavour_non_destructuring,
        &Parser::parse_pattern_flavour_else_case,
        &Parser::parse_pattern_flavour_else);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_flavour_destructuring() -> std::unique_ptr<Asts::CaseExpressionBranchAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_is);
    auto p2 = parse_1_or_more(&Parser::parse_pattern_group_destructure, &Parser::parse_token_comma);
    auto p3 = parse_optional(&Parser::parse_pattern_guard);
    auto p4 = parse_once(&Parser::parse_inner_scope);
    return std::make_unique<Asts::CaseExpressionBranchAst>(c1, p1, p2, p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_flavour_non_destructuring() -> std::unique_ptr<Asts::CaseExpressionBranchAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_boolean_comparison_op);
    auto p2 = parse_1_or_more(&Parser::parse_pattern_variant_expression, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_inner_scope);
    return std::make_unique<Asts::CaseExpressionBranchAst>(c1, p1, p2, std::nullopt, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_flavour_else_case() -> std::unique_ptr<Asts::CaseExpressionBranchAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_pattern_variant_else_case);
    return Asts::CaseExpressionBranchAst::from_else_to_else_case(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_flavour_else() -> std::unique_ptr<Asts::CaseExpressionBranchAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_pattern_variant_else);
    auto p2 = parse_once(&Parser::parse_inner_scope);
    return std::make_unique<Asts::CaseExpressionBranchAst>(c1, std::nullopt, {p1}, std::nullopt, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_group_destructure() -> UniqueVariant<Asts::PatternVariantAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_variant_destructure_array,
        &Parser::parse_pattern_variant_destructure_tuple,
        &Parser::parse_pattern_variant_destructure_object);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_skip_argument() -> std::unique_ptr<Asts::PatternVariantDestructureSkip1ArgumentAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_underscore);
    return std::make_unique<Asts::PatternVariantDestructureSkip1ArgumentAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_skip_arguments() -> std::unique_ptr<Asts::PatternVariantDestructureSkipNArgumentsAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_double_dot);
    auto p2 = parse_optional(&Parser::parse_pattern_variant_single_identifier);
    return std::make_unique<Asts::PatternVariantDestructureSkipNArgumentsAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_single_identifier() -> std::unique_ptr<Asts::PatternVariantSingleIdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_keyword_mut);
    auto p2 = parse_once(&Parser::parse_identifier);
    auto p3 = parse_optional(&Parser::parse_local_variable_single_identifier_alias);
    return std::make_unique<Asts::PatternVariantSingleIdentifierAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_destructure_array() -> std::unique_ptr<Asts::PatternVariantDestructureArrayAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_1_or_more(&Parser::parse_pattern_variant_nested_for_destructure_array, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::PatternVariantDestructureArrayAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_destructure_tuple() -> std::unique_ptr<Asts::PatternVariantDestructureTupleAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_1_or_more(&Parser::parse_pattern_variant_nested_for_destructure_tuple, &Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::PatternVariantDestructureTupleAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_destructure_object() -> std::unique_ptr<Asts::PatternVariantDestructureObjectAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_type_single);
    auto p2 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p3 = parse_0_or_more(&Parser::parse_pattern_variant_nested_for_destructure_object, &Parser::parse_token_comma);
    auto p4 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::PatternVariantDestructureObjectAst>(c1, p1, p2, p3, p4);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_attribute_binding() -> std::unique_ptr<Asts::PatternVariantAttributeBindingAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_pattern_variant_nested_for_attribute_binding);
    return std::make_unique<Asts::PatternVariantAttributeBindingAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_literal() -> std::unique_ptr<Asts::PatternVariantLiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_float,
        &Parser::parse_literal_integer,
        &Parser::parse_literal_string,
        &Parser::parse_literal_boolean);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_expression() -> std::unique_ptr<Asts::PatternVariantExpressionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::PatternVariantExpressionAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_else() -> std::unique_ptr<Asts::PatternVariantElseAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_else);
    return std::make_unique<Asts::PatternVariantElseAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_else_case() -> std::unique_ptr<Asts::PatternVariantElseCaseAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_else);
    auto p2 = parse_once(&Parser::parse_case_expression);
    return std::make_unique<Asts::PatternVariantElseCaseAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_nested_for_destructure_array() -> std::unique_ptr<Asts::PatternVariantNestedForDestructureArrayAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_variant_destructure_array,
        &Parser::parse_pattern_variant_destructure_tuple,
        &Parser::parse_pattern_variant_destructure_object,
        &Parser::parse_pattern_variant_single_identifier,
        &Parser::parse_pattern_variant_literal,
        &Parser::parse_pattern_variant_skip_arguments,
        &Parser::parse_pattern_variant_skip_argument);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_nested_for_destructure_tuple() -> std::unique_ptr<Asts::PatternVariantNestedForDestructureTupleAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_variant_destructure_array,
        &Parser::parse_pattern_variant_destructure_tuple,
        &Parser::parse_pattern_variant_destructure_object,
        &Parser::parse_pattern_variant_single_identifier,
        &Parser::parse_pattern_variant_literal,
        &Parser::parse_pattern_variant_skip_arguments,
        &Parser::parse_pattern_variant_skip_argument);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_nested_for_destructure_object() -> std::unique_ptr<Asts::PatternVariantNestedForDestructureObjectAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_variant_attribute_binding,
        &Parser::parse_pattern_variant_single_identifier,
        &Parser::parse_pattern_variant_skip_arguments);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_variant_nested_for_attribute_binding() -> std::unique_ptr<Asts::PatternVariantNestedForAttributeBindingAst> {
    auto p1 = parse_alternate(
        &Parser::parse_pattern_variant_destructure_array,
        &Parser::parse_pattern_variant_destructure_tuple,
        &Parser::parse_pattern_variant_destructure_object,
        &Parser::parse_pattern_variant_literal);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_pattern_guard() -> std::unique_ptr<Asts::PatternGuardAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_and);
    auto p2 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::PatternGuardAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_op_precedence_level_1() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_once(&Parser::parse_keyword_or);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_op_precedence_level_2() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_once(&Parser::parse_keyword_and);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_op_precedence_level_3() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_once(&Parser::parse_keyword_is);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_op_precedence_level_4() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_alternate(
        &Parser::parse_token_eq,
        &Parser::parse_token_ne,
        &Parser::parse_token_le,
        &Parser::parse_token_ge,
        &Parser::parse_token_lt,
        &Parser::parse_token_gt,
        &Parser::parse_token_ss);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_op_precedence_level_5() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_alternate(
        &Parser::parse_token_add_assign,
        &Parser::parse_token_sub_assign,
        &Parser::parse_token_add,
        &Parser::parse_token_sub);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_binary_op_precedence_level_6() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_alternate(
        &Parser::parse_token_mul_assign,
        &Parser::parse_token_div_assign,
        &Parser::parse_token_rem_assign,
        &Parser::parse_token_mod_assign,
        &Parser::parse_token_exp_assign,
        &Parser::parse_token_mul,
        &Parser::parse_token_div,
        &Parser::parse_token_rem,
        &Parser::parse_token_mod,
        &Parser::parse_token_exp);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_boolean_comparison_op() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_alternate(
        &Parser::parse_token_eq,
        &Parser::parse_token_ne,
        &Parser::parse_token_le,
        &Parser::parse_token_ge,
        &Parser::parse_token_lt,
        &Parser::parse_token_gt);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_unary_op() -> std::unique_ptr<Asts::UnaryExpressionOperatorAst> {
    auto p1 = parse_alternate(
        &Parser::parse_unary_op_async_call);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_unary_op_async_call() -> std::unique_ptr<Asts::UnaryExpressionOperatorAsyncAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_keyword_async);
    return std::make_unique<Asts::UnaryExpressionOperatorAsyncAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op() -> std::unique_ptr<Asts::PostfixExpressionOperatorAst> {
    auto p1 = parse_alternate(
        &Parser::parse_postfix_op_function_call,
        &Parser::parse_postfix_op_member_access,
        &Parser::parse_postfix_op_early_return,
        &Parser::parse_postfix_op_not_keyword,
        &Parser::parse_postfix_op_step_keyword);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_function_call() -> std::unique_ptr<Asts::PostfixExpressionOperatorFunctionCallAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_generic_arguments);
    auto p2 = parse_once(&Parser::parse_function_call_arguments);
    auto p3 = parse_optional(&Parser::parse_token_double_dot);
    return std::make_unique<Asts::PostfixExpressionOperatorFunctionCallAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_member_access() -> std::unique_ptr<Asts::PostfixExpressionOperatorMemberAccessAst> {
    auto p1 = parse_alternate(
        &Parser::parse_postfix_op_member_access_runtime,
        &Parser::parse_postfix_op_member_access_static);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_member_access_runtime() -> std::unique_ptr<Asts::PostfixExpressionOperatorMemberAccessAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_dot);
    auto p2 = parse_alternate(
        &Parser::parse_identifier,
        &Parser::parse_numeric_identifier);
    return std::make_unique<Asts::PostfixExpressionOperatorMemberAccessAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_member_access_static() -> std::unique_ptr<Asts::PostfixExpressionOperatorMemberAccessAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_double_colon);
    auto p2 = parse_once(&Parser::parse_identifier);
    return std::make_unique<Asts::PostfixExpressionOperatorMemberAccessAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_early_return() -> std::unique_ptr<Asts::PostfixExpressionOperatorEarlyReturnAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_question_mark);
    return std::make_unique<Asts::PostfixExpressionOperatorEarlyReturnAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_not_keyword() -> std::unique_ptr<Asts::PostfixExpressionOperatorNotKeywordAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_dot);
    auto p2 = parse_once(&Parser::parse_keyword_primitive_not);
    return std::make_unique<Asts::PostfixExpressionOperatorNotKeywordAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_postfix_op_step_keyword() -> std::unique_ptr<Asts::PostfixExpressionOperatorStepKeywordAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_dot);
    auto p2 = parse_once(&Parser::parse_keyword_primitive_step);
    return std::make_unique<Asts::PostfixExpressionOperatorStepKeywordAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_convention() -> std::unique_ptr<Asts::ConventionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_convention_mut,
        &Parser::parse_convention_ref,
        &Parser::parse_convention_mov);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_convention_mov() -> std::unique_ptr<Asts::ConventionAst> {
    auto c1 = get_current_pos();
    return Asts::ConventionAst::mov(c1);
}

auto SPP::SyntacticAnalysis::Parser::parse_convention_mut() -> std::unique_ptr<Asts::ConventionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_borrow);
    auto p2 = parse_once(&Parser::parse_keyword_mut);
    return Asts::ConventionAst::mut(c1);
}

auto SPP::SyntacticAnalysis::Parser::parse_convention_ref() -> std::unique_ptr<Asts::ConventionAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_borrow);
    return Asts::ConventionAst::ref(c1);
}

auto SPP::SyntacticAnalysis::Parser::parse_object_initializer() -> std::unique_ptr<Asts::ObjectInitializerAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_type_single);
    auto p2 = parse_once(&Parser::parse_object_initializer_arguments);
    return std::make_unique<Asts::ObjectInitializerAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_object_initializer_arguments() -> std::unique_ptr<Asts::ObjectInitializerArgumentGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_0_or_more(&Parser::parse_object_initializer_argument, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::ObjectInitializerArgumentGroupAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_object_initializer_argument() -> std::unique_ptr<Asts::ObjectInitializerArgumentAst> {
    auto p1 = parse_alternate(
        &Parser::parse_object_initializer_argument_named,
        &Parser::parse_object_initializer_argument_unnamed);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_object_initializer_argument_unnamed() -> std::unique_ptr<Asts::ObjectInitializerArgumentUnnamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_token_double_dot);
    auto p2 = parse_once(&Parser::parse_identifier);
    return std::make_unique<Asts::ObjectInitializerArgumentUnnamedAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_object_initializer_argument_named() -> std::unique_ptr<Asts::ObjectInitializerArgumentNamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_expression);
    return std::make_unique<Asts::ObjectInitializerArgumentNamedAst>(c1, p1, p2, p3);
}


template <std::invocable<SPP::SyntacticAnalysis::Parser*> A1, std::invocable<SPP::SyntacticAnalysis::Parser*> A2>
auto SPP::SyntacticAnalysis::Parser::parse_type_binary_expression_precedence_level_n_rhs(A1 &&op, A2 &&rhs) -> std::pair<std::unique_ptr<Asts::TokenAst>, UniqueVariant<Asts::TypeAst>> {
    auto p1 = parse_once(op);
    auto p2 = parse_once(rhs);
    return std::make_pair(p1, p2);
}


template <std::invocable<SPP::SyntacticAnalysis::Parser*> A1, std::invocable<SPP::SyntacticAnalysis::Parser*> A2, std::invocable<SPP::SyntacticAnalysis::Parser*> A3>
auto SPP::SyntacticAnalysis::Parser::parse_type_binary_expression_precedence_level_n(A1 &&lhs, A2 &&op, A3 &&rhs) -> UniqueVariant<Asts::TypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(lhs);
    auto p2 = parse_optional([op, rhs]<typename T>(T&& s) { Parser::parse_binary_expression_precedence_level_n_rhs(s, op, rhs); });
    return p2 ? std::make_unique<Asts::TypeBinaryExpressionAst>(c1, p1, p2.first, p2.second) : p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_type() -> UniqueVariant<Asts::TypeAst> {
    auto p1 = parse_once(&Parser::parse_type_binary_expression_precedence_level_1);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_type_binary_expression_precedence_level_1() -> UniqueVariant<Asts::TypeAst> {
    return parse_type_binary_expression_precedence_level_n(&Parser::parse_type_binary_expression_precedence_level_2, &Parser::parse_type_binary_expression_precedence_level_1, &Parser::parse_type_binary_expression_precedence_level_1);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_binary_expression_precedence_level_2() -> UniqueVariant<Asts::TypeAst> {
    return parse_type_binary_expression_precedence_level_n(&Parser::parse_type_unary_expression, &Parser::parse_type_binary_expression_precedence_level_2, &Parser::parse_type_binary_expression_precedence_level_2);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_unary_expression() -> std::unique_ptr<Asts::TypeUnaryExpressionAst> {
    auto p1 = parse_0_or_more(&Parser::parse_type_unary_op, &Parser::parse_nothing);
    auto p2 = parse_once(&Parser::parse_type_primary_expression);
    return std::move(genex::algorithms::accumulate(p1 | genex::views::reverse, p2, []<typename T>(auto &&acc, T &&elem) -> std::unique_ptr<Asts::TypeUnaryExpressionAst> {
        return std::make_unique<Asts::TypeUnaryExpressionAst>(acc->pos, std::forward<T>(elem), std::move(acc));
    }));
}


auto SPP::SyntacticAnalysis::Parser::parse_type_postfix_expression() -> std::unique_ptr<Asts::TypePostfixExpressionAst> {
    auto p1 = parse_once(&Parser::parse_type_primary_expression);
    auto p2 = parse_0_or_more(&Parser::parse_type_postfix_op, &Parser::parse_nothing);
    return std::move(genex::algorithms::accumulate(p2, p1, []<typename T>(auto &&acc, T &&elem) -> std::unique_ptr<Asts::TypePostfixExpressionAst> {
        return std::make_unique<Asts::TypePostfixExpressionAst>(acc->pos, std::move(acc), std::forward<T>(elem));
    }));
}


auto SPP::SyntacticAnalysis::Parser::parse_type_primary_expression() -> std::unique_ptr<Asts::TypePrimaryExpressionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_type_parenthesized,
        &Parser::parse_type_tuple,
        &Parser::parse_type_array,
        &Parser::parse_type_single);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_type_parenthesized() -> std::unique_ptr<Asts::TypeParenthesizedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_once(&Parser::parse_type);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TypeParenthesizedAst>(c1, p1, p2, p3);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_tuple() -> std::unique_ptr<Asts::TypeTupleAst> {
    auto p1 = parse_alternate(
        &Parser::parse_type_tuple_1_items,
        &Parser::parse_type_tuple_n_items);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_type_array() -> std::unique_ptr<Asts::TypeArrayAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_once(&Parser::parse_type);
    auto p3 = parse_once(&Parser::parse_token_comma);
    auto p4 = parse_once(&Parser::parse_lexeme_dec_integer);
    auto p5 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::TypeArrayAst>(c1, p1, p2, p3, p4, p5);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_single() -> std::unique_ptr<Asts::TypeSingleAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_generic_identifier);
    return std::make_unique<Asts::TypeSingleAst>(c1, p1);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_unary_op() -> UniqueVariant<Asts::TypeUnaryOperatorAst> {
    auto p1 = parse_alternate(
        &Parser::parse_type_unary_op_namespace);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_type_unary_op_namespace() -> std::unique_ptr<Asts::TypeUnaryOperatorNamespaceAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_double_colon);
    return std::make_unique<Asts::TypeUnaryOperatorNamespaceAst>(c1, p1, p2);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_postfix_op() -> UniqueVariant<Asts::TypePostfixOperatorAst> {
    auto p1 = parse_alternate(
        &Parser::parse_type_postfix_op_nested_type,
        &Parser::parse_type_postfix_op_indexed_type,
        &Parser::parse_type_postfix_op_optional_type);
    return p1;
}


auto SPP::SyntacticAnalysis::Parser::parse_type_postfix_op_nested_type() -> std::unique_ptr<Asts::TypePostfixOperatorNestedTypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_double_colon);
    auto p2 = parse_once(&Parser::parse_type_single);
    return std::make_unique<Asts::TypePostfixOperatorNestedTypeAst>(c1, p1, p2);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_postfix_op_indexed_type() -> std::unique_ptr<Asts::TypePostfixOperatorIndexedTypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_dot);
    auto p2 = parse_once(&Parser::parse_lexeme_dec_integer);
    return std::make_unique<Asts::TypePostfixOperatorIndexedTypeAst>(c1, p1, p2);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_postfix_op_optional_type() -> std::unique_ptr<Asts::TypePostfixOperatorOptionalTypeAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_question_mark);
    return std::make_unique<Asts::TypePostfixOperatorOptionalTypeAst>(c1, p1);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_tuple_1_items() -> std::unique_ptr<Asts::TypeTupleAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_once(&Parser::parse_type);
    auto p3 = parse_once(&Parser::parse_token_comma);
    auto p4 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TypeTupleAst>(c1, p1, p2, p3, p4);
}


auto SPP::SyntacticAnalysis::Parser::parse_type_tuple_n_items() -> std::unique_ptr<Asts::TypeTupleAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_2_or_more(&Parser::parse_type, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TypeTupleAst>(c1, p1, p2, p3);
}


auto SPP::SyntacticAnalysis::Parser::parse_identifier() -> std::unique_ptr<Asts::IdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_lexeme_identifier);
    return std::make_unique<Asts::IdentifierAst>(c1, std::move(p1->token_data));
}


auto SPP::SyntacticAnalysis::Parser::parse_numeric_identifier() -> std::unique_ptr<Asts::IdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_lexeme_dec_integer);
    return std::make_unique<Asts::IdentifierAst>(c1, std::move(p1->token_data));
}


auto SPP::SyntacticAnalysis::Parser::parse_upper_identifier() -> std::unique_ptr<Asts::IdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_lexeme_upper_identifier);
    return std::make_unique<Asts::IdentifierAst>(c1, std::move(p1->token_data));
}

auto SPP::SyntacticAnalysis::Parser::parse_generic_identifier() -> std::unique_ptr<Asts::GenericIdentifierAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_upper_identifier);
    auto p2 = parse_optional(&Parser::parse_generic_arguments);
    return std::make_unique<Asts::GenericIdentifierAst>(c1, p1->value, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal() -> std::unique_ptr<Asts::LiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_float,
        &Parser::parse_literal_integer,
        &Parser::parse_literal_string,
        &Parser::parse_literal_tuple,
        &Parser::parse_literal_array,
        &Parser::parse_literal_boolean);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_float() -> std::unique_ptr<Asts::FloatLiteralAst> {
    auto p1 = parse_once(&Parser::parse_literal_float_b10);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_integer() -> std::unique_ptr<Asts::IntegerLiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_integer_b10,
        &Parser::parse_literal_integer_b02,
        &Parser::parse_literal_integer_b16);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_string() -> std::unique_ptr<Asts::StringLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_lexeme_string);
    return std::make_unique<Asts::StringLiteralAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_tuple() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_tuple_0_items,
        &Parser::parse_literal_tuple_1_items,
        &Parser::parse_literal_tuple_n_items);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_comp_tuple() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_tuple_0_items,
        &Parser::parse_literal_comp_tuple_1_items,
        &Parser::parse_literal_comp_tuple_n_items);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_array() -> std::unique_ptr<Asts::LiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_array_0_items,
        &Parser::parse_literal_array_n_items);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_comp_array() -> std::unique_ptr<Asts::ArrayLiteralAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_array_0_items,
        &Parser::parse_literal_comp_array_n_items);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_boolean() -> std::unique_ptr<Asts::BooleanLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_alternate(
        Parser::parse_keyword_true,
        Parser::parse_keyword_false);
    return std::make_unique<Asts::BooleanLiteralAst>(c1, p1);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_float_b10() -> std::unique_ptr<Asts::FloatLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_numeric_prefix_op);
    auto p2 = parse_once(&Parser::parse_lexeme_dec_integer);
    auto p3 = parse_once(&Parser::parse_token_dot);
    auto p4 = parse_once(&Parser::parse_lexeme_dec_integer);
    auto p5 = parse_optional(&Parser::parse_float_postfix_type);
    return std::make_unique<Asts::FloatLiteralAst>(c1, p1, p2, p3, p4, p5.and_then([](auto&& x) { Asts::TypeSingleAst::from(x); }));
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_integer_b10() -> std::unique_ptr<Asts::IntegerLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_numeric_prefix_op);
    auto p2 = parse_once(&Parser::parse_lexeme_dec_integer);
    auto p3 = parse_optional(&Parser::parse_integer_postfix_type);
    return std::make_unique<Asts::IntegerLiteralAst>(c1, p1, p2, p3.and_then([](auto&& x) { Asts::TypeSingleAst::from(x); }));
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_integer_b02() -> std::unique_ptr<Asts::IntegerLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_numeric_prefix_op);
    auto p2 = parse_once(&Parser::parse_lexeme_bin_integer);
    auto p3 = parse_optional(&Parser::parse_integer_postfix_type);
    return std::make_unique<Asts::IntegerLiteralAst>(c1, p1, p2, p3.and_then([](auto&& x) { Asts::TypeSingleAst::from(x); }));
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_integer_b16() -> std::unique_ptr<Asts::IntegerLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_optional(&Parser::parse_numeric_prefix_op);
    auto p2 = parse_once(&Parser::parse_lexeme_hex_integer);
    auto p3 = parse_optional(&Parser::parse_integer_postfix_type);
    return std::make_unique<Asts::IntegerLiteralAst>(c1, p1, p2, p3.and_then([](auto&& x) { Asts::TypeSingleAst::from(x); }));
}

auto SPP::SyntacticAnalysis::Parser::parse_numeric_prefix_op() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_alternate(
        &Parser::parse_token_sub,
        &Parser::parse_token_add);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_integer_postfix_type() -> std::unique_ptr<Asts::IdentifierAst> {
    auto _a = parse_once(&Parser::parse_token_underscore);
    auto p1 = parse_alternate(
        [](auto&& x) { Parser::parse_characters(x, "i8"); },
        [](auto&& x) { Parser::parse_characters(x, "i16"); },
        [](auto&& x) { Parser::parse_characters(x, "i32"); },
        [](auto&& x) { Parser::parse_characters(x, "i64"); },
        [](auto&& x) { Parser::parse_characters(x, "i128"); },
        [](auto&& x) { Parser::parse_characters(x, "i256"); },
        [](auto&& x) { Parser::parse_characters(x, "u8"); },
        [](auto&& x) { Parser::parse_characters(x, "u16"); },
        [](auto&& x) { Parser::parse_characters(x, "u32"); },
        [](auto&& x) { Parser::parse_characters(x, "u64"); },
        [](auto&& x) { Parser::parse_characters(x, "u128"); },
        [](auto&& x) { Parser::parse_characters(x, "u256"); });
    return std::make_unique<Asts::IdentifierAst>(p1->pos, p1->metadata);
}

auto SPP::SyntacticAnalysis::Parser::parse_float_postfix_type() -> std::unique_ptr<Asts::IdentifierAst> {
    auto _a = parse_once(&Parser::parse_token_underscore);
    auto p1 = parse_alternate(
        [](auto&& x) { Parser::parse_characters(x, "f8"); },
        [](auto&& x) { Parser::parse_characters(x, "f16"); },
        [](auto&& x) { Parser::parse_characters(x, "f32"); },
        [](auto&& x) { Parser::parse_characters(x, "f64"); },
        [](auto&& x) { Parser::parse_characters(x, "f128"); },
        [](auto&& x) { Parser::parse_characters(x, "f256"); });
    return std::make_unique<Asts::IdentifierAst>(p1->pos, p1->metadata);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_tuple_0_items() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, {}, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_tuple_1_items() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_once(&Parser::parse_expression);
    auto _a = parse_once(&Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, {p2}, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_comp_tuple_1_items() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_once(&Parser::parse_comp_value);
    auto _a = parse_once(&Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, {p2}, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_tuple_n_items() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_2_or_more(&Parser::parse_expression, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_comp_tuple_n_items() -> std::unique_ptr<Asts::TupleLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_2_or_more(&Parser::parse_comp_value, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_array_0_items() -> std::unique_ptr<Asts::ArrayLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_once(&Parser::parse_type);
    auto p3 = parse_once(&Parser::parse_token_comma);
    auto p4 = parse_once(&Parser::parse_lexeme_dec_integer);
    auto p5 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, p2, p3, p4, p5);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_array_n_items() -> std::unique_ptr<Asts::ArrayLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_1_or_more(&Parser::parse_expression, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::TupleLiteralAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_literal_comp_array_n_items() -> std::unique_ptr<Asts::ArrayLiteralAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_square_bracket);
    auto p2 = parse_1_or_more(&Parser::parse_comp_value, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_square_bracket);
    return std::make_unique<Asts::LiteralAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_comp_value() -> UniqueVariant<Asts::ExpressionAst> {
    auto p1 = parse_alternate(
        &Parser::parse_literal_float,
        &Parser::parse_literal_integer,
        &Parser::parse_literal_string,
        &Parser::parse_literal_comp_tuple,
        &Parser::parse_literal_comp_array,
        &Parser::parse_literal_boolean,
        &Parser::parse_identifier,
        &Parser::parse_comp_object_initializer);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_comp_object_initializer() -> std::unique_ptr<Asts::ObjectInitializerAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_type_single);
    auto p2 = parse_once(&Parser::parse_comp_object_initializer_arguments);
    return std::make_unique<Asts::ObjectInitializerAst>(c1, p1, p2);
}

auto SPP::SyntacticAnalysis::Parser::parse_comp_object_initializer_arguments() -> std::unique_ptr<Asts::ObjectInitializerArgumentGroupAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_token_left_parenthesis);
    auto p2 = parse_0_or_more(&Parser::parse_comp_object_initializer_argument_named, Parser::parse_token_comma);
    auto p3 = parse_once(&Parser::parse_token_right_parenthesis);
    return std::make_unique<Asts::ObjectInitializerArgumentGroupAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_comp_object_initializer_argument_named() -> std::unique_ptr<Asts::ObjectInitializerArgumentNamedAst> {
    auto c1 = get_current_pos();
    auto p1 = parse_once(&Parser::parse_identifier);
    auto p2 = parse_once(&Parser::parse_token_assign);
    auto p3 = parse_once(&Parser::parse_comp_value);
    return std::make_unique<Asts::ObjectInitializerArgumentNamedAst>(c1, p1, p2, p3);
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_primitive(TokenTypes keyword) -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    for (auto c: magic_enum::enum_name(keyword)) {
        parse_once([c](auto &&x) { Parser::parse_character(x, c); });
    }
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, magic_enum::enum_name(keyword));
}

auto SPP::SyntacticAnalysis::Parser::parse_token_left_curly_brace() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkLeftCurlyBrace); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkLeftBrace, "{");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_right_curly_brace() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkRightCurlyBrace); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkRightBrace, "}");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_left_parenthesis() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkLeftParenthesis); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkLeftParenthesis, "(");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_right_parenthesis() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, TokenTypes::TkRightParenthesis); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkRightParenthesis, ")");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_left_square_bracket() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkLeftSquareBracket); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkLeftBracket, "[");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_right_square_bracket() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkRightSquareBracket); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkRightBracket, "]");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_dot() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkDot); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkDot, ".");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_comma() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkComma); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkComma, ",");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_colon() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkColon); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkColon, ":");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_at() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAt); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkAt, "@");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkAssign, "=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_newline() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkNewLine); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkNewLine, "\n");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_question_mark() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkQuestionMark); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkQuestionMark, "?");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_borrow() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAmpersand); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkAmpersand, "&");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_union() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkVerticalBar); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkVerticalBar, "|");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_lt() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkLessThanSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkLessThan, "<");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_gt() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkGreaterThanSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkGreaterThan, ">");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_add() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPlusSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkPlus, "+");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_sub() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkMinusSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkMinus, "-");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_mul() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAsterisk); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkAsterisk, "*");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_div() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkForwardSlash); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkForwardSlash, "/");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_rem() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPercentSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkPercent, "%");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_underscore() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkUnderscore); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkUnderscore, "_");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_speech_mark() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkSpeechMark); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkSpeechMark, "\"");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_double_colon() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_once(&Parser::parse_token_colon);
    auto _a = parse_once(&Parser::parse_token_colon);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_token_double_dot() -> std::unique_ptr<Asts::TokenAst> {
    auto p1 = parse_once(&Parser::parse_token_dot);
    auto _a = parse_once(&Parser::parse_token_dot);
    return p1;
}

auto SPP::SyntacticAnalysis::Parser::parse_token_rightward_arrow() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkMinusSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkGreaterThanSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkRightwardsArrow, "->");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_eq() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkEquals, "==");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_ne() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkExclamationMark); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkNotEquals, "!=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_le() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkLessThanSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkLessThanOrEqual, "<=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_ge() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkGreaterThanSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkGreaterThanOrEqual, ">=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_add_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPlusSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkPlusEquals, "+=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_sub_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkMinusSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkMinusEquals, "-=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_ss() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkLessThanSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkGreaterThanSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkSpaceship, "<=>");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_mul_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAsterisk); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkAsteriskEquals, "*=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_div_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkForwardSlash); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkForwardSlashEquals, "/=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_rem_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPercentSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkPercentEquals, "%=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_mod_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPercentSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPercentSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkDoublePercentEquals, "%%=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_exp_assign() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAsterisk); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAsterisk); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkEqualsSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkExponentEquals, "**=");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_mod() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPercentSign); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkPercentSign); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkPercent, "%%");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_exp() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAsterisk); });
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkAsterisk); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::TkExponent, "**");
}

auto SPP::SyntacticAnalysis::Parser::parse_nothing() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::NoToken); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, "");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_cls() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwCls); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwCls, "cls");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_sup() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwSup); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwSup, "sup");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_ext() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwExt); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwExt, "ext");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_fun() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwFun); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwFun, "fun");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_cor() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwCor); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwCor, "cor");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_use() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwUse); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwUse, "use");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_let() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwLet); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwLet, "let");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_mut() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwMut); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwMut, "mut");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_cmp() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwCmp); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwCmp, "cmp");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_where() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwWhere); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwWhere, "where");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_self_val() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwSelfVal); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwSelfVal, "self");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_self_type() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwSelfType); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwSelfType, "Self");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_case() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwCase); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwCase, "case");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_loop() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwLoop); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwLoop, "loop");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_with() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwWith); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwWith, "with");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_gen() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwGen); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwGen, "gen");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_ret() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwRet); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwRet, "ret");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_skip() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwSkip); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwSkip, "skip");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_exit() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwExit); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwExit, "exit");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_else() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwElse); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwElse, "else");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_false() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwFalse); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwFalse, "false");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_true() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwTrue); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwTrue, "true");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_of() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwOf); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwOf, "of");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_in() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwIn); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwIn, "in");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_pin() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwPin); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwPin, "pin");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_rel() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwRel); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwRel, "rel");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_as() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwAs); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwAs, "as");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_is() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwIs); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwIs, "is");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_and() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwAnd); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwAnd, "and");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_or() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwOr); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwOr, "or");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_not() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwNot); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwNot, "not");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_async() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwAsync); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwAsync, "async");
}

auto SPP::SyntacticAnalysis::Parser::parse_keyword_step() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { parse_keyword_primitive(x, TokenTypes::KwStep); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::KwStep, "step");
}

auto SPP::SyntacticAnalysis::Parser::parse_lexeme_dec_integer() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto integer = std::string{};

    parse_once(&Parser::parse_nothing);
    switch (token_stream[get_current_pos()].tok_type) {
    case RawTokenTypes::TkNumber:
        parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
        integer += token_stream[get_current_pos()].tok_metadata;
    default:
        throw Errors::SyntaxError(c1, "Expected decimal integer");
    }

    while (token_stream[get_current_pos()].tok_type == RawTokenTypes::TkNumber) {
        auto p1 = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
        integer += p1->token_data;
    }

    if (integer.empty())
        throw Errors::SyntaxError(c1, "Expected decimal integer");
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(integer));
}

auto SPP::SyntacticAnalysis::Parser::parse_lexeme_bin_integer() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto integer = std::string{};

    auto p1 = parse_once( [this](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
    if (p1->token_data != "0") {
        throw Errors::SyntaxError(c1, "Expected binary integer");
    }

    auto p2 = parse_once( [this](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
    if (p1->token_data != "b") {
        throw Errors::SyntaxError(c1, "Expected binary integer");
    }

    while (token_stream[get_current_pos()].tok_type == RawTokenTypes::TkNumber) {
        auto p3 = parse_once( [this](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
        integer += p3->token_data;
        if (p3->token_data[0] != '0' or p3->token_data[0] != '1') {
            throw Errors::SyntaxError(c1, "Expected binary integer");
        }
    }

    if (integer.empty())
        throw Errors::SyntaxError(c1, "Expected binary integer");
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(integer));
}

auto SPP::SyntacticAnalysis::Parser::parse_lexeme_hex_integer() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto integer = std::string{};

    auto p1 = parse_once( [this](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
    if (p1->token_data != "0") {
        throw Errors::SyntaxError(c1, "Expected hexadecimal integer");
    }

    auto p2 = parse_once( [this](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
    if (p2->token_data != "x") {
        throw Errors::SyntaxError(c1, "Expected hexadecimal integer");
    }

    while (token_stream[get_current_pos()].tok_type == RawTokenTypes::TkNumber) {
        auto p3 = parse_once( [this](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
        integer += p3->token_data;
        if (not std::isxdigit(p3->token_data[0])) {
            throw Errors::SyntaxError(c1, "Expected hexadecimal integer");
        }
    }

    if (integer.empty())
        throw Errors::SyntaxError(c1, "Expected hexadecimal integer");
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(integer));
}

auto SPP::SyntacticAnalysis::Parser::parse_lexeme_string() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto identifier = std::string{};
    parse_once(&Parser::parse_token_speech_mark);

    while (token_stream[get_current_pos()].tok_type == RawTokenTypes::TkNumber) {
        auto p1 = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
        identifier += p1->token_data;
    }

    parse_once(&Parser::parse_token_speech_mark);
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(identifier));
}

auto SPP::SyntacticAnalysis::Parser::parse_lexeme_identifier() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto identifier = std::string{};

    parse_once(&Parser::parse_nothing);
    switch (token_stream[get_current_pos()]) {
        case RawTokenTypes::TkCharacter:
            if (std::islower(token_stream[get_current_pos()].tok_metadata)) {
                parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
                identifier += token_stream[get_current_pos()].tok_metadata;
            }
            else {
                throw Errors::SyntaxError(c1, "Expected identifier");
            }
        case default: {
            throw Errors::SyntaxError(c1, "Expected identifier");
        }
    }

    while (true) {
        switch (token_stream[get_current_pos()]) {
        case RawTokenTypes::TkCharacter:
            auto p1 = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
            identifier += p1->token_data;
        case RawTokenTypes::TkNumber:
            auto p2 = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
            identifier += p1->token_data;
        case RawTokenTypes::TkUnderscore:
            parse_once( [](auto&& x) { Parser::parse_token_primitive(x, TokenTypes::TkUnderscore); });
            identifier += '_';
        case default:
            break;
        }
    }

    if (identifier.empty())
        throw Errors::SyntaxError(c1, "Expected identifier");
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(identifier));
}

auto SPP::SyntacticAnalysis::Parser::parse_lexeme_upper_identifier() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto identifier = std::string{};

    parse_once(&Parser::parse_nothing);
    switch (token_stream[get_current_pos()]) {
    case RawTokenTypes::TkCharacter:
        if (std::isupper(token_stream[get_current_pos()].tok_metadata)) {
            parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
            identifier += token_stream[get_current_pos()].tok_metadata;
        }
        else {
            throw Errors::SyntaxError(c1, "Expected identifier");
        }
    case default: {
        throw Errors::SyntaxError(c1, "Expected identifier");
    }
    }

    while (true) {
        switch (token_stream[get_current_pos()]) {
        case RawTokenTypes::TkCharacter:
            auto p1 = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
            identifier += p1->token_data;
        case RawTokenTypes::TkNumber:
            auto p2 = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
            identifier += p1->token_data;
        case RawTokenTypes::TkUnderscore:
            parse_once( [](auto&& x) { return Parser::parse_token_primitive(x, TokenTypes::TkUnderscore); });
            identifier += '_';
        case default:
            break;
        }
    }

    if (identifier.empty())
        throw Errors::SyntaxError(c1, "Expected identifier");
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(identifier));
}

auto SPP::SyntacticAnalysis::Parser::parse_characters(std::string&& characters) -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    auto identifier = std::string{};

    for (auto c: characters) {
        auto p1 = parse_once( [c](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_character(x, c); });
        identifier += p1->token_data;
    }

    if (identifier != characters) {
        throw Errors::SyntaxError(c1, std::format("Expected '{}', got '{}'", characters, identifier));
    }

    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(identifier));
}

auto SPP::SyntacticAnalysis::Parser::parse_character(char character) -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();

    parse_once(&Parser::parse_nothing);
    switch (token_stream[get_current_pos()]) {
    case RawTokenTypes::TkCharacter:
        auto string = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { return Parser::parse_token_primitive(x, RawTokenTypes::TkCharacter); });
        if (string->token_data[0] != character)
            throw Errors::SyntaxError(c1, std::format("Expected '{}', got '{}'", character, string));
        return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(string->token_data));
    case RawTokenTypes::TkNumber:
        auto number = parse_once( [](auto&& x) -> std::unique_ptr<Asts::TokenAst> { Parser::parse_token_primitive(x, RawTokenTypes::TkNumber); });
        if (number->token_data[0] != character)
            throw Errors::SyntaxError(c1, format("Expected '{}', got '{}'", character, number));
        return std::make_unique<Asts::TokenAst>(c1, TokenTypes::NoToken, std::move(number->token_data));
    case default:
        throw Errors::SyntaxError(c1, "Expected upper identifier");
    }
}

auto SPP::SyntacticAnalysis::Parser::parse_eof() -> std::unique_ptr<Asts::TokenAst> {
    auto c1 = get_current_pos();
    parse_once( [](auto&& x) { Parser::parse_token_primitive(x, RawTokenTypes::EndOfFile); });
    return std::make_unique<Asts::TokenAst>(c1, TokenTypes::EndOfFile, "");
}

auto SPP::SyntacticAnalysis::Parser::parse_token_primitive(RawTokenTypes token_type) -> std::unique_ptr<Asts::TokenAst> {
    if (pos > token_stream_size) {
        auto new_error = std::format("Expected token {:?} but found end of file", token_type);
        store_error(get_current_pos(), new_error);
        throw *error;
    }

    if (token_type != RawTokenTypes::TkNewLine) {
        while (token_stream[pos].tok_type == RawTokenTypes::TkNewLine || token_stream[pos].tok_type == RawTokenTypes::TkWhitespace) {
            pos += 1;
        }
    }
    if (token_type == RawTokenTypes::TkNewLine) {
        while (token_stream[pos].tok_type == RawTokenTypes::TkWhitespace) {
            pos += 1;
        }
    }

    if (token_type == RawTokenTypes::NoToken) {
        return std::make_unique<Asts::TokenAst>(get_current_pos(), TokenTypes::NoToken, std::string{});
    }

    if (token_stream[pos].tok_type != token_type) {
        if (error->pos == pos) {
            error->expected.insert(token_type);
            throw *error;
        }

        auto new_error = std::format("Expected got '{}'", token_stream[pos]);
        if (store_error(pos, new_error)) {
            error->expected.insert(token_type);
        }
        throw *error;
    }

    auto token_character = std::string{};
    switch (token_stream[pos].tok_type) {
    case RawTokenTypes::TkCharacter:
    case RawTokenTypes::TkNumber:
        token_character = token_stream[pos].tok_metadata;
    default: ;
    }

    auto r = std::make_unique<Asts::TokenAst>(get_current_pos(), TokenTypes::NoToken, std::move(token_character));
    pos += 1;
    return r;
}

#include <Bindings/vili/parser/rules/rules.hpp>

#include <vili/parser/grammar.hpp>

#include <Bindings/Config.hpp>

namespace vili::parser::rules::Bindings
{
    void LoadClassAffectation(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::affectation> bindaffectation
            = rulesNamespace.new_usertype<vili::parser::rules::affectation>(
                "affectation", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassAffectationSeparator(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::affectation_separator> bindaffectation_separator
            = rulesNamespace.new_usertype<vili::parser::rules::affectation_separator>(
                "affectation_separator", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassArray(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array> bindarray
            = rulesNamespace.new_usertype<vili::parser::rules::array>(
                "array", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassArrayElements(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array_elements> bindarray_elements
            = rulesNamespace.new_usertype<vili::parser::rules::array_elements>(
                "array_elements", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassArraySeparator(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array_separator> bindarray_separator
            = rulesNamespace.new_usertype<vili::parser::rules::array_separator>(
                "array_separator", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassBlock(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::block> bindblock
            = rulesNamespace.new_usertype<vili::parser::rules::block>(
                "block", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassBoolean(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::boolean> bindboolean
            = rulesNamespace.new_usertype<vili::parser::rules::boolean>(
                "boolean", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassBraceBasedObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::brace_based_object> bindbrace_based_object
            = rulesNamespace.new_usertype<vili::parser::rules::brace_based_object>(
                "brace_based_object", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassChar_(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::char_> bindchar_
            = rulesNamespace.new_usertype<vili::parser::rules::char_>(
                "char_", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassCloseArray(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::close_array> bindclose_array
            = rulesNamespace.new_usertype<vili::parser::rules::close_array>(
                "close_array", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassCloseObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::close_object> bindclose_object
            = rulesNamespace.new_usertype<vili::parser::rules::close_object>(
                "close_object", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::comment> bindcomment
            = rulesNamespace.new_usertype<vili::parser::rules::comment>(
                "comment", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassData(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::data> binddata
            = rulesNamespace.new_usertype<vili::parser::rules::data>(
                "data", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassDigits(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::digits> binddigits
            = rulesNamespace.new_usertype<vili::parser::rules::digits>(
                "digits", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassElement(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::element> bindelement
            = rulesNamespace.new_usertype<vili::parser::rules::element>(
                "element", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassEmptyLine(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::empty_line> bindempty_line
            = rulesNamespace.new_usertype<vili::parser::rules::empty_line>(
                "empty_line", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassEndline(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::endline> bindendline
            = rulesNamespace.new_usertype<vili::parser::rules::endline>(
                "endline", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassEscaped(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::escaped> bindescaped
            = rulesNamespace.new_usertype<vili::parser::rules::escaped>(
                "escaped", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassEscapedChar(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::escaped_char> bindescaped_char
            = rulesNamespace.new_usertype<vili::parser::rules::escaped_char>(
                "escaped_char", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassFalse_(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::false_> bindfalse_
            = rulesNamespace.new_usertype<vili::parser::rules::false_>(
                "false_", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassFloatingPoint(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::floating_point> bindfloating_point
            = rulesNamespace.new_usertype<vili::parser::rules::floating_point>(
                "floating_point", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassFullNode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::full_node> bindfull_node
            = rulesNamespace.new_usertype<vili::parser::rules::full_node>(
                "full_node", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassGrammar(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::grammar> bindgrammar
            = rulesNamespace.new_usertype<vili::parser::rules::grammar>(
                "grammar", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassIdentifier(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::identifier> bindidentifier
            = rulesNamespace.new_usertype<vili::parser::rules::identifier>(
                "identifier", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassIndent(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::indent> bindindent
            = rulesNamespace.new_usertype<vili::parser::rules::indent>(
                "indent", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassIndentBasedObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::indent_based_object> bindindent_based_object
            = rulesNamespace.new_usertype<vili::parser::rules::indent_based_object>(
                "indent_based_object", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassInlineComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_comment> bindinline_comment
            = rulesNamespace.new_usertype<vili::parser::rules::inline_comment>(
                "inline_comment", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassInlineElement(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_element> bindinline_element
            = rulesNamespace.new_usertype<vili::parser::rules::inline_element>(
                "inline_element", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassInlineNode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_node> bindinline_node
            = rulesNamespace.new_usertype<vili::parser::rules::inline_node>(
                "inline_node", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassInteger(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::integer> bindinteger
            = rulesNamespace.new_usertype<vili::parser::rules::integer>(
                "integer", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassMultilineComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::multiline_comment> bindmultiline_comment
            = rulesNamespace.new_usertype<vili::parser::rules::multiline_comment>(
                "multiline_comment", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassMultilineCommentBlock(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::multiline_comment_block> bindmultiline_comment_block
            = rulesNamespace.new_usertype<vili::parser::rules::multiline_comment_block>(
                "multiline_comment_block", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassNode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::node> bindnode
            = rulesNamespace.new_usertype<vili::parser::rules::node>(
                "node", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassNumber(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::number> bindnumber
            = rulesNamespace.new_usertype<vili::parser::rules::number>(
                "number", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object> bindobject
            = rulesNamespace.new_usertype<vili::parser::rules::object>(
                "object", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassObjectElements(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object_elements> bindobject_elements
            = rulesNamespace.new_usertype<vili::parser::rules::object_elements>(
                "object_elements", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassObjectSeparator(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object_separator> bindobject_separator
            = rulesNamespace.new_usertype<vili::parser::rules::object_separator>(
                "object_separator", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassOpenArray(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::open_array> bindopen_array
            = rulesNamespace.new_usertype<vili::parser::rules::open_array>(
                "open_array", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassOpenObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::open_object> bindopen_object
            = rulesNamespace.new_usertype<vili::parser::rules::open_object>(
                "open_object", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassSign(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::sign> bindsign
            = rulesNamespace.new_usertype<vili::parser::rules::sign>(
                "sign", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassSpaceOrComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::space_or_comment> bindspace_or_comment
            = rulesNamespace.new_usertype<vili::parser::rules::space_or_comment>(
                "space_or_comment", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassString(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string> bindstring
            = rulesNamespace.new_usertype<vili::parser::rules::string>(
                "string", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassStringContent(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string_content> bindstring_content
            = rulesNamespace.new_usertype<vili::parser::rules::string_content>(
                "string_content", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassStringDelimiter(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string_delimiter> bindstring_delimiter
            = rulesNamespace.new_usertype<vili::parser::rules::string_delimiter>(
                "string_delimiter", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateBegin(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_begin> bindtemplate_begin
            = rulesNamespace.new_usertype<vili::parser::rules::template_begin>(
                "template_begin", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateDecl(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_decl> bindtemplate_decl
            = rulesNamespace.new_usertype<vili::parser::rules::template_decl>(
                "template_decl", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateDeclContent(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_decl_content> bindtemplate_decl_content
            = rulesNamespace.new_usertype<vili::parser::rules::template_decl_content>(
                "template_decl_content", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateIdentifier(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_identifier> bindtemplate_identifier
            = rulesNamespace.new_usertype<vili::parser::rules::template_identifier>(
                "template_identifier", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateIdentifierUsage(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_identifier_usage> bindtemplate_identifier_usage
            = rulesNamespace.new_usertype<vili::parser::rules::template_identifier_usage>(
                "template_identifier_usage", sol::call_constructor, sol::default_constructor,
                sol::base_classes, sol::bases<vili::parser::rules::template_identifier>());
    }
    void LoadClassTemplateKeyword(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_keyword> bindtemplate_keyword
            = rulesNamespace.new_usertype<vili::parser::rules::template_keyword>(
                "template_keyword", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateSpecialization(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_specialization> bindtemplate_specialization
            = rulesNamespace.new_usertype<vili::parser::rules::template_specialization>(
                "template_specialization", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTemplateUsage(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_usage> bindtemplate_usage
            = rulesNamespace.new_usertype<vili::parser::rules::template_usage>(
                "template_usage", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassTrue_(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::true_> bindtrue_
            = rulesNamespace.new_usertype<vili::parser::rules::true_>(
                "true_", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassUnescaped(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::unescaped> bindunescaped
            = rulesNamespace.new_usertype<vili::parser::rules::unescaped>(
                "unescaped", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassUnicode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::unicode> bindunicode
            = rulesNamespace.new_usertype<vili::parser::rules::unicode>(
                "unicode", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassViliGrammar(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::vili_grammar> bindvili_grammar
            = rulesNamespace.new_usertype<vili::parser::rules::vili_grammar>(
                "vili_grammar", sol::call_constructor, sol::default_constructor);
    }
    void LoadClassXdigit(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::xdigit> bindxdigit
            = rulesNamespace.new_usertype<vili::parser::rules::xdigit>(
                "xdigit", sol::call_constructor, sol::default_constructor);
    }
};

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
                "affectation");
    }
    void LoadClassAffectationSeparator(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::affectation_separator>
            bindaffectation_separator
            = rulesNamespace.new_usertype<vili::parser::rules::affectation_separator>(
                "affectation_separator");
    }
    void LoadClassArray(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array> bindarray
            = rulesNamespace.new_usertype<vili::parser::rules::array>("array");
    }
    void LoadClassArrayElements(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array_elements> bindarray_elements
            = rulesNamespace.new_usertype<vili::parser::rules::array_elements>(
                "array_elements");
    }
    void LoadClassArraySeparator(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array_separator> bindarray_separator
            = rulesNamespace.new_usertype<vili::parser::rules::array_separator>(
                "array_separator");
    }
    void LoadClassBlock(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::block> bindblock
            = rulesNamespace.new_usertype<vili::parser::rules::block>("block");
    }
    void LoadClassBoolean(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::boolean> bindboolean
            = rulesNamespace.new_usertype<vili::parser::rules::boolean>("boolean");
    }
    void LoadClassBraceBasedObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::brace_based_object> bindbrace_based_object
            = rulesNamespace.new_usertype<vili::parser::rules::brace_based_object>(
                "brace_based_object");
    }
    void LoadClassChar_(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::char_> bindchar_
            = rulesNamespace.new_usertype<vili::parser::rules::char_>("char_");
    }
    void LoadClassCloseArray(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::close_array> bindclose_array
            = rulesNamespace.new_usertype<vili::parser::rules::close_array>(
                "close_array");
    }
    void LoadClassCloseObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::close_object> bindclose_object
            = rulesNamespace.new_usertype<vili::parser::rules::close_object>(
                "close_object");
    }
    void LoadClassComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::comment> bindcomment
            = rulesNamespace.new_usertype<vili::parser::rules::comment>("comment");
    }
    void LoadClassData(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::data> binddata
            = rulesNamespace.new_usertype<vili::parser::rules::data>("data");
    }
    void LoadClassDigits(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::digits> binddigits
            = rulesNamespace.new_usertype<vili::parser::rules::digits>("digits");
    }
    void LoadClassElement(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::element> bindelement
            = rulesNamespace.new_usertype<vili::parser::rules::element>("element");
    }
    void LoadClassEmptyLine(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::empty_line> bindempty_line
            = rulesNamespace.new_usertype<vili::parser::rules::empty_line>("empty_line");
    }
    void LoadClassEndline(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::endline> bindendline
            = rulesNamespace.new_usertype<vili::parser::rules::endline>("endline");
    }
    void LoadClassEscaped(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::escaped> bindescaped
            = rulesNamespace.new_usertype<vili::parser::rules::escaped>("escaped");
    }
    void LoadClassEscapedChar(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::escaped_char> bindescaped_char
            = rulesNamespace.new_usertype<vili::parser::rules::escaped_char>(
                "escaped_char");
    }
    void LoadClassFalse_(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::false_> bindfalse_
            = rulesNamespace.new_usertype<vili::parser::rules::false_>("false_");
    }
    void LoadClassFloatingPoint(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::floating_point> bindfloating_point
            = rulesNamespace.new_usertype<vili::parser::rules::floating_point>(
                "floating_point");
    }
    void LoadClassFullNode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::full_node> bindfull_node
            = rulesNamespace.new_usertype<vili::parser::rules::full_node>("full_node");
    }
    void LoadClassGrammar(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::grammar> bindgrammar
            = rulesNamespace.new_usertype<vili::parser::rules::grammar>("grammar");
    }
    void LoadClassIdentifier(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::identifier> bindidentifier
            = rulesNamespace.new_usertype<vili::parser::rules::identifier>("identifier");
    }
    void LoadClassIndent(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::indent> bindindent
            = rulesNamespace.new_usertype<vili::parser::rules::indent>("indent");
    }
    void LoadClassIndentBasedObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::indent_based_object> bindindent_based_object
            = rulesNamespace.new_usertype<vili::parser::rules::indent_based_object>(
                "indent_based_object");
    }
    void LoadClassInlineComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_comment> bindinline_comment
            = rulesNamespace.new_usertype<vili::parser::rules::inline_comment>(
                "inline_comment");
    }
    void LoadClassInlineElement(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_element> bindinline_element
            = rulesNamespace.new_usertype<vili::parser::rules::inline_element>(
                "inline_element");
    }
    void LoadClassInlineNode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_node> bindinline_node
            = rulesNamespace.new_usertype<vili::parser::rules::inline_node>(
                "inline_node");
    }
    void LoadClassInteger(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::integer> bindinteger
            = rulesNamespace.new_usertype<vili::parser::rules::integer>("integer");
    }
    void LoadClassMultilineComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::multiline_comment> bindmultiline_comment
            = rulesNamespace.new_usertype<vili::parser::rules::multiline_comment>(
                "multiline_comment");
    }
    void LoadClassMultilineCommentBlock(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::multiline_comment_block>
            bindmultiline_comment_block
            = rulesNamespace.new_usertype<vili::parser::rules::multiline_comment_block>(
                "multiline_comment_block");
    }
    void LoadClassNode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::node> bindnode
            = rulesNamespace.new_usertype<vili::parser::rules::node>("node");
    }
    void LoadClassNumber(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::number> bindnumber
            = rulesNamespace.new_usertype<vili::parser::rules::number>("number");
    }
    void LoadClassObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object> bindobject
            = rulesNamespace.new_usertype<vili::parser::rules::object>("object");
    }
    void LoadClassObjectElements(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object_elements> bindobject_elements
            = rulesNamespace.new_usertype<vili::parser::rules::object_elements>(
                "object_elements");
    }
    void LoadClassObjectSeparator(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object_separator> bindobject_separator
            = rulesNamespace.new_usertype<vili::parser::rules::object_separator>(
                "object_separator");
    }
    void LoadClassOpenArray(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::open_array> bindopen_array
            = rulesNamespace.new_usertype<vili::parser::rules::open_array>("open_array");
    }
    void LoadClassOpenObject(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::open_object> bindopen_object
            = rulesNamespace.new_usertype<vili::parser::rules::open_object>(
                "open_object");
    }
    void LoadClassSign(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::sign> bindsign
            = rulesNamespace.new_usertype<vili::parser::rules::sign>("sign");
    }
    void LoadClassSpaceOrComment(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::space_or_comment> bindspace_or_comment
            = rulesNamespace.new_usertype<vili::parser::rules::space_or_comment>(
                "space_or_comment");
    }
    void LoadClassString(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string> bindstring
            = rulesNamespace.new_usertype<vili::parser::rules::string>("string");
    }
    void LoadClassStringContent(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string_content> bindstring_content
            = rulesNamespace.new_usertype<vili::parser::rules::string_content>(
                "string_content");
    }
    void LoadClassStringDelimiter(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string_delimiter> bindstring_delimiter
            = rulesNamespace.new_usertype<vili::parser::rules::string_delimiter>(
                "string_delimiter");
    }
    void LoadClassTemplateBegin(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_begin> bindtemplate_begin
            = rulesNamespace.new_usertype<vili::parser::rules::template_begin>(
                "template_begin");
    }
    void LoadClassTemplateDecl(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_decl> bindtemplate_decl
            = rulesNamespace.new_usertype<vili::parser::rules::template_decl>(
                "template_decl");
    }
    void LoadClassTemplateDeclContent(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_decl_content>
            bindtemplate_decl_content
            = rulesNamespace.new_usertype<vili::parser::rules::template_decl_content>(
                "template_decl_content");
    }
    void LoadClassTemplateIdentifier(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_identifier> bindtemplate_identifier
            = rulesNamespace.new_usertype<vili::parser::rules::template_identifier>(
                "template_identifier");
    }
    void LoadClassTemplateIdentifierUsage(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_identifier_usage>
            bindtemplate_identifier_usage
            = rulesNamespace.new_usertype<vili::parser::rules::template_identifier_usage>(
                "template_identifier_usage", sol::base_classes,
                sol::bases<vili::parser::rules::template_identifier>());
    }
    void LoadClassTemplateKeyword(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_keyword> bindtemplate_keyword
            = rulesNamespace.new_usertype<vili::parser::rules::template_keyword>(
                "template_keyword");
    }
    void LoadClassTemplateSpecialization(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_specialization>
            bindtemplate_specialization
            = rulesNamespace.new_usertype<vili::parser::rules::template_specialization>(
                "template_specialization");
    }
    void LoadClassTemplateUsage(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::template_usage> bindtemplate_usage
            = rulesNamespace.new_usertype<vili::parser::rules::template_usage>(
                "template_usage");
    }
    void LoadClassTrue_(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::true_> bindtrue_
            = rulesNamespace.new_usertype<vili::parser::rules::true_>("true_");
    }
    void LoadClassUnescaped(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::unescaped> bindunescaped
            = rulesNamespace.new_usertype<vili::parser::rules::unescaped>("unescaped");
    }
    void LoadClassUnicode(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::unicode> bindunicode
            = rulesNamespace.new_usertype<vili::parser::rules::unicode>("unicode");
    }
    void LoadClassViliGrammar(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::vili_grammar> bindvili_grammar
            = rulesNamespace.new_usertype<vili::parser::rules::vili_grammar>(
                "vili_grammar");
    }
    void LoadClassXdigit(sol::state_view state)
    {
        sol::table rulesNamespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::xdigit> bindxdigit
            = rulesNamespace.new_usertype<vili::parser::rules::xdigit>("xdigit");
    }
};
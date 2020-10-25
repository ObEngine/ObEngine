#pragma once

namespace sol
{
    class state_view;
};
namespace vili::parser::rules::Bindings
{
    void LoadClassAffectation(sol::state_view state);
    void LoadClassAffectationSeparator(sol::state_view state);
    void LoadClassArray(sol::state_view state);
    void LoadClassArrayElements(sol::state_view state);
    void LoadClassArraySeparator(sol::state_view state);
    void LoadClassBoolean(sol::state_view state);
    void LoadClassBraceBasedObject(sol::state_view state);
    void LoadClassChar_(sol::state_view state);
    void LoadClassCloseArray(sol::state_view state);
    void LoadClassCloseObject(sol::state_view state);
    void LoadClassData(sol::state_view state);
    void LoadClassDigits(sol::state_view state);
    void LoadClassElement(sol::state_view state);
    void LoadClassEmptyLine(sol::state_view state);
    void LoadClassEscaped(sol::state_view state);
    void LoadClassEscapedChar(sol::state_view state);
    void LoadClassFalse_(sol::state_view state);
    void LoadClassFloatingPoint(sol::state_view state);
    void LoadClassFullNode(sol::state_view state);
    void LoadClassGrammar(sol::state_view state);
    void LoadClassIdentifier(sol::state_view state);
    void LoadClassIndent(sol::state_view state);
    void LoadClassIndentBasedObject(sol::state_view state);
    void LoadClassInlineComment(sol::state_view state);
    void LoadClassInlineElement(sol::state_view state);
    void LoadClassInlineNode(sol::state_view state);
    void LoadClassInteger(sol::state_view state);
    void LoadClassLine(sol::state_view state);
    void LoadClassNode(sol::state_view state);
    void LoadClassNumber(sol::state_view state);
    void LoadClassObject(sol::state_view state);
    void LoadClassObjectElements(sol::state_view state);
    void LoadClassObjectSeparator(sol::state_view state);
    void LoadClassOpenArray(sol::state_view state);
    void LoadClassOpenObject(sol::state_view state);
    void LoadClassSign(sol::state_view state);
    void LoadClassString(sol::state_view state);
    void LoadClassStringContent(sol::state_view state);
    void LoadClassStringDelimiter(sol::state_view state);
    void LoadClassTemplateBegin(sol::state_view state);
    void LoadClassTemplateDecl(sol::state_view state);
    void LoadClassTemplateDeclContent(sol::state_view state);
    void LoadClassTemplateIdentifier(sol::state_view state);
    void LoadClassTemplateIdentifierUsage(sol::state_view state);
    void LoadClassTemplateKeyword(sol::state_view state);
    void LoadClassTemplateSpecialization(sol::state_view state);
    void LoadClassTemplateUsage(sol::state_view state);
    void LoadClassTrue_(sol::state_view state);
    void LoadClassUnescaped(sol::state_view state);
    void LoadClassUnicode(sol::state_view state);
    void LoadClassViliGrammar(sol::state_view state);
    void LoadClassXdigit(sol::state_view state);
};
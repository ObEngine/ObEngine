#include <Bindings/UtilsBindings.hpp>
#include <Utils/ExecUtils.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

#include <cmath>

#include <kaguya/kaguya.hpp>

#define UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE(fNamespace, funcName, func)                         \
    (*lua)["obe"][fNamespace][funcName] = kaguya::function(func<bool>);                            \
    (*lua)["obe"][fNamespace][funcName] = kaguya::function(func<int>);                             \
    (*lua)["obe"][fNamespace][funcName] = kaguya::function(func<double>);                          \
    (*lua)["obe"][fNamespace][funcName] = kaguya::function(func<std::string>)

namespace obe::Bindings::UtilsBindings
{
    void LoadExecUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["RunArgsParser"].setClass(
            kaguya::UserdataMetatable<Utils::Exec::RunArgsParser>()
                .addFunction("argumentExists", &Utils::Exec::RunArgsParser::argumentExists)
                .addFunction("getArgumentValue", &Utils::Exec::RunArgsParser::getArgumentValue));
    }

    void LoadFileUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["Filesystem"] = kaguya::NewTable();
        (*lua)["obe"]["Filesystem"]["getDirectoryList"]
            = kaguya::function(Utils::File::getDirectoryList);
        (*lua)["obe"]["Filesystem"]["getFileList"] = kaguya::function(Utils::File::getFileList);
        (*lua)["obe"]["Filesystem"]["fileExists"] = kaguya::function(Utils::File::fileExists);
        (*lua)["obe"]["Filesystem"]["directoryExists"]
            = kaguya::function(Utils::File::directoryExists);
        (*lua)["obe"]["Filesystem"]["createDirectory"]
            = kaguya::function(Utils::File::createDirectory);
        (*lua)["obe"]["Filesystem"]["createFile"] = kaguya::function(Utils::File::createFile);
        (*lua)["obe"]["Filesystem"]["copy"] = kaguya::function(Utils::File::copy);
        (*lua)["obe"]["Filesystem"]["deleteFile"] = kaguya::function(Utils::File::deleteFile);
        (*lua)["obe"]["Filesystem"]["deleteDirectory"]
            = kaguya::function(Utils::File::deleteDirectory);
        (*lua)["obe"]["Filesystem"]["getCurrentDirectory"]
            = kaguya::function(Utils::File::getCurrentDirectory);
        (*lua)["obe"]["Filesystem"]["separator"] = kaguya::function(Utils::File::separator);
    }

    void LoadMathUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["Math"] = kaguya::NewTable();
        (*lua)["obe"]["Math"]["randint"] = kaguya::function(Utils::Math::randint);
        (*lua)["obe"]["Math"]["randfloat"] = kaguya::function(Utils::Math::randfloat);
        (*lua)["obe"]["Math"]["getMin"] = kaguya::function(Utils::Math::getMin<double>);
        (*lua)["obe"]["Math"]["getMax"] = kaguya::function(Utils::Math::getMax<double>);
        (*lua)["obe"]["Math"]["isBetween"]
            = kaguya::function(Utils::Math::isBetween<double, double, double>);
        (*lua)["obe"]["Math"]["isDoubleInt"] = kaguya::function(Utils::Math::isDoubleInt);
        (*lua)["obe"]["Math"]["sign"] = kaguya::function(Utils::Math::sign<double>);
        (*lua)["obe"]["Math"]["atan2"]
            = kaguya::function(static_cast<double (*)(double, double)>(std::atan2));
        (*lua)["obe"]["Math"]["pi"] = Utils::Math::pi;
    }

    void loadStringUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["String"] = kaguya::NewTable();
        (*lua)["obe"]["String"]["split"] = kaguya::function(Utils::String::split);
        (*lua)["obe"]["String"]["occurencesInString"]
            = kaguya::function(Utils::String::occurencesInString);
        (*lua)["obe"]["String"]["isStringAlpha"] = kaguya::function(Utils::String::isStringAlpha);
        (*lua)["obe"]["String"]["isStringAlphaNumeric"]
            = kaguya::function(Utils::String::isStringAlphaNumeric);
        (*lua)["obe"]["String"]["isStringNumeric"]
            = kaguya::function(Utils::String::isStringNumeric);
        (*lua)["obe"]["String"]["isStringInt"] = kaguya::function(Utils::String::isStringInt);
        (*lua)["obe"]["String"]["isStringFloat"] = kaguya::function(Utils::String::isStringFloat);
        (*lua)["obe"]["String"]["replaceInPlace"] = kaguya::function(Utils::String::replaceInPlace);
        (*lua)["obe"]["String"]["replace"] = kaguya::function(Utils::String::replace);
        (*lua)["obe"]["String"]["isSurroundedBy"] = kaguya::function(Utils::String::isSurroundedBy);
        (*lua)["obe"]["String"]["getRandomKey"] = kaguya::function(Utils::String::getRandomKey);
        (*lua)["obe"]["String"]["contains"] = kaguya::function(Utils::String::contains);
        (*lua)["obe"]["String"]["Alphabet"] = Utils::String::Alphabet;
        (*lua)["obe"]["String"]["Numbers"] = Utils::String::Numbers;
    }

    void loadVectorUtils(kaguya::State* lua)
    {
        (*lua)["obe"]["Array"] = kaguya::NewTable();
        UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Array", "contains", Utils::Vector::contains);
        UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Array", "index", Utils::Vector::indexOfElement);
        UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Array", "eraseAll", Utils::Vector::eraseAll);
        UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Array", "sub", Utils::Vector::getSubVector);
        (*lua)["obe"]["Array"]["join"] = kaguya::function(Utils::Vector::join);
    }
} // namespace obe::Bindings::UtilsBindings
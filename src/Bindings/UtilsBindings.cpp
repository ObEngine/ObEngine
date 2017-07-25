#include <Bindings/UtilsBindings.hpp>
#include <Utils/ExecUtils.hpp>
#include <Utils/FileUtils.hpp>
#include <Utils/MathUtils.hpp>
#include <Utils/StringUtils.hpp>
#include "Utils/TypeUtils.hpp"

#define UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE(fNamespace, funcName, func) \
     (*lua)["Core"]["Utils"][fNamespace][funcName] = kaguya::function(func<bool>); \
     (*lua)["Core"]["Utils"][fNamespace][funcName] = kaguya::function(func<int>); \
     (*lua)["Core"]["Utils"][fNamespace][funcName] = kaguya::function(func<double>); \
     (*lua)["Core"]["Utils"][fNamespace][funcName] = kaguya::function(func<std::string>)

namespace obe
{
    namespace Bindings
    {
        void LoadExecUtils(kaguya::State* lua)
        {
            (*lua)["Core"]["Utils"]["Exec"]["RunArgsParser"].setClass(kaguya::UserdataMetatable<Utils::Exec::RunArgsParser>()
                .addFunction("argumentExists", &Utils::Exec::RunArgsParser::argumentExists)
                .addFunction("getArgumentValue", &Utils::Exec::RunArgsParser::getArgumentValue)
            );
        }

        void LoadFileUtils(kaguya::State* lua)
        {
            (*lua)["Core"]["Utils"]["File"]["getDirectoryList"] = kaguya::function(Utils::File::getDirectoryList);
            (*lua)["Core"]["Utils"]["File"]["getFileList"] = kaguya::function(Utils::File::getFileList);
            (*lua)["Core"]["Utils"]["File"]["fileExists"] = kaguya::function(Utils::File::fileExists);
            (*lua)["Core"]["Utils"]["File"]["directoryExists"] = kaguya::function(Utils::File::directoryExists);
            (*lua)["Core"]["Utils"]["File"]["createDirectory"] = kaguya::function(Utils::File::createDirectory);
            (*lua)["Core"]["Utils"]["File"]["createFile"] = kaguya::function(Utils::File::createFile);
            (*lua)["Core"]["Utils"]["File"]["copy"] = kaguya::function(Utils::File::copy);
            (*lua)["Core"]["Utils"]["File"]["deleteFile"] = kaguya::function(Utils::File::deleteFile);
            (*lua)["Core"]["Utils"]["File"]["deleteDirectory"] = kaguya::function(Utils::File::deleteDirectory);
            (*lua)["Core"]["Utils"]["File"]["getCurrentDirectory"] = kaguya::function(Utils::File::getCurrentDirectory);
            (*lua)["Core"]["Utils"]["File"]["separator"] = kaguya::function(Utils::File::separator);
        }

        void LoadMathUtils(kaguya::State* lua)
        {
            (*lua)["Core"]["Utils"]["Math"]["randint"] = kaguya::function(Utils::Math::randint);
            (*lua)["Core"]["Utils"]["Math"]["randfloat"] = kaguya::function(Utils::Math::randfloat);
            (*lua)["Core"]["Utils"]["Math"]["getMin"] = kaguya::function(Utils::Math::getMin<double>);
            (*lua)["Core"]["Utils"]["Math"]["getMax"] = kaguya::function(Utils::Math::getMax<double>);
            (*lua)["Core"]["Utils"]["Math"]["isBetween"] = kaguya::function(Utils::Math::isBetween<double, double, double>);
            (*lua)["Core"]["Utils"]["Math"]["isDoubleInt"] = kaguya::function(Utils::Math::isDoubleInt);
            (*lua)["Core"]["Utils"]["Math"]["sign"] = kaguya::function(Utils::Math::sign<double>);
        }

        void loadStringUtils(kaguya::State* lua)
        {
            (*lua)["Core"]["Utils"]["String"]["split"] = kaguya::function(Utils::String::split);
            (*lua)["Core"]["Utils"]["String"]["occurencesInString"] = kaguya::function(Utils::String::occurencesInString);
            (*lua)["Core"]["Utils"]["String"]["isStringAlpha"] = kaguya::function(Utils::String::isStringAlpha);
            (*lua)["Core"]["Utils"]["String"]["isStringAlphaNumeric"] = kaguya::function(Utils::String::isStringAlphaNumeric);
            (*lua)["Core"]["Utils"]["String"]["isStringNumeric"] = kaguya::function(Utils::String::isStringNumeric);
            (*lua)["Core"]["Utils"]["String"]["isStringInt"] = kaguya::function(Utils::String::isStringInt);
            (*lua)["Core"]["Utils"]["String"]["isStringFloat"] = kaguya::function(Utils::String::isStringFloat);
            (*lua)["Core"]["Utils"]["String"]["replaceInPlace"] = kaguya::function(Utils::String::replaceInPlace);
            (*lua)["Core"]["Utils"]["String"]["replace"] = kaguya::function(Utils::String::replace);
            (*lua)["Core"]["Utils"]["String"]["isSurroundedBy"] = kaguya::function(Utils::String::isSurroundedBy);
            (*lua)["Core"]["Utils"]["String"]["getRandomKey"] = kaguya::function(Utils::String::getRandomKey);
            (*lua)["Core"]["Utils"]["String"]["contains"] = kaguya::function(Utils::String::contains);
        }

        void loadVectorUtils(kaguya::State* lua)
        {
            UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Vector", "isInList", Utils::Vector::isInList);
            UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Vector", "indexOfElement", Utils::Vector::indexOfElement);
            UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Vector", "eraseAll", Utils::Vector::eraseAll);
            UTILS_BINDING_EXPOSE_TEMPLATE_MONOTYPE("Vector", "getSubVector", Utils::Vector::getSubVector);
            (*lua)["Core"]["Utils"]["Vector"]["join"] = kaguya::function(Utils::Vector::join);
        }
    }
}
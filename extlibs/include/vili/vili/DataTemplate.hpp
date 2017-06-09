#pragma once

#include "LinkAttribute.hpp"

namespace vili
{
    class AttributeConstraintManager
    {
    private:
        LinkAttribute m_attribute;
        std::vector<std::function<bool(BaseAttribute*)>> m_constraints;
    public:
        AttributeConstraintManager(ComplexAttribute* parent, std::string path);
        void addConstraint(std::function<bool(BaseAttribute*)> constraint);
        bool checkAllConstraints();
        LinkAttribute* getLinkAttribute();
        std::string getArgumentPath() const;
    };

    class DataTemplate
    {
    private:
        std::string m_name;
        std::vector<AttributeConstraintManager> m_signature;
        ComplexAttribute m_body;
        bool m_visible = true;
        bool m_signatureEnd = false;
        bool m_defaultLinkRoot = false;
        bool checkSignature();
    public:
        DataTemplate(const std::string& name);
        ComplexAttribute* getBody();
        void build(ComplexAttribute* parent, const std::string& id);
        void addConstraintManager(const AttributeConstraintManager& constraintManager, bool facultative = false);
        void useDefaultLinkRoot();
        unsigned int getArgumentCount() const;
        std::string getName() const;
        void setVisible(bool visible);
        bool isVisible();
    };
}

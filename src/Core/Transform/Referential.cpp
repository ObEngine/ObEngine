#include <Transform/Referential.hpp>
#include "vili/ErrorHandler.hpp"

namespace obe::Transform
{
    Referential reverseReferential(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return Referential::BottomRight;
        case Referential::Top: return Referential::Bottom;
        case Referential::TopRight: return Referential::BottomLeft;
        case Referential::Left: return Referential::Right;
        case Referential::Center: return Referential::Center;
        case Referential::Right: return Referential::Left;
        case Referential::BottomLeft: return Referential::TopRight;
        case Referential::Bottom: return Referential::Top;
        case Referential::BottomRight: return Referential::TopLeft;
        default: return Referential::Center;
        }
    }

    Referential horizontallyReverseReferential(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return Referential::TopRight;
        case Referential::Top: return Referential::Top;
        case Referential::TopRight: return Referential::TopLeft;
        case Referential::Left: return Referential::Right;
        case Referential::Center: return Referential::Center;
        case Referential::Right: return Referential::Left;
        case Referential::BottomLeft: return Referential::BottomRight;
        case Referential::Bottom: return Referential::Bottom;
        case Referential::BottomRight: return Referential::BottomLeft;
        default: return Referential::Center;
        }
    }

    Referential verticallyReverseReferential(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return Referential::BottomLeft;
        case Referential::Top: return Referential::Bottom;
        case Referential::TopRight: return Referential::BottomRight;
        case Referential::Left: return Referential::Left;
        case Referential::Center: return Referential::Center;
        case Referential::Right: return Referential::Right;
        case Referential::BottomLeft: return Referential::TopLeft;
        case Referential::Bottom: return Referential::Top;
        case Referential::BottomRight: return Referential::TopRight;
        default: return Referential::Center;
        }
    }

    bool isOnLeftSide(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return true;
        case Referential::Top: return false;
        case Referential::TopRight: return false;
        case Referential::Left: return true;
        case Referential::Center: return false;
        case Referential::Right: return false;
        case Referential::BottomLeft: return true;
        case Referential::Bottom: return false;
        case Referential::BottomRight: return false;
        default: return false;
        }
    }

    bool isOnRightSide(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return false;
        case Referential::Top: return false;
        case Referential::TopRight: return true;
        case Referential::Left: return false;
        case Referential::Center: return false;
        case Referential::Right: return true;
        case Referential::BottomLeft: return false;
        case Referential::Bottom: return false;
        case Referential::BottomRight: return true;
        default: return false;
        }
    }

    bool isOnTopSide(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return true;
        case Referential::Top: return true;
        case Referential::TopRight: return true;
        case Referential::Left: return false;
        case Referential::Center: return false;
        case Referential::Right: return false;
        case Referential::BottomLeft: return false;
        case Referential::Bottom: return false;
        case Referential::BottomRight: return false;
        default: return false;
        }
    }

    bool isOnBottomSide(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return false;
        case Referential::Top: return false;
        case Referential::TopRight: return false;
        case Referential::Left: return false;
        case Referential::Center: return false;
        case Referential::Right: return false;
        case Referential::BottomLeft: return true;
        case Referential::Bottom: return true;
        case Referential::BottomRight: return true;
        default: return false;
        }
    }

    bool isOnCorner(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return true;
        case Referential::Top: return false;
        case Referential::TopRight: return true;
        case Referential::Left: return false;
        case Referential::Center: return false;
        case Referential::Right: return false;
        case Referential::BottomLeft: return true;
        case Referential::Bottom: return false;
        case Referential::BottomRight: return true;
        default: return false;
        }
    }

    bool isOnSide(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return false;
        case Referential::Top: return true;
        case Referential::TopRight: return false;
        case Referential::Left: return true;
        case Referential::Center: return false;
        case Referential::Right: return true;
        case Referential::BottomLeft: return false;
        case Referential::Bottom: return true;
        case Referential::BottomRight: return false;
        default: return false;
        }
    }

    UnitVector getReferentialOffset(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft:
            return UnitVector(1, 1);
        case Referential::Top:
            return UnitVector(0, 1);
        case Referential::TopRight:
            return UnitVector(-1, 1);
        case Referential::Left:
            return UnitVector(1, 0);
        case Referential::Center:
            return UnitVector(0, 0);
        case Referential::Right:
            return UnitVector(-1, 0);
        case Referential::BottomLeft:
            return UnitVector(1, -1);
        case Referential::Bottom:
            return UnitVector(0, -1);
        case Referential::BottomRight:
            return UnitVector(-1, -1);
        default:
            return UnitVector(0, 0);
        }
    }

    std::string referentialToString(Referential ref)
    {
        switch (ref)
        {
        case Referential::TopLeft: return "TopLeft";
        case Referential::Top: return "Top";
        case Referential::TopRight: return "TopRight";
        case Referential::Left: return "Left";
        case Referential::Center: return "Center";
        case Referential::Right: return "Right";
        case Referential::BottomLeft: return "BottomLeft";
        case Referential::Bottom: return "Bottom";
        case Referential::BottomRight: return "BottomRight";
        default: return "Error";
        }
    }

    Referential stringToReferential(const std::string& ref)
    {
        if (ref == "TopLeft")
            return Referential::TopLeft;
        if (ref == "Top")
            return Referential::Top;
        if (ref == "TopRight")
            return Referential::TopRight;
        if (ref == "Left")
            return Referential::Left;
        if (ref == "Center")
            return Referential::Center;
        if (ref == "Right")
            return Referential::Right;
        if (ref == "BottomLeft")
            return Referential::BottomLeft;
        if (ref == "Bottom")
            return Referential::Bottom;
        if (ref == "BottomRight")
            return Referential::BottomRight;
        throw aube::ErrorHandler::Raise("ObEngine.Transform.Referential.UnknownReferential", { {"referential", ref} });
    }

    std::ostream& operator<<(std::ostream& os, Referential m)
    {
        os << referentialToString(m);
        return os;
    }
}
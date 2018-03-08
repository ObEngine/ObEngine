#include <Transform/Referencial.hpp>
#include "vili/ErrorHandler.hpp"

namespace obe::Transform
{
    Referencial reverseReferencial(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return Referencial::BottomRight;
        case Referencial::Top: return Referencial::Bottom;
        case Referencial::TopRight: return Referencial::BottomLeft;
        case Referencial::Left: return Referencial::Right;
        case Referencial::Center: return Referencial::Center;
        case Referencial::Right: return Referencial::Left;
        case Referencial::BottomLeft: return Referencial::TopRight;
        case Referencial::Bottom: return Referencial::Top;
        case Referencial::BottomRight: return Referencial::TopLeft;
        default: return Referencial::Center;
        }
    }

    Referencial horizontallyReverseReferencial(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return Referencial::TopRight;
        case Referencial::Top: return Referencial::Top;
        case Referencial::TopRight: return Referencial::TopLeft;
        case Referencial::Left: return Referencial::Right;
        case Referencial::Center: return Referencial::Center;
        case Referencial::Right: return Referencial::Left;
        case Referencial::BottomLeft: return Referencial::BottomRight;
        case Referencial::Bottom: return Referencial::Bottom;
        case Referencial::BottomRight: return Referencial::BottomLeft;
        default: return Referencial::Center;
        }
    }

    Referencial verticallyReverseReferencial(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return Referencial::BottomLeft;
        case Referencial::Top: return Referencial::Bottom;
        case Referencial::TopRight: return Referencial::BottomRight;
        case Referencial::Left: return Referencial::Left;
        case Referencial::Center: return Referencial::Center;
        case Referencial::Right: return Referencial::Right;
        case Referencial::BottomLeft: return Referencial::TopLeft;
        case Referencial::Bottom: return Referencial::Top;
        case Referencial::BottomRight: return Referencial::TopRight;
        default: return Referencial::Center;
        }
    }

    bool isOnLeftSide(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return true;
        case Referencial::Top: return false;
        case Referencial::TopRight: return false;
        case Referencial::Left: return true;
        case Referencial::Center: return false;
        case Referencial::Right: return false;
        case Referencial::BottomLeft: return true;
        case Referencial::Bottom: return false;
        case Referencial::BottomRight: return false;
        default: return false;
        }
    }

    bool isOnRightSide(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return false;
        case Referencial::Top: return false;
        case Referencial::TopRight: return true;
        case Referencial::Left: return false;
        case Referencial::Center: return false;
        case Referencial::Right: return true;
        case Referencial::BottomLeft: return false;
        case Referencial::Bottom: return false;
        case Referencial::BottomRight: return true;
        default: return false;
        }
    }

    bool isOnTopSide(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return true;
        case Referencial::Top: return true;
        case Referencial::TopRight: return true;
        case Referencial::Left: return false;
        case Referencial::Center: return false;
        case Referencial::Right: return false;
        case Referencial::BottomLeft: return false;
        case Referencial::Bottom: return false;
        case Referencial::BottomRight: return false;
        default: return false;
        }
    }

    bool isOnBottomSide(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return false;
        case Referencial::Top: return false;
        case Referencial::TopRight: return false;
        case Referencial::Left: return false;
        case Referencial::Center: return false;
        case Referencial::Right: return false;
        case Referencial::BottomLeft: return true;
        case Referencial::Bottom: return true;
        case Referencial::BottomRight: return true;
        default: return false;
        }
    }

    bool isOnCorner(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return true;
        case Referencial::Top: return false;
        case Referencial::TopRight: return true;
        case Referencial::Left: return false;
        case Referencial::Center: return false;
        case Referencial::Right: return false;
        case Referencial::BottomLeft: return true;
        case Referencial::Bottom: return false;
        case Referencial::BottomRight: return true;
        default: return false;
        }
    }

    bool isOnSide(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return false;
        case Referencial::Top: return true;
        case Referencial::TopRight: return false;
        case Referencial::Left: return true;
        case Referencial::Center: return false;
        case Referencial::Right: return true;
        case Referencial::BottomLeft: return false;
        case Referencial::Bottom: return true;
        case Referencial::BottomRight: return false;
        default: return false;
        }
    }

    UnitVector getReferencialOffset(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft:
            return UnitVector(1, 1);
        case Referencial::Top:
            return UnitVector(0, 1);
        case Referencial::TopRight:
            return UnitVector(-1, 1);
        case Referencial::Left:
            return UnitVector(1, 0);
        case Referencial::Center:
            return UnitVector(0, 0);
        case Referencial::Right:
            return UnitVector(-1, 0);
        case Referencial::BottomLeft:
            return UnitVector(1, -1);
        case Referencial::Bottom:
            return UnitVector(0, -1);
        case Referencial::BottomRight:
            return UnitVector(-1, -1);
        default:
            return UnitVector(0, 0);
        }
    }

    std::string referencialToString(Referencial ref)
    {
        switch (ref)
        {
        case Referencial::TopLeft: return "TopLeft";
        case Referencial::Top: return "Top";
        case Referencial::TopRight: return "TopRight";
        case Referencial::Left: return "Left";
        case Referencial::Center: return "Center";
        case Referencial::Right: return "Right";
        case Referencial::BottomLeft: return "BottomLeft";
        case Referencial::Bottom: return "Bottom";
        case Referencial::BottomRight: return "BottomRight";
        default: return "Error";
        }
    }

    Referencial stringToReferencial(const std::string& ref)
    {
        if (ref == "TopLeft")
            return Referencial::TopLeft;
        if (ref == "Top")
            return Referencial::Top;
        if (ref == "TopRight")
            return Referencial::TopRight;
        if (ref == "Left")
            return Referencial::Left;
        if (ref == "Center")
            return Referencial::Center;
        if (ref == "Right")
            return Referencial::Right;
        if (ref == "BottomLeft")
            return Referencial::BottomLeft;
        if (ref == "Bottom")
            return Referencial::Bottom;
        if (ref == "BottomRight")
            return Referencial::BottomRight;
        throw aube::ErrorHandler::Raise("ObEngine.Transform.Referencial.UnknownReferencial", { {"referencial", ref} });
    }

    std::ostream& operator<<(std::ostream& os, Referencial m)
    {
        os << referencialToString(m);
        return os;
    }
}
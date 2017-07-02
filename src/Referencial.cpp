#include "Referencial.hpp"

namespace obe
{
    namespace Coord
    {
        std::string referencialToString(Referencial ref)
        {
            switch (ref)
            {
            case Referencial::TopLeft: return "TopLeft"; break;
            case Referencial::Top: return "Top"; break;
            case Referencial::TopRight: return "TopRight"; break;
            case Referencial::Left: return "Left"; break;
            case Referencial::Center: return "Center"; break;
            case Referencial::Right: return "Right"; break;
            case Referencial::BottomLeft: return "BottomLeft"; break;
            case Referencial::Bottom: return "Bottom"; break;
            case Referencial::BottomRight: return "BottomRight"; break;
            default: return "Error";
            }
        }
        std::ostream& operator<<(std::ostream& os, Referencial m)
        {
            os << referencialToString(m).c_str();
            return os;
        }
    }
}
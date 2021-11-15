#include "geometryelement.h"
#include "parser.h"
#include "layoutcontext.h"

#include <cmath>

namespace lunasvg {

GeometryElement::GeometryElement(ElementId id)
    : GraphicsElement(id)
{
}

void GeometryElement::layout(LayoutContext* context, LayoutContainer* current) const
{
    if(isDisplayNone())
        return;

    auto path = this->path();
    if(path.empty())
        return;

    auto shape = std::make_unique<LayoutShape>();
    shape->path = std::move(path);
    shape->transform = transform();
    shape->fillData = context->fillData(this);
    shape->strokeData = context->strokeData(this);
    shape->markerData = context->markerData(this, shape->path);
    shape->visibility = visibility();
    shape->clipRule = clip_rule();
    shape->masker = context->getMasker(mask());
    shape->clipper = context->getClipper(clip_path());
    current->addChild(std::move(shape));
}

PathElement::PathElement()
    : GeometryElement(ElementId::Path)
{
}

Path PathElement::d() const
{
    auto& value = get(PropertyId::D);
    return Parser::parsePath(value);
}

Path PathElement::path() const
{
    return d();
}

std::unique_ptr<Node> PathElement::clone() const
{
    return cloneElement<PathElement>();
}

PolyElement::PolyElement(ElementId id)
    : GeometryElement(id)
{
}

PointList PolyElement::points() const
{
    auto& value = get(PropertyId::Points);
    return Parser::parsePointList(value);
}

PolygonElement::PolygonElement()
    : PolyElement(ElementId::Polygon)
{
}

Path PolygonElement::path() const
{
    auto points = this->points();
    if(points.empty())
        return Path{};

    Path path;
    path.moveTo(points[0].x, points[0].y);
    for(std::size_t i = 1;i < points.size();i++)
        path.lineTo(points[i].x, points[i].y);

    path.close();
    return path;
}

std::unique_ptr<Node> PolygonElement::clone() const
{
    return cloneElement<PolygonElement>();
}

PolylineElement::PolylineElement()
    : PolyElement(ElementId::Polyline)
{
}

Path PolylineElement::path() const
{
    auto points = this->points();
    if(points.empty())
        return Path{};

    Path path;
    path.moveTo(points[0].x, points[0].y);
    for(std::size_t i = 1;i < points.size();i++)
        path.lineTo(points[i].x, points[i].y);

    return path;
}

std::unique_ptr<Node> PolylineElement::clone() const
{
    return cloneElement<PolylineElement>();
}

CircleElement::CircleElement()
    : GeometryElement(ElementId::Circle)
{
}

Length CircleElement::cx() const
{
    auto& value = get(PropertyId::Cx);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length CircleElement::cy() const
{
    auto& value = get(PropertyId::Cy);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length CircleElement::r() const
{
    auto& value = get(PropertyId::R);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Zero);
}

Path CircleElement::path() const
{
    auto r = this->r();
    if(r.isZero())
        return Path{};

    LengthContext lengthContext(this);
    auto _cx = lengthContext.valueForLength(cx(), LengthMode::Width);
    auto _cy = lengthContext.valueForLength(cy(), LengthMode::Height);
    auto _r = lengthContext.valueForLength(r, LengthMode::Both);

    Path path;
    path.ellipse(_cx, _cy, _r, _r);
    return path;
}

std::unique_ptr<Node> CircleElement::clone() const
{
    return cloneElement<CircleElement>();
}

EllipseElement::EllipseElement()
    : GeometryElement(ElementId::Ellipse)
{
}

Length EllipseElement::cx() const
{
    auto& value = get(PropertyId::Cx);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length EllipseElement::cy() const
{
    auto& value = get(PropertyId::Cy);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length EllipseElement::rx() const
{
    auto& value = get(PropertyId::Rx);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Zero);
}

Length EllipseElement::ry() const
{
    auto& value = get(PropertyId::Ry);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Zero);
}

Path EllipseElement::path() const
{
    auto rx = this->rx();
    auto ry = this->ry();
    if(rx.isZero() || ry.isZero())
        return Path{};

    LengthContext lengthContext(this);
    auto _cx = lengthContext.valueForLength(cx(), LengthMode::Width);
    auto _cy = lengthContext.valueForLength(cy(), LengthMode::Height);
    auto _rx = lengthContext.valueForLength(rx, LengthMode::Width);
    auto _ry = lengthContext.valueForLength(ry, LengthMode::Height);

    Path path;
    path.ellipse(_cx, _cy, _rx, _ry);
    return path;
}

std::unique_ptr<Node> EllipseElement::clone() const
{
    return cloneElement<EllipseElement>();
}

LineElement::LineElement()
    : GeometryElement(ElementId::Line)
{
}

Length LineElement::x1() const
{
    auto& value = get(PropertyId::X1);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length LineElement::y1() const
{
    auto& value = get(PropertyId::Y1);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length LineElement::x2() const
{
    auto& value = get(PropertyId::X2);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length LineElement::y2() const
{
    auto& value = get(PropertyId::Y2);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Path LineElement::path() const
{
    LengthContext lengthContext(this);
    auto _x1 = lengthContext.valueForLength(x1(), LengthMode::Width);
    auto _y1 = lengthContext.valueForLength(y1(), LengthMode::Height);
    auto _x2 = lengthContext.valueForLength(x2(), LengthMode::Width);
    auto _y2 = lengthContext.valueForLength(y2(), LengthMode::Height);

    Path path;
    path.moveTo(_x1, _y1);
    path.lineTo(_x2, _y2);
    return path;
}

std::unique_ptr<Node> LineElement::clone() const
{
    return cloneElement<LineElement>();
}

RectElement::RectElement()
    : GeometryElement(ElementId::Rect)
{
}

Length RectElement::x() const
{
    auto& value = get(PropertyId::X);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length RectElement::y() const
{
    auto& value = get(PropertyId::Y);
    return Parser::parseLength(value, AllowNegativeLengths, Length::Zero);
}

Length RectElement::rx() const
{
    auto& value = get(PropertyId::Rx);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Unknown);
}

Length RectElement::ry() const
{
    auto& value = get(PropertyId::Ry);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Unknown);
}

Length RectElement::width() const
{
    auto& value = get(PropertyId::Width);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Zero);
}

Length RectElement::height() const
{
    auto& value = get(PropertyId::Height);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::Zero);
}

Path RectElement::path() const
{
    auto w = this->width();
    auto h = this->height();
    if(w.isZero() || h.isZero())
        return Path{};

    LengthContext lengthContext(this);
    auto _x = lengthContext.valueForLength(x(), LengthMode::Width);
    auto _y = lengthContext.valueForLength(y(), LengthMode::Height);
    auto _w = lengthContext.valueForLength(w, LengthMode::Width);
    auto _h = lengthContext.valueForLength(h, LengthMode::Height);

    auto rx = this->rx();
    auto ry = this->ry();

    auto _rx = lengthContext.valueForLength(rx, LengthMode::Width);
    auto _ry = lengthContext.valueForLength(ry, LengthMode::Height);

    if(!rx.isValid()) _rx = _ry;
    if(!ry.isValid()) _ry = _rx;

    Path path;
    path.rect(_x, _y, _w, _h, _rx, _ry);
    return path;
}

std::unique_ptr<Node> RectElement::clone() const
{
    return cloneElement<RectElement>();
}

} // namespace lunasvg

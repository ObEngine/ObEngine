#include "maskelement.h"
#include "parser.h"
#include "layoutcontext.h"

namespace lunasvg {

MaskElement::MaskElement()
    : StyledElement(ElementId::Mask)
{
}

Length MaskElement::x() const
{
    auto& value = get(PropertyId::X);
    return Parser::parseLength(value, AllowNegativeLengths, Length::MinusTenPercent);
}

Length MaskElement::y() const
{
    auto& value = get(PropertyId::Y);
    return Parser::parseLength(value, AllowNegativeLengths, Length::MinusTenPercent);
}

Length MaskElement::width() const
{
    auto& value = get(PropertyId::Width);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::OneTwentyPercent);
}

Length MaskElement::height() const
{
    auto& value = get(PropertyId::Height);
    return Parser::parseLength(value, ForbidNegativeLengths, Length::OneTwentyPercent);
}

Units MaskElement::maskUnits() const
{
    auto& value = get(PropertyId::MaskUnits);
    return Parser::parseUnits(value, Units::ObjectBoundingBox);
}

Units MaskElement::maskContentUnits() const
{
    auto& value = get(PropertyId::MaskContentUnits);
    return Parser::parseUnits(value, Units::UserSpaceOnUse);
}

std::unique_ptr<LayoutMask> MaskElement::getMasker(LayoutContext* context) const
{
    auto w = this->width();
    auto h = this->height();
    if(w.isZero() || h.isZero() || context->hasReference(this))
        return nullptr;

    LayoutBreaker layoutBreaker(context, this);
    auto masker = std::make_unique<LayoutMask>();
    masker->units = maskUnits();
    masker->contentUnits = maskContentUnits();
    masker->opacity = opacity();
    masker->clipper = context->getClipper(clip_path());
    masker->masker = context->getMasker(mask());

    LengthContext lengthContext(this, maskUnits());
    masker->x = lengthContext.valueForLength(x(), LengthMode::Width);
    masker->y = lengthContext.valueForLength(y(), LengthMode::Height);
    masker->width = lengthContext.valueForLength(w, LengthMode::Width);
    masker->height = lengthContext.valueForLength(h, LengthMode::Height);
    layoutChildren(context, masker.get());
    return masker;
}

std::unique_ptr<Node> MaskElement::clone() const
{
    return cloneElement<MaskElement>();
}

} // namespace lunasvg

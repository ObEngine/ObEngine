#include "Rect.hpp"
#include "Camera.hpp"

namespace obe
{
	namespace Coord
	{
		void Rect::transformRef(UnitVector& vec, Referencial ref, ConversionType type) const
		{
			double factor = (type == From) ? 1.0 : -1.0;
			switch (ref)
			{
			case TopLeft: break;
			case Top: vec.add(factor * m_size.to(vec.unit).x / 2, 0); break;
			case TopRight: vec.add(factor * m_size.to(vec.unit).x, 0); break;
			case Left: vec.add(0, factor * m_size.to(vec.unit).y / 2); break;
			case Center: vec.add(factor * m_size.to(vec.unit).x / 2, factor * m_size.to(vec.unit).y / 2); break;
			case Right: vec.add(factor * m_size.to(vec.unit).x, factor * m_size.to(vec.unit).y / 2); break;
			case BottomLeft: vec.add(0, factor * m_size.to(vec.unit).y); break;
			case Bottom: vec.add(factor * m_size.to(vec.unit).x / 2, factor * m_size.to(vec.unit).y); break;
			case BottomRight: vec.add(factor * m_size.to(vec.unit).x, factor * m_size.to(vec.unit).y); break;
			default: break;
			}
		}

		void Rect::setPosition(const Coord::UnitVector& position, Referencial ref)
		{
			Coord::UnitVector pVec = position.to<Coord::WorldUnits>();
			this->transformRef(pVec, ref, To);
			this->setPosition(pVec.x, pVec.y);
		}

		void Rect::setPosition(double x, double y, Referencial ref)
		{
			this->setPosition(UnitVector(x, y, WorldUnits), ref);
		}

		void Rect::move(const Coord::UnitVector& position)
		{
			m_position += position;
		}

		void Rect::move(double x, double y)
		{
			m_position.add(x, y);
		}

		void Rect::setX(double x, Referencial ref)
		{
			UnitVector vec(x, 0, WorldUnits);
			this->transformRef(vec, ref, To);
			m_position.x = vec.x;
		}

		void Rect::setY(double y, Referencial ref)
		{
			UnitVector vec(0, y, WorldUnits);
			this->transformRef(vec, ref, To);
			m_position.y = vec.y;
		}

		void Rect::setSize(double width, double height)
		{
			m_size.set(width, height);
		}

		void Rect::scale(const UnitVector& size)
		{
			m_size.add(size);
		}

		void Rect::scale(double width, double height)
		{
			m_size *= UnitVector(width, height, m_size.unit);
		}

		void Rect::setWidth(double width)
		{
			m_size.x = width;
		}

		void Rect::setHeight(double height)
		{
			m_size.y = height;
		}

		UnitVector Rect::getPosition(Referencial ref) const
		{
			UnitVector getPosVec = m_position;
			this->transformRef(getPosVec, ref, From);
			return getPosVec;
		}

		void Rect::setSize(const UnitVector& size)
		{
			m_size.set(size);
		}

		UnitVector Rect::getSize() const
		{
			return m_size;
		}

		double Rect::getX(Referencial ref) const
		{
			return this->getPosition(ref).x;
		}

		double Rect::getY(Referencial ref) const
		{
			return this->getPosition(ref).y;
		}

		double Rect::getWidth() const
		{
			return m_size.x;
		}

		double Rect::getHeight() const
		{
			return m_size.y;
		}
	}
}

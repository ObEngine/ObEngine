////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2022 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderTarget.hpp>
#include <sfe/SpannableVertexArray.hpp>


namespace sfe
{
////////////////////////////////////////////////////////////
SpannableVertexArray::SpannableVertexArray() : m_vertices(), m_primitiveType(sf::PrimitiveType::Points)
{
}


////////////////////////////////////////////////////////////
SpannableVertexArray::SpannableVertexArray(sf::PrimitiveType type, std::size_t vertexCount) : m_vertices(vertexCount), m_primitiveType(type)
{
}


////////////////////////////////////////////////////////////
std::size_t SpannableVertexArray::getVertexCount() const
{
    return m_vertices.size();
}


////////////////////////////////////////////////////////////
sf::Vertex& SpannableVertexArray::operator[](std::size_t index)
{
    return m_vertices[index];
}


////////////////////////////////////////////////////////////
const sf::Vertex& SpannableVertexArray::operator[](std::size_t index) const
{
    return m_vertices[index];
}


////////////////////////////////////////////////////////////
void SpannableVertexArray::clear()
{
    m_vertices.clear();
    m_end = 0;
}


////////////////////////////////////////////////////////////
void SpannableVertexArray::resize(std::size_t vertexCount)
{
    m_vertices.resize(vertexCount);
    m_end = m_vertices.size();
}


////////////////////////////////////////////////////////////
void SpannableVertexArray::append(const sf::Vertex& vertex)
{
    m_vertices.push_back(vertex);
    m_end = m_vertices.size();
}


////////////////////////////////////////////////////////////
void SpannableVertexArray::setPrimitiveType(sf::PrimitiveType type)
{
    m_primitiveType = type;
}


////////////////////////////////////////////////////////////
sf::PrimitiveType SpannableVertexArray::getPrimitiveType() const
{
    return m_primitiveType;
}


////////////////////////////////////////////////////////////
sf::FloatRect SpannableVertexArray::getBounds() const
{
    if (!m_vertices.empty())
    {
        float left   = m_vertices[0].position.x;
        float top    = m_vertices[0].position.y;
        float right  = m_vertices[0].position.x;
        float bottom = m_vertices[0].position.y;

        for (std::size_t i = 1; i < m_vertices.size(); ++i)
        {
            sf::Vector2f position = m_vertices[i].position;

            // Update left and right
            if (position.x < left)
                left = position.x;
            else if (position.x > right)
                right = position.x;

            // Update top and bottom
            if (position.y < top)
                top = position.y;
            else if (position.y > bottom)
                bottom = position.y;
        }

        return sf::FloatRect({left, top}, {right - left, bottom - top});
    }
    else
    {
        // Array is empty
        return sf::FloatRect();
    }
}

void SpannableVertexArray::setSpan(std::size_t start, std::size_t end)
{
    m_start = start;
    m_end = end;
}


////////////////////////////////////////////////////////////
void SpannableVertexArray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_vertices.empty())
        target.draw(m_vertices.data() + m_start, m_end - m_start, m_primitiveType, states);
}

} // namespace sf

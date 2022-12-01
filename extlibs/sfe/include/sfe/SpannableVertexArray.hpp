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

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>


namespace sfe
{
////////////////////////////////////////////////////////////
/// \brief Define a set of one or more 2D primitives
///
////////////////////////////////////////////////////////////
class SpannableVertexArray : public sf::Drawable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty vertex array.
    ///
    ////////////////////////////////////////////////////////////
    SpannableVertexArray();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vertex array with a type and an initial number of vertices
    ///
    /// \param type        Type of primitives
    /// \param vertexCount Initial number of vertices in the array
    ///
    ////////////////////////////////////////////////////////////
    explicit SpannableVertexArray(sf::PrimitiveType type, std::size_t vertexCount = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Return the vertex count
    ///
    /// \return Number of vertices in the array
    ///
    ////////////////////////////////////////////////////////////
    std::size_t getVertexCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get a read-write access to a vertex by its index
    ///
    /// This function doesn't check \a index, it must be in range
    /// [0, getVertexCount() - 1]. The behavior is undefined
    /// otherwise.
    ///
    /// \param index Index of the vertex to get
    ///
    /// \return Reference to the index-th vertex
    ///
    /// \see getVertexCount
    ///
    ////////////////////////////////////////////////////////////
    sf::Vertex& operator[](std::size_t index);

    ////////////////////////////////////////////////////////////
    /// \brief Get a read-only access to a vertex by its index
    ///
    /// This function doesn't check \a index, it must be in range
    /// [0, getVertexCount() - 1]. The behavior is undefined
    /// otherwise.
    ///
    /// \param index Index of the vertex to get
    ///
    /// \return Const reference to the index-th vertex
    ///
    /// \see getVertexCount
    ///
    ////////////////////////////////////////////////////////////
    const sf::Vertex& operator[](std::size_t index) const;

    ////////////////////////////////////////////////////////////
    /// \brief Clear the vertex array
    ///
    /// This function removes all the vertices from the array.
    /// It doesn't deallocate the corresponding memory, so that
    /// adding new vertices after clearing doesn't involve
    /// reallocating all the memory.
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Resize the vertex array
    ///
    /// If \a vertexCount is greater than the current size, the previous
    /// vertices are kept and new (default-constructed) vertices are
    /// added.
    /// If \a vertexCount is less than the current size, existing vertices
    /// are removed from the array.
    ///
    /// \param vertexCount New size of the array (number of vertices)
    ///
    ////////////////////////////////////////////////////////////
    void resize(std::size_t vertexCount);

    ////////////////////////////////////////////////////////////
    /// \brief Add a vertex to the array
    ///
    /// \param vertex Vertex to add
    ///
    ////////////////////////////////////////////////////////////
    void append(const sf::Vertex& vertex);

    ////////////////////////////////////////////////////////////
    /// \brief Set the type of primitives to draw
    ///
    /// This function defines how the vertices must be interpreted
    /// when it's time to draw them:
    /// \li As points
    /// \li As lines
    /// \li As triangles
    /// The default primitive type is sf::Points.
    ///
    /// \param type Type of primitive
    ///
    ////////////////////////////////////////////////////////////
    void setPrimitiveType(sf::PrimitiveType type);

    ////////////////////////////////////////////////////////////
    /// \brief Get the type of primitives drawn by the vertex array
    ///
    /// \return Primitive type
    ///
    ////////////////////////////////////////////////////////////
    sf::PrimitiveType getPrimitiveType() const;

    ////////////////////////////////////////////////////////////
    /// \brief Compute the bounding rectangle of the vertex array
    ///
    /// This function returns the minimal axis-aligned rectangle
    /// that contains all the vertices of the array.
    ///
    /// \return Bounding rectangle of the vertex array
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect getBounds() const;

    void setSpan(std::size_t start, std::size_t end);

    ////////////////////////////////////////////////////////////
    /// \brief Draw the vertex array to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<sf::Vertex> m_vertices;      //!< Vertices contained in the array
    sf::PrimitiveType       m_primitiveType; //!< Type of primitives to draw
    std::size_t         m_start = 0;
    std::size_t         m_end = 0;
};

} // namespace sf

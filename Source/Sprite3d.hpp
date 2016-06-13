//////////////////////////////////////////////////////////////////////////////
//
// Selba Ward (https://github.com/Hapaxia/SelbaWard)
// --
//
// Sprite3d
//
// Copyright(c) 2015-2016 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef SELBAWARD_SPRITE3D_HPP
#define SELBAWARD_SPRITE3D_HPP

#include "Common.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp> // to construct from sf::Sprite

namespace selbaward
{

// Sprite3d version 1.1.0
class Sprite3d : public sf::Drawable, public sf::Transformable
{
public:
	// constructors
	Sprite3d();
	Sprite3d(const sf::Texture& texture); // create from texture
	Sprite3d(const sf::Texture& texture, const sf::IntRect& textureRect); // create from texture and texture rectangle
	Sprite3d(const sf::Texture& texture, const sf::Texture& backTexture); // create from (front) texture and back texture
	Sprite3d(const sf::Texture& texture, const sf::IntRect& textureRect, const sf::Texture& backTexture, sf::Vector2i backTextureOffset = sf::Vector2i()); // create from (front) texture, texture rectangle, back texture, and back texture offset
	Sprite3d(const sf::Sprite& sprite); // create from standard sprite (copies texture, texture rectangle and all transformations)



	// get a standard sprite formed similarly to sprite3d
	const sf::Sprite getSprite() const;



	// standard sprite
	const sf::Texture* getTexture() const;
	sf::IntRect getTextureRect() const;
	sf::Color getColor() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void setTexture(const sf::Texture& texture, bool resetRect = false, bool resetBackOffset = false);
	void setTextureRect(const sf::IntRect& rectangle);
	void setColor(const sf::Color& color);



	// back face
	const sf::Texture* getBackTexture() const;
	bool getBackFlipEnabled() const;
	sf::Vector2i getTextureOffset() const;
	sf::Vector2i getBackTextureOffset() const;

	void setBackTexture(const sf::Texture& texture, bool resetOffset = false);
	void setBackFlipEnabled(bool flipBack = true);
	void setTextureOffset(sf::Vector2i textureOffset = sf::Vector2i());
	void setBackTextureOffset(sf::Vector2i backTextureOffset = sf::Vector2i());



	// 3D rotation
	float getPitch() const;
	float getYaw() const;
	float getRoll() const;
	sf::Vector3f getRotation3d() const;
	sf::Vector3f getOrigin3d() const;
	float getMostExtremeAngle() const; // most extreme angle of pitch and yaw. ranges from 0 to 90

	void setPitch(float pitch); // rotation around the x axis
	void setYaw(float yaw);     // rotation around the y axis
	void setRoll(float roll);   // rotation around the z axis (this is the usual 2D rotation)
	void setRotation(float rotation); // supplied as the 3d rotation method overrides the sf::Transformable rotation method
	void setRotation(sf::Vector3f rotation); // set pitch, yaw, and roll at once
	void setRotation3d(sf::Vector3f rotation); // set pitch, yaw, and roll at once
	void setOriginZ(float originZ); // sets the origin's z position, which is taken into account when rotating
	void setOrigin(sf::Vector2f origin); // supplied as the 3d origin method overrides the sf::Transformable origin method: sets the 2D origin position. also resets origin's z position to zero
	void setOrigin(sf::Vector3f origin); // sets the 3D origin position
	void setOrigin3d(sf::Vector3f origin); // sets the 3D origin position



	// mesh setup
	unsigned int getMeshDensity() const;
	unsigned int getSubdividedMeshDensity() const;
	unsigned int getSubdivision() const;
	bool getDynamicSubdivisionEnabled() const;

	void reserveMeshDensity(unsigned int meshDensity); // allow an expected maximum mesh density to be reserved in advance
	void setMeshDensity(unsigned int meshDensity);
	void setDynamicSubdivisionEnabled(bool enabled = true);
	void setDynamicSubdivisionRange(unsigned int maximum, unsigned int minimum = 0u);
	void setSubdivision(const unsigned int subdivision) const; // required to be const to allow dynamic subdivision
	void setNumberOfPoints(unsigned int numberOfPoints); // provided for convenience (sets number of points before any subdivision)
	void setNumberOfQuads(unsigned int numberOfPoints); // provided for convenience (sets number of apparent quads before any subdivision)
	void minimalMesh();



	// 3D setup
	// depth controls the amount of the apparent depth of the 3D effect.
	// higher values give a more extreme depth effect but more visible texture distortion
	// higher values give a more subtle depth effect but less visible texture distortion
	float getDepth() const;

	void setDepth(float depth);



private:
	const float m_depthToShallownessConversionNumerator;

	float m_pitch;
	float m_yaw;
	float m_depth; // even though m_shallowness is the one that actually gets used internally, this is stored as a form of cache to return through getDepth() to avoid the unnecessary division in a getter
	float m_shallowness;
	unsigned int m_meshDensity;
	bool m_flipBack; // flips the back's texture coordinates so that it shows the right way around

	// texture
	const sf::Texture* m_pTexture;
	const sf::Texture* m_pBackTexture;
	sf::Vector2i m_size;
	sf::Vector2i m_textureOffset;
	sf::Vector2i m_backTextureOffset;

	// for dynamic subdivision based on angle
	bool m_useDynamicSubdivision;
	unsigned int m_minSubdivision;
	unsigned int m_maxSubdivision;

	// need to be mutable to allow dynamic subdivision
	mutable unsigned int m_subdivision;
	mutable unsigned int m_subdividedMeshDensity; // stored as a cache to avoid unnecessary power calculations
	mutable std::vector<sf::Vector3f> m_points;

	// need to be mutable to allow modification through draw call
	mutable std::vector<sf::Vector2f> m_transformedPoints;
	mutable sf::Vector3f m_origin;
	mutable std::vector<sf::Vertex> m_vertices;
	mutable std::vector<float> m_compactTransformMatrix;
	mutable bool m_isBackFacing;

	// corners' global positions (mutable as they are automatically updated when the points are transformed)
	mutable sf::Vector2f m_topLeft;
	mutable sf::Vector2f m_topRight;
	mutable sf::Vector2f m_bottomLeft;
	mutable sf::Vector2f m_bottomRight;



	void createPointGrid() const; // needs to be const to allow dynamic subdivision

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateTransformedPoints() const;
	void updateVertices() const;
	void updateGlobalCorners() const;

	unsigned int getPointIndexForVertexIndex(unsigned int vertexIndex, bool invertPointX = false) const;
	unsigned int getNumberOfVerticesNeededForCurrentSubdividedMeshDensity() const;
	float linearInterpolation(float from, float to, float alpha) const;
	float mod(float numerator, float denominator) const;
	float min(float a, float b) const;
	float max(float a, float b) const;
	sf::Vector2i abs(const sf::Vector2i& vector) const;
};

} // namespace selbaward
#endif // SELBAWARD_SPRITE3D_HPP

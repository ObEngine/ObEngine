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



#include "Sprite3d.hpp"

namespace selbaward
{

Sprite3d::Sprite3d() :
m_depthToShallownessConversionNumerator(10000.f),
m_pitch(0.f),
m_yaw(0.f),
m_depth(10.f),
m_shallowness(m_depthToShallownessConversionNumerator / m_depth),
m_meshDensity(0u),
m_flipBack(false),
m_pTexture(nullptr),
m_pBackTexture(nullptr),
m_textureOffset(),
m_backTextureOffset(),
m_size(),
m_useDynamicSubdivision(false),
m_minSubdivision(1u),
m_maxSubdivision(4u),
m_subdivision(0u),
m_subdividedMeshDensity(0u),
m_points(4),
m_transformedPoints(4),
m_origin(),
m_vertices(4),
m_isBackFacing(false),
m_compactTransformMatrix(8, 0.f), // was 5. is now 8 to take into account z (for origin's z)
m_topLeft(),
m_topRight(),
m_bottomLeft(),
m_bottomRight()
{
}

Sprite3d::Sprite3d(const sf::Texture& texture) :
Sprite3d()
{
	setTexture(texture);
}

Sprite3d::Sprite3d(const sf::Texture& texture, const sf::IntRect& textureRect) :
Sprite3d()
{
	setTexture(texture);
	setTextureRect(textureRect);
}

Sprite3d::Sprite3d(const sf::Texture& texture, const sf::Texture& backTexture) :
Sprite3d()
{
	setTexture(texture);
	setBackTexture(backTexture);
}

Sprite3d::Sprite3d(const sf::Texture& texture, const sf::IntRect& textureRect, const sf::Texture& backTexture, sf::Vector2i backTextureOffset) :
Sprite3d()
{
	setTexture(texture);
	setTextureRect(textureRect);
	setBackTexture(backTexture);
	setBackTextureOffset(backTextureOffset);
}

Sprite3d::Sprite3d(const sf::Sprite& sprite) :
Sprite3d()
{
	setTexture(*sprite.getTexture());
	setTextureRect(sprite.getTextureRect());
	this->setColor(sprite.getColor());
	this->setOrigin(sprite.getOrigin());
	this->setPosition(sprite.getPosition());
	this->setRotation(sprite.getRotation());
	this->setScale(sprite.getScale());
}

const sf::Sprite Sprite3d::getSprite() const
{
	sf::IntRect textureRect(m_textureOffset, m_size);
	sf::Sprite sprite(*m_pTexture, textureRect);
	sprite.setColor(this->getColor());
	sprite.setOrigin(this->getOrigin());
	sprite.setPosition(this->getPosition());
	sprite.setRotation(this->getRotation());
	sprite.setScale(this->getScale());
	return sprite;
}

void Sprite3d::setTextureRect(const sf::IntRect& textureRectangle)
{
	m_textureOffset = sf::Vector2i(textureRectangle.left, textureRectangle.top);
	m_backTextureOffset = m_textureOffset;
	m_size = sf::Vector2i(textureRectangle.width, textureRectangle.height);
	createPointGrid();
	updateTransformedPoints();
	updateVertices();
	updateGlobalCorners();
}

void Sprite3d::setTexture(const sf::Texture& texture, const bool resetRect, const bool resetBackOffset)
{
	if (m_pTexture == nullptr || resetRect)
	{
		m_textureOffset = sf::Vector2i(0, 0);
		m_size = sf::Vector2i(texture.getSize());
		createPointGrid();
		m_vertices.resize(getNumberOfVerticesNeededForCurrentSubdividedMeshDensity());
	}
	if (resetBackOffset)
		m_backTextureOffset = sf::Vector2i(0, 0);
	m_pTexture = &texture;
}

void Sprite3d::setBackTexture(const sf::Texture& texture, const bool resetOffset)
{
	m_pBackTexture = &texture;
	if (m_pBackTexture == nullptr || resetOffset)
		m_backTextureOffset = sf::Vector2i(0, 0);
}

void Sprite3d::setBackFlipEnabled(const bool flipBack)
{
	m_flipBack = flipBack;
}

const sf::Texture* Sprite3d::getTexture() const
{
	return m_pTexture;
}

const sf::Texture* Sprite3d::getBackTexture() const
{
	return m_pBackTexture;
}

bool Sprite3d::getBackFlipEnabled() const
{
	return m_flipBack;
}

sf::Vector2i Sprite3d::getTextureOffset() const
{
	return m_textureOffset;
}

void Sprite3d::setTextureOffset(sf::Vector2i textureOffset)
{
	m_textureOffset = textureOffset;
}

sf::Vector2i Sprite3d::getBackTextureOffset() const
{
	return m_backTextureOffset;
}

void Sprite3d::setBackTextureOffset(sf::Vector2i backTextureOffset)
{
	m_backTextureOffset = backTextureOffset;
}

void Sprite3d::setColor(const sf::Color& color)
{
	for (auto& vertex : m_vertices)
		vertex.color = color;
}

sf::Color Sprite3d::getColor() const
{
	return m_vertices[0].color;
}

float Sprite3d::getPitch() const
{
	return m_pitch;
}

float Sprite3d::getYaw() const
{
	return m_yaw;
}

float Sprite3d::getRoll() const
{
	return this->getRotation();
}

sf::Vector3f Sprite3d::getRotation3d() const
{
	return{ m_pitch, m_yaw, this->Transformable::getRotation() };
}

sf::Vector3f Sprite3d::getOrigin3d() const
{
	const sf::Vector2f origin2d{ this->Transformable::getOrigin() };
	return{ origin2d.x, origin2d.y, m_origin.z };
}

void Sprite3d::setPitch(float pitch)
{
	m_pitch = pitch;
	while (m_pitch > 180.f)
		m_pitch -= 360.f;
	while (m_pitch < -180.f)
		m_pitch += 360.f;
}

void Sprite3d::setYaw(float yaw)
{
	m_yaw = yaw;
	while (m_yaw > 180.f)
		m_yaw -= 360.f;
	while (m_yaw < -180.f)
		m_yaw += 360.f;
}

void Sprite3d::setRoll(float roll)
{
	this->Transformable::setRotation(roll);
}

void Sprite3d::setRotation(float rotation)
{
	setRoll(rotation);
}

void Sprite3d::setRotation(sf::Vector3f rotation)
{
	setRotation3d(rotation);
}

void Sprite3d::setRotation3d(sf::Vector3f rotation)
{
	setPitch(rotation.x);
	setYaw(rotation.y);
	setRoll(rotation.z);
}

void Sprite3d::setOriginZ(float originZ)
{
	m_origin.z = originZ;
}

void Sprite3d::setOrigin(sf::Vector2f origin)
{
	this->Transformable::setOrigin(origin);
	m_origin.z = 0.f; // reset origin's z back to zero when setting a 2D origin
}

void Sprite3d::setOrigin(sf::Vector3f origin)
{
	setOrigin3d(origin);
}

void Sprite3d::setOrigin3d(sf::Vector3f origin)
{
	setOrigin(sf::Vector2f(origin.x, origin.y));
	setOriginZ(origin.z);
}

float Sprite3d::getMostExtremeAngle() const
{
	float pitch = std::abs(m_pitch);
	if (pitch > 90.f)
		pitch = 180.f - pitch;
	float yaw = std::abs(m_yaw);
	if (yaw > 90.f)
		yaw = 180.f - yaw;
	return std::max(pitch, yaw);
}

void Sprite3d::setMeshDensity(const unsigned int meshDensity)
{
	m_meshDensity = meshDensity;

	setSubdivision(m_subdivision);
}

unsigned int Sprite3d::getMeshDensity() const
{
	return m_meshDensity;
}

unsigned int Sprite3d::getSubdividedMeshDensity() const
{
	return m_subdividedMeshDensity;
}

void Sprite3d::reserveMeshDensity(const unsigned int meshDensity)
{
	const unsigned int numberOfPointsPerDimension = meshDensity + 2;
	m_points.reserve(numberOfPointsPerDimension * numberOfPointsPerDimension);
	m_transformedPoints.reserve(m_points.size());

	const unsigned int currentSubdividedMeshDensity = m_subdividedMeshDensity;
	m_subdividedMeshDensity = meshDensity;
	m_vertices.reserve(getNumberOfVerticesNeededForCurrentSubdividedMeshDensity());
	m_subdividedMeshDensity = currentSubdividedMeshDensity;
}

void Sprite3d::setDynamicSubdivisionEnabled(const bool enabled)
{
	m_useDynamicSubdivision = enabled;
}

void Sprite3d::setDynamicSubdivisionRange(unsigned int maximum, unsigned int minimum)
{
	if (maximum < minimum)
	{
		unsigned int temp;
		temp = maximum;
		maximum = minimum;
		minimum = temp;
	}
	m_maxSubdivision = maximum;
	m_minSubdivision = minimum;
	reserveMeshDensity(m_maxSubdivision);
}

bool Sprite3d::getDynamicSubdivisionEnabled() const
{
	return m_useDynamicSubdivision;
}

void Sprite3d::setSubdivision(const unsigned int subdivision) const
{
	m_subdivision = subdivision;

	m_subdividedMeshDensity = m_meshDensity;

	for (unsigned int i = 0; i < m_subdivision; ++i)
		m_subdividedMeshDensity = m_subdividedMeshDensity * 2 + 1;

	createPointGrid();
	m_vertices.resize(getNumberOfVerticesNeededForCurrentSubdividedMeshDensity());
}

unsigned int Sprite3d::getSubdivision() const
{
	return m_subdivision;
}

void Sprite3d::setNumberOfPoints(const unsigned int numberOfPoints)
{
	unsigned int root = static_cast<unsigned int>(sqrt(numberOfPoints));
	if (root > 2)
		setMeshDensity(root - 2);
	else
		setMeshDensity(0);
}

void Sprite3d::setNumberOfQuads(const unsigned int numberOfQuads)
{
	unsigned int root = static_cast<unsigned int>(sqrt(numberOfQuads));
	if (root > 1)
		setMeshDensity(root - 1);
	else
		setMeshDensity(0);
}

void Sprite3d::minimalMesh()
{
	m_meshDensity = 0;
	setSubdivision(0);
}

sf::FloatRect Sprite3d::getLocalBounds() const
{
	return sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(abs(m_size)));
}

sf::FloatRect Sprite3d::getGlobalBounds() const
{
	updateTransformedPoints();
	updateGlobalCorners();

	float minX = min(m_topLeft.x, min(m_topRight.x, min(m_bottomLeft.x, m_bottomRight.x)));
	float maxX = max(m_topLeft.x, max(m_topRight.x, max(m_bottomLeft.x, m_bottomRight.x)));
	float minY = min(m_topLeft.y, min(m_topRight.y, min(m_bottomLeft.y, m_bottomRight.y)));
	float maxY = max(m_topLeft.y, max(m_topRight.y, max(m_bottomLeft.y, m_bottomRight.y)));

	return sf::FloatRect(sf::Vector2f(minX, minY), sf::Vector2f(maxX - minX, maxY - minY));
}

void Sprite3d::setDepth(const float depth)
{
	m_depth = depth;
	m_shallowness = m_depthToShallownessConversionNumerator / ((m_depth > -0.000001f && m_depth < 0.000001f) ? 0.000001f : m_depth); // avoid division by zero here but don't change m_depth from being zero
}

float Sprite3d::getDepth() const
{
	return m_depth;
}

void Sprite3d::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_pTexture != nullptr)
	{
		updateTransformedPoints();
		updateVertices();
		states.transform *= getTransform();

		if (m_isBackFacing && m_pBackTexture != nullptr)
			states.texture = m_pBackTexture;
		else
			states.texture = m_pTexture;

		target.draw(&m_vertices[0], m_vertices.size(), sf::PrimitiveType::TrianglesStrip, states);
	}
}

void Sprite3d::updateTransformedPoints() const
{
	if (m_useDynamicSubdivision)
		setSubdivision(static_cast<unsigned int>((m_maxSubdivision - m_minSubdivision) * getMostExtremeAngle() / 90.f + m_minSubdivision));

	m_origin = { this->getOrigin().x, this->getOrigin().y, m_origin.z };
	const float radiansFromDegreesMultiplier = 0.0174532925f; // pi / 180;
	const float pitchInRadians = m_pitch * radiansFromDegreesMultiplier;
	const float yawInRadians = m_yaw * radiansFromDegreesMultiplier;

	const float cosPitch = cos(pitchInRadians);
	const float sinPitch = sin(pitchInRadians);
	const float cosYaw = cos(yawInRadians);
	const float sinYaw = sin(yawInRadians);

	/*******************************************************
	*          Pitch and Yaw combined matrix               *
	*                                                      *
	*  cosYaw,  sinPitch * sinYaw, -cosPitch * sinYaw, 0,  *
	*  0,       cosPitch,           sinPitch,          0,  *
	*  sinYaw, -sinPitch * cosYaw,  cosPitch * cosYaw, 0,  *
	*  0,       0,                  0,                 1   *
	*******************************************************/

	//m_compactTransformMatrix = { cosYaw, sinYaw, sinPitch * sinYaw, cosPitch, -sinPitch * cosYaw }; // only the five used elements
	m_compactTransformMatrix = { cosYaw, sinYaw, sinPitch * sinYaw, cosPitch, -sinPitch * cosYaw, -cosPitch * sinYaw, sinPitch, cosPitch * cosYaw }; // all eight used elements

	for (unsigned int v = 0; v < m_points.size(); ++v)
	{
		sf::Vector3f point = m_points[v];

		point -= m_origin;
		point =
		{
			/*
			m_compactTransformMatrix[0] * point.x + m_compactTransformMatrix[2] * point.y,
			                                        m_compactTransformMatrix[3] * point.y,
			m_compactTransformMatrix[1] * point.x + m_compactTransformMatrix[4] * point.y
			*/
			m_compactTransformMatrix[0] * point.x + m_compactTransformMatrix[2] * point.y + m_compactTransformMatrix[5] * point.z,
			                                        m_compactTransformMatrix[3] * point.y + m_compactTransformMatrix[6] * point.z,
			m_compactTransformMatrix[1] * point.x + m_compactTransformMatrix[4] * point.y + m_compactTransformMatrix[7] * point.z
		}; // apply rotations
		point *= m_shallowness / (m_shallowness + point.z); // apply depth
		point += m_origin;

		m_transformedPoints[v] = sf::Vector2f(point.x, point.y);
	}

	updateGlobalCorners();

	m_isBackFacing = false;
	if (m_pitch < -90.f || m_pitch > 90.f)
		m_isBackFacing = true;
	if (m_yaw < -90.f || m_yaw > 90.f)
		m_isBackFacing = !m_isBackFacing;
}

void Sprite3d::updateVertices() const
{
	sf::Vector2i currentTextureOffset = m_textureOffset;
	if (m_isBackFacing)
		currentTextureOffset = m_backTextureOffset;

	// create a mesh (triangle strip) from the points
	for (unsigned int v = 0; v < m_vertices.size(); ++v)
	{
		const unsigned int pointIndex = getPointIndexForVertexIndex(v);
		const unsigned int texturePointIndex = getPointIndexForVertexIndex(v, m_isBackFacing && m_flipBack);

		// update vertex
		m_vertices[v].position = m_transformedPoints[pointIndex];
		m_vertices[v].texCoords.x = (m_points[texturePointIndex].x * (m_size.x < 0 ? -1 : 1)) + currentTextureOffset.x;
		m_vertices[v].texCoords.y = (m_points[texturePointIndex].y * (m_size.y < 0 ? -1 : 1)) + currentTextureOffset.y;
	}
}

void Sprite3d::updateGlobalCorners() const
{
	m_topLeft = getTransform().transformPoint(m_transformedPoints.front());
	m_topRight = getTransform().transformPoint(*(m_transformedPoints.begin() + m_subdividedMeshDensity + 1));
	m_bottomLeft = getTransform().transformPoint(*(m_transformedPoints.end() - m_subdividedMeshDensity - 2)); // end() - (m_subdividedMeshDensity + 1) - 1
	m_bottomRight = getTransform().transformPoint(m_transformedPoints.back());

}

void Sprite3d::createPointGrid() const
{
	sf::Vector2f leftTop(0.f, 0.f);
	sf::Vector2f rightBottom(abs(m_size));

	const unsigned int numberOfPointsPerDimension = m_subdividedMeshDensity + 2;

	// create a grid of points
	m_points.resize(numberOfPointsPerDimension * numberOfPointsPerDimension);
	for (unsigned int y = 0; y < numberOfPointsPerDimension; ++y)
	{
		for (unsigned int x = 0; x < numberOfPointsPerDimension; ++x)
		{
			m_points[y * numberOfPointsPerDimension + x].x = linearInterpolation(leftTop.x, rightBottom.x, static_cast<float>(x) / (numberOfPointsPerDimension - 1));
			m_points[y * numberOfPointsPerDimension + x].y = linearInterpolation(leftTop.y, rightBottom.y, static_cast<float>(y) / (numberOfPointsPerDimension - 1));
			m_points[y * numberOfPointsPerDimension + x].z = 0.f;
		}
	}

	m_transformedPoints.resize(m_points.size());
}

unsigned int Sprite3d::getPointIndexForVertexIndex(const unsigned int vertexIndex, const bool invertPointX) const
{
	const unsigned int numberOfPointsPerDimension = m_subdividedMeshDensity + 2;
	const unsigned int numberOfVerticesPerRow = numberOfPointsPerDimension * 2 - 1;

	bool isOddRow = ((vertexIndex / numberOfVerticesPerRow) % 2) == 1;
	unsigned int pointX = (vertexIndex % numberOfVerticesPerRow) / 2;
	if (isOddRow)
		pointX = numberOfPointsPerDimension - pointX - 1;
	if (invertPointX)
		pointX = numberOfPointsPerDimension - pointX - 1;
	unsigned int pointY = (vertexIndex / numberOfVerticesPerRow) + ((vertexIndex % numberOfVerticesPerRow) % 2);

	return pointY * numberOfPointsPerDimension + pointX;
}

unsigned int Sprite3d::getNumberOfVerticesNeededForCurrentSubdividedMeshDensity() const
{
	//const unsigned int numberOfPointsPerDimension = m_meshDensity + 2;
	//const unsigned int numberOfVerticesPerRow = numberOfPointsPerDimension * 2 - 1;
	//return numberOfVerticesPerRow * (numberOfPointsPerDimension - 1) + 1;
	/*
	= v * (p - 1) + 1

	v = p * 2 - 1

	= (p * 2 - 1) * (p - 1) + 1

	= (2p - 1)(p - 1) + 1

	p = m + 2

	= (2(m + 2) - 1)(m + 2 - 1) + 1

	= (2m + 4 - 1)(m + 1) + 1

	= (2m + 3)(m + 1) + 1

	= (2m² + 3m + 2m + 3) + 1

	= 2m² + 5m + 4

	= m(2m + 5) + 4
	*/
	return (m_subdividedMeshDensity * 2 + 5) * m_subdividedMeshDensity + 4;
}

float Sprite3d::linearInterpolation(float from, float to, float alpha) const
{
	return from * (1.f - alpha) + to * alpha;
}

float Sprite3d::mod(float numerator, float denominator) const
{
	// avoid division by zero (if more accuracy is required, only offset the divided denominator, still use the actual denominator to multiply back as zero multiplication is fine)
	if (denominator > -0.000001f && denominator < 0.000001f)
		denominator = 0.000001f;

	return numerator - (trunc(numerator / denominator) * denominator);
}

float Sprite3d::min(float a, float b) const
{
	return (a < b) ? a : b;
}

float Sprite3d::max(float a, float b) const
{
	return (a > b) ? a : b;
}

sf::Vector2i Sprite3d::abs(const sf::Vector2i& vector) const
{
	return sf::Vector2i(std::abs(vector.x), std::abs(vector.y));
}

} // namespace selbaward

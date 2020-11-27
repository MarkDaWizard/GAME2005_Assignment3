#include "ship.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "CircleCollider.h"
#include <algorithm>

Ship::Ship() :m_maxSpeed(10.0f), m_currentDirection(glm::vec2(0.0f,-1.0f))
{
	TextureManager::Instance()->load("../Assets/textures/shipM.png","ship");

	auto size = TextureManager::Instance()->getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(585.0f, 510.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SHIP);
	setCollisionShape(RECTANGLE);
	
}


Ship::~Ship()
= default;

void Ship::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("ship", x, y, 0, 255, true);
}
float Ship::getMaxSpeed() const
{
	return m_maxSpeed;
}
void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}
glm::vec2 Ship::getCurrentDirection() const
{
	return m_currentDirection;
}
void Ship::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Ship::update()
{
	move();
	m_checkBounds();
}

void Ship::clean()
{
}







void Ship::move()
{
	const float deltaTime = 1.0f / 60.f;
	getTransform()->position += getRigidBody()->velocity* deltaTime* m_PPM;
	//getRigidBody()->velocity *= 0.9f;
}









void Ship::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

}

void Ship::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}




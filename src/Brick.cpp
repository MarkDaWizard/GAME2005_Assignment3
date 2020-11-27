#include "Brick.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "CircleCollider.h"
#include <algorithm>
#include "EventManager.h"

Brick::Brick() //:m_maxSpeed(5.0f), m_currentDirection(glm::vec2(0.0f, -1.0f))
{
	TextureManager::Instance()->load("../Assets/textures/brick.png", "brick");

	auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(585.0f, 510.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BRICK);
	setCollisionShape(RECTANGLE);

}


Brick::~Brick()
= default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}
float Brick::getMaxSpeed() const
{
	return m_maxSpeed;
}
void Brick::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}
glm::vec2 Brick::getCurrentDirection() const
{
	return m_currentDirection;
}
void Brick::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Brick::update()
{
	move();
	m_checkBounds();
}

void Brick::clean()
{
}







void Brick::move()
{
	if (isActive)
	{
		glm::vec2 mouseVector = EventManager::Instance().getMousePosition();
		getTransform()->position = glm::vec2(mouseVector.x, mouseVector.y);
	}
	/*const float deltaTime = 1.0f / 60.f;
	getTransform()->position += getRigidBody()->velocity * deltaTime * m_PPM;
	getRigidBody()->velocity *= 0.0f;*/
}









void Brick::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH - getWidth() * 0.5f)
	{
		getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - getWidth() * 0.5f, getTransform()->position.y);
	}

	if (getTransform()->position.x < getWidth() * 0.5f)
	{
		getTransform()->position = glm::vec2(getWidth() * 0.5f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT - getHeight() * 0.5f)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, Config::SCREEN_HEIGHT - getHeight() * 0.5f);
	}

	if (getTransform()->position.y < getHeight() * 0.5f)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, getHeight() * 0.5f);
	}

}

void Brick::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}




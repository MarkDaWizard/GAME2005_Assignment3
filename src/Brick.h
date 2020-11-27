#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "DisplayObject.h"
#include "TextureManager.h"

class Brick final : public DisplayObject
{
public:
	Brick();
	~Brick();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;



	void move();
	float getMaxSpeed() const;
	void setMaxSpeed(float newSpeed);
	const float SPEED = 100.0f;
	float m_PPM = 1.0f;
	bool isActive = false;
	glm::vec2 getCurrentDirection() const;
	void setCurrentDirection(glm::vec2 newDirection);
private:
	void m_checkBounds();
	void m_reset();
	glm::vec2 m_currentDirection;
	float m_maxSpeed;
};


#endif /* defined (__SHIP__) */


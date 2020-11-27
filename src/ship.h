#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "DisplayObject.h"
#include "TextureManager.h"

class Ship final : public DisplayObject
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	
	
	void move();
	float getMaxSpeed() const;
	void setMaxSpeed(float newSpeed);
	float SPEED = 100.0f;
	float m_PPM = 1.0f;
	glm::vec2 getCurrentDirection() const;
	void setCurrentDirection(glm::vec2 newDirection);
private:
	void m_checkBounds();
	void m_reset();
	glm::vec2 m_currentDirection;
	float m_maxSpeed;
};


#endif /* defined (__SHIP__) */


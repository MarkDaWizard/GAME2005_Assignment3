#pragma once
#ifndef __BALL__
#define __BALL__
#include "Sprite.h"


class Ball : public Sprite
{
public:
	Ball();
	~Ball();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;
	void m_checkBounds();
	void m_move();
	void reset();
	//void addForce(glm::vec2 Amount);
	//void move();

//	bool doesUpdate = false;
	bool active = false;
	//float m_gravity = 9.8f;
	float m_PPM = 1.0f;
	//float Mass;
	//float nextPosition;
//	bool showWire;

	//glm::vec2 Force;
	//void RandomPos();

};

#endif
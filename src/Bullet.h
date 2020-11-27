#pragma once
#ifndef __BULLET__
#define __BULLET__
#include "Sprite.h"


class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;
	void Reset();
	//void addForce(glm::vec2 Amount);
	//void move();

//	bool doesUpdate = false;
	bool active = false;
	float m_gravity=9.8f;
	float m_PPM =1.0f;
	//float Mass;
	//float nextPosition;
//	bool showWire;

	//glm::vec2 Force;
	//void RandomPos();

};

#endif
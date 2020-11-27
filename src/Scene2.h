#pragma once
#ifndef __SCENE_2__
#define __SCENE_2__
#include "Scene.h"
#include "Label.h"
#include "ship.h"
//#include "MoveState.h"
//#include "Planet.h"
//#include "Mine.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "ball.h"

class Scene2 final : public Scene
{
public:
	Scene2();
	~Scene2();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	/*Label* m_pStartLabel;
	Label* m_pInstructionsLabel;*/

	// Ship Stuff
	Ship* m_pShip;
//	MoveState m_moveState;
	glm::vec2 m_speedFactor;

	
	// Bullet Stuff
	Ball* m_pBall;

	std::vector<Ball*> m_pBalls;

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;

	// Physics Variables
	float m_gravity = 9.8f;
	int m_PPM = 10; // pixels per meter
	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_acceleration = glm::vec2(0.0f, 0.0f);

	// Physics functions
	void m_move();
};

#endif /* defined (__START_SCENE__) */
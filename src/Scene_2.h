#pragma once
#ifndef __SCENE_2__
#define __SCENE_2__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "ball.h"
#include "Brick.h"

class Scene_2 final : public Scene
{
public:
	Scene_2();
	~Scene_2();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void reset();

private:
	
	// Ship Stuff
	Brick* m_pBrick;
//	MoveState m_moveState;
	glm::vec2 m_speedFactor;
	
	
	// Bullet Stuff
	Ball* m_pBall;
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;



	// Labels stuffs
	Label* m_pInstructionsLabel;


	
	//std::vector<Ball*> m_pBalls;

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	
	void StartSimulation();
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

};

#endif /* defined (__END_SCENE__) */
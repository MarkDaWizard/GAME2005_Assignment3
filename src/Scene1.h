#pragma once
#ifndef __SCENE1__
#define __SCENE1__

#include "Scene.h"
#include "Plane.h"
#include "ship.h"
#include "Button.h"
#include "Label.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "SoundManager.h"

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void changeLabel();
	
	void StartSimulation();
	void reset();
	
private:

	float bulletSpawnTimerDuration = 500.0f;//in milliseconds
	float bulletSpawnTimerinSec = 0.5f;
	float bulletSpawnTimerStart;
	// IMGUI Function
	void GUI_Function() ;
	void SpawnBullet();
	
	
	glm::vec2 m_mousePosition;

	BulletPool* m_pPool;
	
	Ship* m_pPlayer;
	bool running = false;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	

	Label* m_pInstructionsLabel;
	Label* m_pNumberOfBullet;
	Label* m_pVelocity;
	Label* m_pSpawnDuration;


	float m_PPM = 1.0f; // pixels per meter - scale


	int m_noOfBullet = 10;


};

#endif /* defined (__PLAY_SCENE__) */
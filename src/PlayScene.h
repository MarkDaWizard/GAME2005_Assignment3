#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
//#include "Target.h"
#include "ship.h"
//#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "SoundManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

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

	Label* m_pNoOfBullet;
	
	Label* m_pVel;
	Label* m_pSpawnTimer;


	float m_PPM = 1.0f; // pixels per meter - scale


	int m_noOfBullet = 10;


};

#endif /* defined (__PLAY_SCENE__) */
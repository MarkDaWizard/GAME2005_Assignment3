#pragma once
#ifndef __PLAY_SCENE2__
#define __PLAY_SCENE2__

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

class PlayScene2 : public Scene
{
public:
	PlayScene2();
	~PlayScene2();

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
	const float bulletSpawnTimerDuration = 500.0f;
	float bulletSpawnTimerStart;
	// IMGUI Function
	void GUI_Function() ;
	void SpawnBullet();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;
	
	//Plane* m_pPlaneSprite;
	BulletPool* m_pPool;
	
	Ship* m_pPlayer;
	//Bullet* bullet;
	//Ship* m_pStormtrooper;
	//bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	
	
	
	
	Label* m_pInstructionsLabel;
	//mass, position, velocity, acceleration
	//Label* m_pMass;
	Label* m_pNoOfBullet;
	
	Label* m_pVel;
	Label* m_pAcce;

	Label* m_pForce;

	
	//int fl = 510.0f;


	// Physics Variables
	

	float m_PPM = 1.0f; // pixels per meter - scale
	


	int m_noOfBullet = 10;
	float m_Force = 0.0f;
	
	
	


	

	






//	float m_totalTime=0.0f;
};

#endif /* defined (__PLAY_SCENE__) */
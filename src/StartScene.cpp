#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"


#include "Renderer.h"


StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void StartScene::start()
{
	//Sets the color for the background, values of RGB and alpha
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 100, 100, 255, 255);
	
	
	
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pTeamLabel1 = new Label("Phu Pham - 101250748", "Consolas", 30, red, glm::vec2(400.0f, 150.0f));
	m_pTeamLabel1->setParent(this);
	addChild(m_pTeamLabel1);

	m_pTeamLabel1 = new Label("Justin Dela Cruz - 101127646", "Consolas", 30, red, glm::vec2(400.0f, 100.0f));
	m_pTeamLabel1->setParent(this);
	addChild(m_pTeamLabel1);

	m_pInstructionsLabel = new Label("Press 1 for Bullet Rain and 2 for Bouncing Ball", "Consolas", 30, blue, glm::vec2(400.0f, 200.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	
	// Scene1 Button
	m_pScene1Button = new Button("../Assets/textures/scene1.png","scene1Button",START_BUTTON, glm::vec2(150.0f, 300.0f),false);

	m_pScene1Button->addEventListener(CLICK, [&]()-> void
	{
		m_pScene1Button->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pScene1Button->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pScene1Button->setAlpha(200);
	});

	m_pScene1Button->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pScene1Button->setAlpha(255);
	});
	addChild(m_pScene1Button);


	// Scene2 Button

	m_pScene2Button = new Button("../Assets/textures/scene2.png", "scene2Button", START_BUTTON, glm::vec2(500.0f, 300.0f), false);

	m_pScene2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2Button->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_pScene2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2Button->setAlpha(200);
		});

	m_pScene2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2Button->setAlpha(255);
		});
	addChild(m_pScene2Button);

	
}


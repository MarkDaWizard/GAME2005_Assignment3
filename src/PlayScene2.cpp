#include "PlayScene2.h"
#include "Game.h"
#include "EventManager.h"
#include <iostream>
#include <vector>
// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
//#include "BulletPool.h"
#include "Util.h"
//#include <string>

PlayScene2::PlayScene2()
{
	PlayScene2::start();
	
}

PlayScene2::~PlayScene2()
= default;

void PlayScene2::draw()
{
	TextureManager::Instance()->draw("bg", Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2, 0, 255, true);
	//bullet->draw();
	
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
		Util::DrawRect(m_pPlayer->getTransform()->position - glm::vec2(m_pPlayer->getWidth() * 0.5f, m_pPlayer->getHeight() * 0.5f), m_pPlayer->getWidth(), m_pPlayer->getHeight());
		//Util::DrawCapsule(m_pPlayer->getTransform()->position, m_pPlayer->getWidth(), m_pPlayer->getHeight());
		
	}
	

}

void PlayScene2::update()
{
	updateDisplayList();
	//Util::DrawIntersectRect(bullet->getTransform()->position, bullet->getWidth(), bullet->getHeight(), m_pPlayer->getTransform()->position, m_pPlayer->getWidth(), m_pPlayer->getHeight());
	//CollisionManager::AABBCheck(bullet, m_pPlayer);
	if (m_pPool != NULL)
	{
		
		if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration) {
			SpawnBullet();
		}
		//std::vector<bool>::iterator myBoolIter = m_pPool->activeColliding.begin();
		int i = 0;
		for (std::vector<Bullet*>::iterator myiter = m_pPool->active.begin(); myiter != m_pPool->active.end(); myiter++)
		//for (int i = 0; i < m_pPool->active.size(); i++)
		
		{
			Bullet* currentbullet = *myiter;
			const float p1Width = currentbullet->getWidth();
			const float p1Height = currentbullet->getHeight();
			const float p2Width = m_pPlayer->getWidth();
			const float p2Height = m_pPlayer->getHeight();
			//move the position from center to top left corner
			const auto p1 = currentbullet->getTransform()->position - glm::vec2(p1Width * 0.5f, p1Height * 0.5f);
			const auto p2 = m_pPlayer->getTransform()->position - glm::vec2(p2Width * 0.5f, p2Height * 0.5f);
			if (
				p1.x < p2.x + p2Width &&
				p1.x + p1Width > p2.x &&
				p1.y < p2.y + p2Height &&
				p1.y + p1Height > p2.y
				)
			{
				//collistion detected
				if (!m_pPool->activeColliding[i])
				{
					m_pPool->activeColliding[i] = true;
					SoundManager::Instance().playSound("yay", 0);
				}
			}
			else
				m_pPool->activeColliding[i] = false;
			
			//bool collision=CollisionManager::AABBCheck1(currentbullet, m_pPlayer, m_pPool->activeColliding,i);
			//m_pPool->activeColliding[i] = collision;
			
			if (currentbullet->getTransform()->position.y >= 650)
			{
				m_pPool->Despawn(currentbullet);
				break;
			}
			i++;
		}
	}
}

void PlayScene2::clean()
{
	removeAllChildren();
}

void PlayScene2::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			/*if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}*/
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		/*if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}*/
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->getRigidBody()->velocity = glm::vec2(-m_pPlayer->SPEED, 0.0f);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->getRigidBody()->velocity = glm::vec2(m_pPlayer->SPEED, 0.0f);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, -m_pPlayer->SPEED);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, m_pPlayer->SPEED);
	}
	else {
		m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}
void PlayScene2::reset() {
	
	//m_pStormtrooper->getTransform()->position = glm::vec2(585.0f, fl);
	//m_pLoot->m_gravity = 9.8f;
	//m_pPool = NULL;
	m_PPM = 1.0f;
	/*if(m_pPool!=NULL)
		m_pPool->ResetAll();*/
	//m_pLoot->m_mass = 12.5f;
	//m_pLoot->m_PPM = 1.0f;
	//m_pLoot->m_Atime = 0.016667f;
	//m_pLoot->m_angle = 0.0f;
	//m_pLoot->m_velocity = 0.0f;
	//m_pLoot->m_velocityX = 0.0f;
	//m_pLoot->m_velocityY = 0.0f;
	//m_pLoot->m_acceleration = glm::vec2(0.0f, 0.0f);
	//m_pLoot->throwSpeed = glm::vec2(0.0f, 0.0f);
	//m_pLoot->buttonPressed = false;
	//m_pLoot->isGravityEnabled = false;
	
}
void PlayScene2::start()
{
	//load background from texture.
	TextureManager::Instance()->load("../Assets/textures/bg.png", "bg");
	SoundManager::Instance().load("../Assets/audio/death.wav", "yay", SOUND_SFX);
	// Set GUI Title
	m_guiTitle = "Play Scene 1";
	//// Ball Sprite
	//bullet = new Bullet();
	//bullet->getTransform()->position = glm::vec2(300, 300);
	//addChild(bullet);
	
	m_pPlayer = new Ship();
	addChild(m_pPlayer);
	
	
	// Back Button
	m_pBackButton = new Button("../Assets/textures/back.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(60.0f, 560.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/next.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(740.0f, 560.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);
	const SDL_Color white = { 255, 255, 255, 255 };
	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Menu", "Consolas",15,white);
	
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 570.0f);

	addChild(m_pInstructionsLabel);
	
	m_pNoOfBullet = new Label("No of bullet: 10", "Consolas", 20, white);
	m_pNoOfBullet->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 10.0f);
	addChild(m_pNoOfBullet);
	
	m_pVel = new Label("Velocity: 95m/s", "Consolas", 20, white);
	m_pVel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 30.0f);
	addChild(m_pVel);
	
	
	
	m_pForce = new Label("Force: 50N", "Consolas", 20, white);
	m_pForce->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.85f,110.0f);
	addChild(m_pForce);
	
	m_pAcce = new Label("Acceleration: 3m/s^2", "Consolas", 20, white);
	m_pAcce->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 150.0f);
	addChild(m_pAcce);
	reset();

}
void PlayScene2::StartSimulation() {
	m_pPlayer->m_PPM = m_PPM;
	m_pPool = new BulletPool(m_noOfBullet);
	//add each one to scene
	for (std::vector<Bullet*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); myiter++)
	{
		Bullet* bullet = *myiter;

		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}
void PlayScene2::changeLabel() {
	std::string text;// = "Velocity: " + std::to_string(m_pLoot->m_velocity) + " m/s";
	//m_pVel->setText(text);
	text = "No of Bullet: " + std::to_string(m_noOfBullet) ;//Mass: 12.8Kg
	m_pNoOfBullet->setText(text);
	;
	//text = "distance: " + std::to_string(m_pStormtrooper->getTransform()->position.x- m_pBall->getTransform()->position.x) + " m";//Angle: 45degree

	//text = "Force: " + std::to_string(m_pLoot->m_pF) + " N";
	//m_pForce->setText(text);

	//std::cout << "labl" <<  m_pLoot->m_accelerationVal << std::endl;
	//text = "Acceleration: " + std::to_string(m_pLoot->m_accelerationVal);//Angle: 45degree
	//m_pAcce->setText(text);
}


void PlayScene2::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Physics Simulation Control", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	
	ImGui::Separator();
	bool buttonPressed = ImGui::Button("Start Simulation");
	if (buttonPressed)
	{
		StartSimulation();
		//m_pLoot->doThrow();
	}
	/*ImGui::SameLine();
	if (ImGui::Button("Reset All"))
	{
		reset();
	}*/
	ImGui::Separator();
	if (ImGui::SliderFloat("Pixels Per Meter", &m_PPM, 0.1f, 30.0f, "%.1f"));
	
	if (ImGui::SliderInt("No of Bullet", &m_noOfBullet, 0, 100));
	
	changeLabel();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
void PlayScene2::SpawnBullet() {
	Bullet* bullet = m_pPool->Spawn();
	
	if (bullet)
	{
		bullet->m_PPM = m_PPM;
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
		
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}
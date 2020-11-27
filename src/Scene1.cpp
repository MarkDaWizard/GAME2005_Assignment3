#include "Scene1.h"
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

Scene1::Scene1()
{
	Scene1::start();
}

Scene1::~Scene1()
= default;

void Scene1::draw()
{
	TextureManager::Instance()->draw("bg", Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2, 0, 255, true);
	//bullet->draw();
	
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
		Util::DrawRect(m_pPlayer->getTransform()->position - glm::vec2(m_pPlayer->getWidth() * 0.5f, m_pPlayer->getHeight() * 0.5f), m_pPlayer->getWidth(), m_pPlayer->getHeight());
	}

}

void Scene1::update()
{
	updateDisplayList();
	
	//Object pool update
	if (m_pPool != NULL)
	{
		if (running)
		{
			if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration) {
				if(m_pPool->active.size()>m_noOfBullet)
				{
					Bullet* bullet = (m_pPool->active.back());	
					m_pPool->active.pop_back();
					bullet->active = false;
					bullet->getTransform()->position.y = -bullet->getHeight();
					m_pPool->inactive.push_back(bullet);
					
				}
				else if (m_pPool->active.size() < m_noOfBullet)
					SpawnBullet();
			}
			//std::vector<bool>::iterator myBoolIter = m_pPool->activeColliding.begin();
			int i = 0;
			for (std::vector<Bullet*>::iterator myiter = m_pPool->active.begin(); myiter != m_pPool->active.end(); myiter++)

			{
				Bullet* currentbullet = *myiter;
				const float p1Width = currentbullet->getWidth();
				const float p1Height = currentbullet->getHeight();
				const float p2Width = m_pPlayer->getWidth();
				const float p2Height = m_pPlayer->getHeight();
				//Move the position from center to top left corner
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

				if (currentbullet->getTransform()->position.y >= 650)
				{
					m_pPool->Despawn(currentbullet);
					break;
				}
				i++;
			}
		}
		
	}
}

void Scene1::clean()
{
	removeAllChildren();
}

void Scene1::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		
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
	
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, -m_pPlayer->SPEED);
	}
	
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) 
	{
		m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, m_pPlayer->SPEED);
	}
	else 
	{
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
void Scene1::reset() {
	
	//Reset label parameters to default
	m_PPM = 1.0f;
	running = false;
	m_pPlayer->SPEED = 100.0f;

	//Player's position
	m_pPlayer->getTransform()->position = glm::vec2(400.0f, 400.0f);
	m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	m_pPlayer->getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	//Bullet stuffs
	bulletSpawnTimerinSec = 0.5f;
	bulletSpawnTimerDuration = bulletSpawnTimerinSec * 1000;
	m_noOfBullet = 10;
	m_pPool->ResetAll();
	
}
void Scene1::start()
{
	//Load Texture
	TextureManager::Instance()->load("../Assets/textures/bg.png", "bg");
	SoundManager::Instance().load("../Assets/audio/death.wav", "yay", SOUND_SFX);
	
	
	m_pPlayer = new Ship();
	addChild(m_pPlayer);
	
	m_pPlayer->m_PPM = m_PPM;
	m_pPool = new BulletPool(m_noOfBullet);
	
	//add each one to scene
	for (std::vector<Bullet*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); myiter++)
	{
		Bullet* bullet = *myiter;

		addChild(bullet);
	}
	

	// Next Button
	m_pNextButton = new Button("../Assets/textures/next.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(700.0f, 560.0f);
	
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
		
	});

	//Event when mousing over button
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

	// Display number of bullets
	m_pNumberOfBullet = new Label("Bullets: 10", "Consolas", 20, white);
	m_pNumberOfBullet->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 10.0f);
	addChild(m_pNumberOfBullet);

	// Display bullet speed
	m_pVelocity = new Label("Speed: 100m/s", "Consolas", 20, white);
	m_pVelocity->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 30.0f);
	addChild(m_pVelocity);
	
	// Display spawn duration
	m_pSpawnDuration = new Label("Duration: 0.5 s", "Consolas", 20, white);
	m_pSpawnDuration->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 50.0f);
	addChild(m_pSpawnDuration);
	reset();

}
void Scene1::StartSimulation() {
	running = true;
	bulletSpawnTimerStart = SDL_GetTicks();
}
void Scene1::changeLabel()
{
	std::string text = "Speed: " + std::to_string(m_pPlayer->SPEED) + " m/s";
	m_pVelocity->setText(text);
	text = "Bullets: " + std::to_string(m_noOfBullet) ;
	m_pNumberOfBullet->setText(text);
	
	text = "Duration: " + std::to_string(bulletSpawnTimerinSec)+" s";
	m_pSpawnDuration->setText(text);
}


void Scene1::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	
	ImGui::Begin("Physics Simulation Control", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	// Buttons functionality
	ImGui::Separator();
	bool buttonPressed = ImGui::Button("Start Simulation");
	if (buttonPressed)
	{
		StartSimulation();
		//m_pLoot->doThrow();
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset All"))
	{
		reset();
	}

	ImGui::Separator();
	if (ImGui::SliderFloat("Spawn Timer Duration", &bulletSpawnTimerinSec, 0.001f, 10.0f, "%.1f"))
		bulletSpawnTimerDuration = bulletSpawnTimerinSec * 1000;
	if (ImGui::SliderInt("Number of bullets", &m_noOfBullet, 0, 100));
	if (ImGui::SliderFloat("Bullet speed (Pixels/Second)", &m_PPM, 0.1f, 50.0f, "%.1f"));
	changeLabel();
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}


//Spawning bullets
void Scene1::SpawnBullet() {
	Bullet* bullet = m_pPool->Spawn();
	
	if (bullet)
	{
		bullet->m_PPM = m_PPM;
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
		
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}
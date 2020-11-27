#include "Scene_2.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "Renderer.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Util.h"

Scene_2::Scene_2()
{
	Scene_2::start();
}

Scene_2::~Scene_2()
= default;

void Scene_2::draw()
{
	TextureManager::Instance()->draw("bg", Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, 0, 255, true);


	if (m_pBall != NULL)
		m_pBall->draw();

	
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	// ImGui Rendering section - DO NOT MOVE OR DELETE
	if (EventManager::Instance().isIMGUIActive())
	{
		m_updateUI();
		
		if (m_pBall != NULL)
		{
			Util::DrawRect(m_pBall->getTransform()->position - glm::vec2(m_pBall->getWidth() * 0.5f, m_pBall->getHeight() * 0.5f), m_pBall->getWidth(), m_pBall->getHeight());
			Util::DrawLine(m_pBall->getTransform()->position, m_pBrick->getTransform()->position);
		}

		if (m_pBrick != NULL)
			Util::DrawRect(m_pBrick->getTransform()->position - glm::vec2(m_pBrick->getWidth() * 0.5f, m_pBrick->getHeight() * 0.5f), m_pBrick->getWidth(), m_pBrick->getHeight());
		
	}
}

void Scene_2::update()
{
	updateDisplayList();
	//m_move();
	m_pBrick->update();
	
	if (m_pBall != NULL)
		m_pBall->update();
	if (m_pBrick->isActive)
	{
		CollisionManager::circleAABBCheck(m_pBall, m_pBrick);
	}
}

void Scene_2::clean()
{
	
	removeAllChildren();
}

void Scene_2::handleEvents()
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
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	
}

void Scene_2::start()
{
	TextureManager::Instance()->load("../Assets/textures/bg.png", "bg");
	
	SoundManager::Instance().load(
		"../Assets/audio/yay.ogg",
		"yay", SOUND_SFX);
	SoundManager::Instance().load(
		"../Assets/audio/thunder.ogg",
		"thunder", SOUND_SFX);

	m_position = glm::vec2(400.0f, 500.0f);
	m_pBrick = new Brick();
	m_pBrick->getTransform()->position = m_position;
	addChild(m_pBrick);

	m_velocity = glm::vec2(0.0, 0.0); //glm::vec2(1.0f, m_velocity.y);
	m_speedFactor = glm::vec2(4.0f, 4.0f);



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
		m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Menu", "Consolas", 15, white);

		m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 570.0f);

		addChild(m_pInstructionsLabel);
}

void Scene_2::reset()
{
	m_pBall = NULL;
}


void Scene_2::StartSimulation() {
	m_pBall = new Ball();
	m_pBall->reset();
	m_pBrick->isActive = true;
}


void Scene_2::m_updateUI()
{
	// Prepare Window Frame
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow(); // use for debug purposes

	std::string windowString = "BOUNCING BALL";

	ImGui::Begin(&windowString[0], NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

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

	// Main Window End
	ImGui::End();
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

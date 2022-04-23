#include "Game.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Enemy.h"
#include "input.h" 
#include "Timer.h"
#include "mapParser.h"
#include "Camera.h"
#include "ObjectFactory.h"
#include "soundGame.h"


Game* Game::s_Instance = nullptr;

static bool aliveVas = 1, aliveStep = 1, alivePal = 1;

void Game::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	int flags = (fullscreen)?SDL_WINDOW_FULLSCREEN:0;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
	{
		 SDL_Log("Init has failed: %s", SDL_GetError());
		m_bRunning = false;
		return;
	}
    
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, w, h, flags);

	if (m_pWindow == nullptr)
	{
		SDL_Log("Init window has failed: %s", SDL_GetError());
		m_bRunning = false;
		return;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_pRenderer == nullptr)
	{
		SDL_Log("Init renderer from window has failed: %s", SDL_GetError());
		m_bRunning = false;
		return;
	}

    if (!mapParser::GetInstance()->load("../Assets/maps/Tiled/TEST/map.tmx"))
	{
		std::cout << "Failed to load map" << '\n';
	}
	TextureManager::GetInstance()->ParseTextures("../Assets/texture.tml");
    TextureManager::GetInstance()->ParseSounds("../Assets/sounds.tml");

    m_LevelMap = mapParser::GetInstance()->GetMaps("MAP");

	Properties* props = new Properties("player", 50, 460, 112, 113);

    player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);
    firstEnemy = new Enemy(new Properties("firstBoss", 2050, 510, 78, 78, SDL_FLIP_HORIZONTAL));

	m_GameObjects.push_back(firstEnemy);
    m_GameObjects.push_back(player);

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    mainmenu = new menu("mainmenu", SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);
    mainmenu->init();
	m_bRunning = true;
}

void Game::handleEvents()
{
	input::GetInstance()->Listen();
}

void Game::renderer()
{
	SDL_RenderClear(m_pRenderer);
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);

    TextureManager::GetInstance()->Draw("background", 0, 0, 8160, 1024, 1, 1, 1.0f);
	m_LevelMap->Render();
	for (int i = 0; i != m_GameObjects.size(); ++i)
	{
		m_GameObjects[i]->Draw();
	}

    SDL_RenderPresent(m_pRenderer);
}

void Game::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();
    // setting menu
    while (mainmenu->getActive() == true) {
        mainmenu->update(m_pRenderer);
        mainmenu->draw(m_pRenderer);
        Timer::GetInstance()->Tick();
    }
    if (mainmenu->getExit() == true || mainmenu->getCredits() == true || mainmenu->getStart() == true) {
        if (mainmenu->getExit() == true) {
            m_bRunning = false;
            mainmenu->deleteButton();
        }

        else if (mainmenu->getStart() == true)
        {
            userButEscape = false;
            mainmenu->setDefault();
            mainmenu->deleteButton();
        }
        return;
    }

    if (aliveVas){
        if (firstEnemy->GetHealth()<=0){
            aliveVas = 0;
            m_GameObjects[0]->Clean();
            m_GameObjects.erase(m_GameObjects.begin());
        }
    }

	m_LevelMap->Update();

	for (int i = 0; i != m_GameObjects.size(); ++i) {
        m_GameObjects[i]->Update(dt);
    }

    Camera::GetInstance()->Update(dt);
}

void Game::clean()
{
	for (int i = 0; i != m_GameObjects.size(); ++i) {
        m_GameObjects[i]->Clean();
    }
	TextureManager::GetInstance()->clean();

    mainmenu->clean();

    SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	IMG_Quit();
	SDL_Quit();
}

bool Game::exitMenu()
{
    if (userButEscape){
        userButEscape = false;
        if (mainmenu == nullptr) {
            mainmenu = new menu("mainmenu", SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH);
        }
        mainmenu->init();

        return true;
    }

    return false;
}
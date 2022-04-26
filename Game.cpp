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
#include "SDL2/SDL_ttf.h"
#include "FontsManager.h"


Game* Game::s_Instance = nullptr;

void Game::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	int flags = (fullscreen)?SDL_WINDOW_FULLSCREEN:0;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0 && TTF_Init() != 0)
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
//    Properties* props = new Properties("player", 7031, 371, 112, 113); Тестовая строка, для телепортации к последнему боссу
    player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);
    firstEnemy = new Enemy(new Properties("firstBoss", 2050, 510, 78, 78, SDL_FLIP_HORIZONTAL));
    secondEnemy = new secondBoss(new Properties("secondBoss", 4267, 328, 100, 74, SDL_FLIP_HORIZONTAL));
    thirdEnemy = new ThirdBoss(new Properties("thirdBoss", 7500, 480, 80, 80, SDL_FLIP_HORIZONTAL));

    m_GameObjects["thirdEnemy"] = thirdEnemy;
    m_GameObjects["secondEnemy"] = secondEnemy;
    m_GameObjects["firstEnemy"] = firstEnemy;
    m_GameObjects["player"] = player;

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    FontsManager::GetInstance()->Add("../Assets/fonts/MachinaOrto.ttf", "TimerText", 48);

    progressMission = new ProgressBar("progress");

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

    m_GameObjects["player"]->Draw();

    if (aliveVas == 1) {
        m_GameObjects["firstEnemy"]->Draw();
    }

    if (aliveStep == 1) {
        m_GameObjects["secondEnemy"]->Draw();
    }

    if (alivePal == 1) {
        m_GameObjects["thirdEnemy"]->Draw();
    }

    Timer::GetInstance()->Draw("TimerText");
    progressMission->Draw();

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

    // Check alive first boss
    if (aliveVas) {
        if (firstEnemy->GetHealth()<=0){
            aliveVas = 0;
            m_GameObjects.erase("firstEnemy");
            soundGame::GetInstance()->playEffect("lastPhraseVasukov");
            soundGame::GetInstance()->playMusic("startMenu");
        }
    }

    if (aliveStep) {
        if (secondEnemy->GetHealth()<=0){
            aliveStep = 0;
            m_GameObjects.erase("secondEnemy");

            soundGame::GetInstance()->playEffect("lastPhraseStepanov");
            soundGame::GetInstance()->playMusic("startMenu");
        }
    }

    if (alivePal) {
        if (thirdEnemy->GetHealth() <= 0) {
            alivePal = 0;
            m_GameObjects.erase("thirdEnemy");

            soundGame::GetInstance()->playEffect("lastPhraseUnk");
            soundGame::GetInstance()->playMusic("startMenu");
        }
    }

    if (player->GetHealth()<=0)
    {
        m_GameObjects.clear();
        delete firstEnemy;
        delete secondEnemy;
        delete thirdEnemy;

        firstEnemy = new Enemy(new Properties("firstBoss", 2050, 510, 78, 78, SDL_FLIP_HORIZONTAL));
        secondEnemy = new secondBoss(new Properties("secondBoss", 4267, 328, 100, 74, SDL_FLIP_HORIZONTAL));
        thirdEnemy = new ThirdBoss(new Properties("thirdBoss", 7500, 480, 80, 80, SDL_FLIP_HORIZONTAL));

        m_GameObjects["thirdEnemy"] = thirdEnemy;
        m_GameObjects["secondEnemy"] = secondEnemy;
        m_GameObjects["firstEnemy"] = firstEnemy;
        m_GameObjects["player"] = player;

        aliveStep = aliveVas = alivePal = true;

        Timer::GetInstance()->Start();

    }


	m_LevelMap->Update();

    m_GameObjects["player"]->Update(dt);

    if (aliveVas == 1) {
        m_GameObjects["firstEnemy"]->Update(dt);
    }

    if (aliveStep == 1) {
        m_GameObjects["secondEnemy"]->Update(dt);
    }

    if (alivePal == 1) {
        m_GameObjects["thirdEnemy"]->Update(dt);
    }

    Camera::GetInstance()->Update(dt);

    progressMission->Update(dt);
}

void Game::clean()
{
    m_GameObjects["player"]->Clean();

    if (aliveVas) {
        m_GameObjects["firstEnemy"]->Clean();
    }

    if (aliveStep) {
        m_GameObjects["secondEnemy"]->Clean();
    }

    if (alivePal) {
        m_GameObjects["thirdEnemy"]->Clean();
    }

    progressMission->Clean();

    TextureManager::GetInstance()->clean();

    mainmenu->clean();

    soundGame::GetInstance()->clean();

    SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

    TTF_Quit();
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
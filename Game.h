#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map>

#include "Map.h"
#include "GameObject.h"
#include "menu.h"
#include "Enemy.h"
#include "secondBoss.h"
#include "thirdBoss.h"
#include "Timer.h"
#include "ProgressBar.h"


#define MAP_WIDTH 8160//10384
#define MAP_HEIGHT 1024//640
#define SCREEN_WIDTH 960//1280
#define SCREEN_HEIGHT 640//480
#define VIEW_WIDTH 480
#define VIEW_HEIGHT 320
class Game
{
public:
	static Game* GetInstance()
	{
		return s_Instance = (s_Instance != nullptr)? s_Instance : new Game();
	}

	void init(const char*, int xpos, int ypos, int w, int h, bool fullscreen);
	void Update();
	void renderer();
	void clean();
	void handleEvents();

    bool exitMenu();

    inline void set_mbRunning(bool running) { m_bRunning = running; }
	inline bool running() { return m_bRunning; }
	inline SDL_Renderer* GetRenderer() { return m_pRenderer; }
	inline Map* GetMap() { return m_LevelMap; }
    // return boss

    inline GameObject* getPlayer() {return player;}
    // check the end game
    inline bool getFinish() {return (aliveVas==false && alivePal == false && aliveStep == false)?true:false;}
    // chang channel sound
    inline int& GetChannel() {return numberChannel;}
public:
    inline Enemy* getFirstBoss() {return firstEnemy;}
    inline secondBoss* getSecondBoss() {return secondEnemy;}
    inline ThirdBoss* getThirdBoss() {return thirdEnemy;}

    inline bool getAliveVas() {return aliveVas;}
    inline bool getAliveStep() {return aliveStep;}
    inline bool getAliveUnk() {return alivePal;}

private:
	Game() {};
	bool m_bRunning = 1;
    bool aliveVas = true, aliveStep = true, alivePal = true;

    int numberChannel = 0;
	Map* m_LevelMap;
    std::map<std::string, GameObject*> m_GameObjects;

    SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

    static Game* s_Instance;

    menu* mainmenu;

    Enemy* firstEnemy;
    secondBoss* secondEnemy;
    ThirdBoss* thirdEnemy;
    GameObject* player;
    ProgressBar* progressMission;
};
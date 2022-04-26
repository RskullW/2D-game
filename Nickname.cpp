#include "Nickname.h"
#include "Game.h"
#include "FontsManager.h"
#include "input.h"

Nickname::Nickname(std::string id) {
    m_textureID = id;
    m_nickname = "";
    dt = 0;
    m_LengthNick = 6;
    m_pFont = FontsManager::GetInstance()->GetFont(id);

    m_textureBackground = TextureManager::GetInstance()->getTexture("entername");
    m_srcBackground.x = m_srcBackground.y = 0;
    m_srcBackground.w = SCREEN_WIDTH;
    m_srcBackground.h = SCREEN_HEIGHT;

    m_isActivated = true;
}

bool Nickname::HandleEvents() {
    input::GetInstance()->GetKey();
    dt++;

    for (int i = (int) SDL_SCANCODE_A; i <= (int) SDL_SCANCODE_Z; ++i) {
        if (input::GetInstance()->GetKeyDown((SDL_Scancode) i) && m_nickname.size() <= m_LengthNick && dt>=15) {
            m_nickname += (SDL_GetKeyFromScancode((SDL_Scancode) i));
            dt = 0;
            soundGame::GetInstance()->playEffect("write", -1);
        }
    }

    if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_BACKSPACE) && m_nickname.size() && dt>=15) {
        m_nickname.pop_back();
        dt = 0;
        soundGame::GetInstance()->playEffect("write", -1);
    }

    if (input::GetInstance()->GetKeyDown(SDL_SCANCODE_RETURN) && m_nickname.size()) {
        Game::GetInstance()->SetNick(m_nickname);
        m_isActivated = false;
        soundGame::GetInstance()->playEffect("enter", -1);
        SDL_Delay(1000);
        return 1;
    }

    return 0;
}

void Nickname::Update() {
    HandleEvents();
}

void Nickname::Render() {
    SDL_Color color = {255, 255, 255, 255};

    if (m_nickname.size()!=0) {
        SDL_Rect src;

        src.x = SCREEN_WIDTH / 3;
        src.y = SCREEN_HEIGHT / 2;


        m_pSurface = TTF_RenderText_Solid(m_pFont, m_nickname.c_str(), color);

        if (m_pSurface == nullptr) {
            SDL_Log("Error! Font do not exist, surface not loaded...");
        }

        m_pTextureID = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), m_pSurface);

        if (m_pTextureID == nullptr) {
            SDL_Log("Error! Font do not exist, texture not loaded...");
        }

        SDL_FreeSurface(m_pSurface);

        SDL_QueryTexture(m_pTextureID, NULL, NULL, &src.w, &src.h);
        src.w*=2.5;
        src.h*=2.5;
        SDL_RenderCopy(Game::GetInstance()->GetRenderer(), m_pTextureID, NULL, &src);
    }
}
#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "TextureManager.h"
#include "SpriteAnim.h"
#include "Collider.h"
#include "Vector2D.h"


class Bullet {
public:
    Bullet(std::string id, int x, int y, int w, int h);

    void Add(int startX, int startY, int endX, int endY);

    bool CheckPosition(Vector2D coordNPC);
    void Draw();
    void Clean();
    void Update(float dt);

    bool GetAddBullet() {return m_AddBullet;}

private:
    struct Coordinate_Bullets{
        int startX;
        int startY;
        int endX;
        int endY;
    };
private:
    bool m_AddBullet;

    std::string m_pTextureID;
    SpriteAnim* m_AnimationBullet;
    // Size bullet
    SDL_Rect m_Size;
    // Coordinates of the bullet direction
    Coordinate_Bullets m_coordinate;
};
#include "pedestal.h"

#include "raylib.h"

Pedestal::Pedestal()
    : x(0)
    , y(75)
    , width(75)
    , height(25) {}

void Pedestal::Draw() const {
    //idk what to name it besides gronly
    const Color gronly = {0, 0, 20, 100};
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    DrawRectangle(screenWidth/2.0f + x, screenHeight/2.0f + y, width, height, gronly);
}
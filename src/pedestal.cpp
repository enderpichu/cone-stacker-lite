#include "pedestal.h"

#include "raylib.h"

Pedestal::Pedestal()
    : x(-30)
    , y(15)
    , width(75)
    , height(25)
    , pedestalPos({0.0f,0.0f})
    {}

void Pedestal::Draw(int screenWidth) const {
    //idk what to name it besides gronly
    const Color gronly = {0, 0, 20, 100};
    const int screenHeight = GetScreenHeight();
    pedestalPos = {screenWidth/2.0f - width/2.0f, screenHeight/2.0f - y};
    Rectangle pedestal = {pedestalPos.x,pedestalPos.y, static_cast<float>(width), static_cast<float>(height)};

    DrawRectangleRec(pedestal, gronly);
}

int Pedestal::GetPedestalPosY() const {
    return (pedestalPos.y - static_cast<int>(height))-5;
}
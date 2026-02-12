#include "cone.h"

#include "raylib.h"

Cone::Cone()
    : x(390)
    , y(100)
    , speedX(4)
    , speedY(0)
    , height(32)
    , width(32)
    {}

  

void Cone::Update() {
    //setting speedX to change X
    x += speedX;
    y += speedY;
    //getting screen width and making it easier to type
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    //cone bounces from sides of the screen
    if ((x + width >= screenWidth - 250) || (x <= 250)) {
        speedX *= -1;
    }
}
void Cone::Draw() const {
    DrawRectangle(x, y, width, height, WHITE);
}

int Cone::GetConeX() const {
    return x;
}

int Cone::GetConeY() const {
    return y;
}
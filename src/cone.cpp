#include "cone.h"
#include "coneNumberSetup.h"

#include "raylib.h"

Cone::Cone()
    : x(390)
    , y(100)
    , speedX(4)
    , speedY(0)
    , height(32)
    , width(32)
    , resetApplied(false)
    {}

  

void Cone::Update(ConeNumberSetup& coneSetup) {
    //setting speedX to change X
    x += speedX;
    //getting screen width and making it easier to type
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    //cone bounces from sides of the screen
    if (coneSetup.coneNumbers / 7 > coneSetup.lastCone) {
        speedX += (speedX >= 0 ? 1 : -1);
        coneSetup.lastCone = coneSetup.coneNumbers / 7;
    }

    if (coneSetup.coneNumbers / 20 > coneSetup.coneLevelUpSpeed) {
        speedX *= 2;
        coneSetup.coneLevelUpSpeed = coneSetup.coneNumbers / 20;
    }

    if (coneSetup.coneNumbers < 1) {
        if (!resetApplied) {
            speedX = 4;
            coneSetup.lastCone = 0;
            resetApplied = true;
        }
    } else {
        resetApplied = false;
    }

    if ((x + width >= screenWidth - 225) || (x <= 225)) {
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
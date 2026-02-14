#include "powerUpLocator.h"
#include "coneNumberSetup.h"

#include "raylib.h"

bool claimInput() {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool isClaimable(ConeNumberSetup& conesetup) {
    if (conesetup.coneNumbers > 14) {
        return true;
    }
    return false;
}

PowerUpLocation::PowerUpLocation()
: randomizer(GetRandomValue(0,50))
, showPowerUp(GetRandomValue(0,3) == 0 ? 1 : 0)
, x(randomizer)
, y(30)
, speedY(0)
, height(32)
, width(32)
, isClaimed(false)
{}

void PowerUpLocation::Update() {
    y += speedY;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int mouseX = GetMouseX();
    const int mouseY = GetMouseY();

    if (isClaimable && !isClaimed) {
        if (showPowerUp == 1) {
            if ((y + height >= screenHeight) || (y <= 0)) {
            speedY *= -1;
            }
            if (claimInput && mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
                isClaimed = true;
            }
        }
    }
}


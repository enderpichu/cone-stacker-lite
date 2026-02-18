#include "powerUpLocator.h"
#include "coneNumberSetup.h"

#include "raylib.h"

bool claimInput() {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

PowerUpLocation::PowerUpLocation()
: randomizer(0)
, showPowerUp(0)
, powerUpPicker(0)
, x(0)
, y(30)
, speedY(10)
, radius(16)
, isClaimed(false)
, killedPowerUp(false)
, yReset(false)
, updateTimer(0)
, lifetimeTimer(0)
, speedTimeout(0)
{}

bool isClaimable(ConeNumberSetup& conesetup, PowerUpLocation& powerUp) {
    if (conesetup.coneNumbers > 14 && powerUp.showPowerUp == 1) {
        return true;
    }
    return false;
}

void PowerUpLocation::Update(ConeNumberSetup& conesetup) {
    if (conesetup.coneNumbers > 14) {
        updateTimer++;
        if (updateTimer >= 300) { // chance of powerup every ~5 sec
            randomizer = GetRandomValue(16, 66);
            showPowerUp = GetRandomValue(0, 3) == 0 ? 1 : 0;
            x = randomizer;
            killedPowerUp = false;
            updateTimer = 0;
            if (showPowerUp == 1) {
                lifetimeTimer = 0;
                isClaimed = false;
                powerUpPicker = GetRandomValue(1, 3); // selects power up type randomly between three options
            }
        }
    }

    if (conesetup.coneNumbers > 14 && showPowerUp == 1 && !killedPowerUp) {
        lifetimeTimer++;
        if (lifetimeTimer >= 120) { // powerup clears after 2 sec
            showPowerUp = 0;
            killedPowerUp = true;
            lifetimeTimer = 0;
        }
    }
    
    y += speedY;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int mouseX = GetMouseX();
    const int mouseY = GetMouseY();

    if (isClaimable(conesetup, *this) && !isClaimed) {
        speedTimeout++;
        if (showPowerUp == 1) {
            if (!yReset) {
                y = 30;
                yReset = true;
            }
        if (speedTimeout > 15) {
            speedY += (speedY >= 0 ? 10 : -10); //speed it up every 1/4 second
            speedTimeout = 0;
        }
            if ((y + radius >= screenHeight) || (y - radius <= 0)) {
            speedY *= -1;
            }
            if (claimInput() && mouseX >= x - radius && mouseX <= x + radius && mouseY >= y - radius && mouseY <= y + radius) {
                isClaimed = true;
                showPowerUp = 0;
                killedPowerUp = true;
            }
        }
        else if (showPowerUp != 1) {
            yReset = false;
        }
    }
}

void PowerUpLocation::Draw() const {
    if (showPowerUp != 1) {
        return;
    }
    const Color Power1 = {0,0,0,255};
    const Color Power2 = {0,0,0,255};
    const Color Power3 = {0,0,0,255};
    if (powerUpPicker == 1) {
        DrawCircle(x, y, radius, Power1);
    }
    else if (powerUpPicker == 2) {
        DrawCircle(x, y, radius, Power2);
    }
    else if (powerUpPicker == 3) {
        DrawCircle(x, y, radius, Power3);
    }
}
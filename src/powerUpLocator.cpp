#include "powerUpLocator.h"
#include "coneNumberSetup.h"
#include <iostream>

#include "raylib.h"

bool claimInput() {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

PowerUpLocation::PowerUpLocation()
: randomizer(0)
, showPowerUp(0)
, powerUpPicker(0)
, x(50)
, y(30)
, speedY(10)
, heightAndWidth(64)
, isClaimed(false)
, killedPowerUp(false)
, yReset(false)
, updateTimer(0)
, lifetimeTimer(0)
, lifetime(250)
, speedTimeout(0)
, powerUpTester(3)
, minConesForPowerUp(3)
{}

bool isClaimable(const ConeNumberSetup& conesetup, const PowerUpLocation& powerUp) {
    if (conesetup.conesAmount > powerUp.minConesForPowerUp && powerUp.showPowerUp == 1) {
        return true;
    }
    return false;
}

void PowerUpLocation::Draw(Texture2D& texture1, Texture2D& texture2, Texture2D& texture3, bool stateOne, bool stateTwo) const{
    if (!stateOne && !stateTwo && showPowerUp == 1 && !isClaimed) {
        if (powerUpPicker != 0) {
            switch (powerUpPicker) {
                case 1:
                    DrawTexture(texture1, x - texture1.width /2, y - texture1.height /2, WHITE);
                    DrawRectangleLines(x - texture1.width /2, y - texture1.height / 2, texture1.width, texture1.height, RED);
                break;
                case 2:
                    DrawTexture(texture2, x - texture2.width /2, y - texture2.height /2, WHITE);
                    DrawRectangleLines(x - texture2.width /2, y - texture2.height / 2, texture2.width, texture2.height, RED);
                break;
                case 3:
                    DrawTexture(texture3, x - texture3.width /2, y - texture3.height /2, WHITE);
                    DrawRectangleLines(x - texture3.width /2, y - texture3.height / 2, texture3.width, texture3.height, RED);
                break;
            }
            DrawText(TextFormat("%02.02f", (lifetimeTimer / 60.0f)), x - texture1.width / 2, y - texture1.height, 20, RED);
        }
    }
}

bool PowerUpLocation::IsMouseInBounds(const ConeNumberSetup& conesetup) const {
    if (!isClaimable(conesetup, *this) || isClaimed) {
        return false;
    }

    const int mouseX = GetMouseX();
    const int mouseY = GetMouseY();
    return mouseX >= x - heightAndWidth/2 && mouseX <= x + heightAndWidth/2 && mouseY >= y - heightAndWidth/2 && mouseY <= y + heightAndWidth/2;
}
//TODO: change behaviors- make golden cone easier to get and very low chance (~5%), time slowing harder and a lower chance (~35%), and team colorize the most common. keep durations
void PowerUpLocation::Update(ConeNumberSetup& conesetup) {
    if (conesetup.conesAmount <= minConesForPowerUp) {
        showPowerUp = 0;
        powerUpPicker = 0;
        isClaimed = false;
        killedPowerUp = false;
        lifetimeTimer = lifetime;
        updateTimer = 0;
    }
    else if (showPowerUp == 1 && !isClaimed && !killedPowerUp) {
        lifetimeTimer--;
        if (lifetimeTimer <= 0) { // powerup clears after lifetime expires
            showPowerUp = 0;
            powerUpPicker = 0;
            killedPowerUp = true;
            lifetimeTimer = lifetime;
        }
    }
    else {
        updateTimer++;
        if (updateTimer >= 60) { // chance of powerup every ~1 sec
            updateTimer = 0;
            if (GetRandomValue(0, 3) == 0) {
                randomizer = GetRandomValue(32, 120);
                x = randomizer;
                showPowerUp = 1;
                killedPowerUp = false;
                isClaimed = false;
                lifetimeTimer = lifetime;
                powerUpPicker = GetRandomValue(1, 3); // selects power up type randomly between three options
            }
            else {
                showPowerUp = 0;
                powerUpPicker = 0;
                killedPowerUp = false;
            }
        }
    }

    const int screenHeight = GetScreenHeight();
    const int mouseX = GetMouseX();
    const int mouseY = GetMouseY();

    if (isClaimable(conesetup, *this) && !isClaimed) {
        speedTimeout++;
        if (!yReset) {
            y = 30;
            speedY = 2;
            yReset = true;
            speedTimeout = 0;
        }

        if (speedTimeout > 15) {
            //old logic speedY += (speedY >= 0 ? 2 : -2); //speed it up every 1/4 second
            speedY *= 1.25;
            speedTimeout = 0;
        }

        y += speedY;
        if (y - heightAndWidth/2 <= 0) {
            y = heightAndWidth/2;
            if (speedY < 0) speedY = -speedY;
        }
        else if (y + heightAndWidth/2 >= screenHeight) {
            y = screenHeight - heightAndWidth/2;
            if (speedY > 0) speedY = -speedY;
        }

        if (claimInput() && mouseX >= x - heightAndWidth/2 && mouseX <= x + heightAndWidth/2 && mouseY >= y - heightAndWidth/2 && mouseY <= y + heightAndWidth/2) {
            isClaimed = true;
            showPowerUp = 0;
            killedPowerUp = true;
        }
    }
    else {
        yReset = false;
        speedTimeout = 0;
    }
}

void PowerUpLocation::PickPowerUp() const {
    if (powerUpPicker == 1) {
        return;
    }
    else if (powerUpPicker == 2) {
        return;
    }
    else if (powerUpPicker == 3) {
        return;
    }
}

int PowerUpLocation::EatPowerUp() {
    if (isClaimed) {
        const int claimedPowerUp = powerUpPicker;
        isClaimed = false;
        powerUpPicker = 0;
        return claimedPowerUp;
    }
    return 0;
}

int PowerUpLocation::TestPowerUp() {
    if (isClaimed) {
        isClaimed = false;
        return powerUpTester;
    }
    return 0;
}

int PowerUpLocation::GetPowerUpX() const {
    return x;
}

int PowerUpLocation::GetPowerUpY() const {
    return y;
}
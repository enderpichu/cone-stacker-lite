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
, speedTimeout(0)
, powerUpTester(3)
, minConesForPowerUp(3)
{}

bool isClaimable(const ConeNumberSetup& conesetup, const PowerUpLocation& powerUp) {
    if (conesetup.coneNumbers > powerUp.minConesForPowerUp && powerUp.showPowerUp == 1) {
        return true;
    }
    return false;
}

void PowerUpLocation::Draw(Texture2D& texture1, Texture2D& texture2, Texture2D& texture3, bool stateOne, bool stateTwo) const{
    if (!stateOne && !stateTwo && showPowerUp == 1 && !isClaimed) {
        if (powerUpPicker != 0) {
            switch (powerUpPicker) {
                case 1:
                    DrawTexture(texture1, x - texture1.width/2, y - texture1.height/2, WHITE);
                break;
                case 2:
                    DrawTexture(texture2, x - texture2.width/2, y - texture2.height/2, WHITE);
                break;
                case 3:
                    DrawTexture(texture3, x - texture3.width/2, y - texture3.height/2, WHITE);
                break;
            }
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

void PowerUpLocation::Update(ConeNumberSetup& conesetup) {
    if (conesetup.coneNumbers > minConesForPowerUp) {
        updateTimer++;
        if (updateTimer >= 60) { // chance of powerup every ~1 sec
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
            else {
                powerUpPicker = 0;
            }
        }
    }
    else {
        showPowerUp = 0;
        powerUpPicker = 0;
        killedPowerUp = false;
        lifetimeTimer = 0;
        updateTimer = 0;
    }
    // std::cout << showPowerUp << std::endl;
    // if (showPowerUp == 1) {
    // std::cout << powerUpPicker << std::endl;
    // }

    if (conesetup.coneNumbers > 14 && showPowerUp == 1 && !killedPowerUp) {
        lifetimeTimer++;
        if (lifetimeTimer >= 150) { // powerup clears after 2.5 sec
            showPowerUp = 0;
            powerUpPicker = 0;
            killedPowerUp = true;
            lifetimeTimer = 0;
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
            speedY += (speedY >= 0 ? 2 : -2); //speed it up every 1/4 second
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
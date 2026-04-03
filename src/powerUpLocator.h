#pragma once

#include "raylib.h"
#include "raymath.h"

class ConeNumberSetup;

class PowerUpLocation {
    public:
        PowerUpLocation();
        void Update(ConeNumberSetup& conesetup);
        void Draw(Texture2D& texture1, Texture2D& texture2, Texture2D& texture3, bool stateOne, bool stateTwo) const;
        bool IsMouseInBounds(const ConeNumberSetup& conesetup) const;
        void PickPowerUp() const;
        int GetPowerUpY() const;
        int GetPowerUpX() const;
        int showPowerUp;
        int powerUpPicker;
        int powerUpTester;
        bool isClaimed;
        int EatPowerUp();
        int TestPowerUp();
        int minConesForPowerUp;



    private:
        int randomizer;
        int x;
        int y;
        int speedY;
        int heightAndWidth;
        bool killedPowerUp;
        bool yReset;
        int updateTimer;
        int lifetimeTimer;
        int lifetime;
        int speedTimeout;
};
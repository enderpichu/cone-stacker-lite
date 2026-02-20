#pragma once

#include "raylib.h"
#include "raymath.h"

class ConeNumberSetup;

class PowerUpLocation {
    public:
        PowerUpLocation();
        void Update(ConeNumberSetup& conesetup);
        void PickPowerUp() const;
        int GetPowerUpY() const;
        int GetPowerUpX() const;
        int showPowerUp;
        int powerUpPicker;
        bool isClaimed;
        int EatPowerUp();


    private:
        int randomizer;
        int x;
        int y;
        int speedY;
        int radius;
        bool killedPowerUp;
        bool yReset;
        int updateTimer;
        int lifetimeTimer;
        int speedTimeout;

};
#pragma once

#include "raylib.h"
#include "raymath.h"

class ConeNumberSetup;

class PowerUpLocation {
    public:
        PowerUpLocation();
        void Update(ConeNumberSetup& conesetup);
        void Draw() const;
        int GetPowerUpY() const;
        int showPowerUp;
        int powerUpPicker;


    private:
        int randomizer;
        int x;
        int y;
        int speedY;
        int radius;
        bool isClaimed;
        bool killedPowerUp;
        bool yReset;
        int updateTimer;
        int lifetimeTimer;
        int speedTimeout;

};
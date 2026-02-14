#pragma once

#include "raylib.h"
#include "raymath.h"

class PowerUpLocation {
    public:
        PowerUpLocation();
        void Update();
        void Draw() const;
        int GetPowerUpY() const;

    private:
        int showPowerUp;
        int randomizer;
        int x;
        int y;
        int speedY;
        int height;
        int width;
        bool isClaimed;

};
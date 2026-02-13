#pragma once

#include "raylib.h"
#include "coneNumberSetup.h"

class Cone {
    public:
        Cone();
        void Update(ConeNumberSetup& coneSetup);
        void Draw() const;
        int GetConeX() const;
        int GetConeY() const;

    private:
        int x;
        int y;
        int speedX;
        int speedY;
        int height;
        int width;
        bool resetApplied;
};
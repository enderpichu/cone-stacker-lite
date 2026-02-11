#pragma once

#include "raylib.h"

class Cone {
    public:
        Cone();
        void Update();
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
};
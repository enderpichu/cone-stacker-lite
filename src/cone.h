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
        void slowDownPUp();
        void TeamColorizePUp();
        bool slowApplied;
        bool IsPeak;


    private:
        int x;
        int y;
        int speedX;
        int speedY;
        int height;
        int width;
        float slowDownTimer;
        float teamColorizeTimer;
        float speedMultiplier;
        bool resetApplied;
};
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
        double GetSlowTimer() const;
        double GetTeamTimer() const;
        bool slowApplied;
        bool IsPeak;


    private:
        int x;
        int y;
        int maxX;
        int minX;
        int speedX;
        int speedY;
        int height;
        int width;
        double slowDownTimer;
        double teamColorizeTimer;
        double speedMultiplier;
        bool resetApplied;
};
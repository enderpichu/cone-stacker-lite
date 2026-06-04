#include "cone.h"
#include "coneNumberSetup.h"

#include "raylib.h"
#include "raymath.h"

Cone::Cone()
    : x(390)
    , y(100)
    , maxX(500)
    , minX(220)
    , speedX(4)
    , speedY(0)
    , height(32)
    , width(32)
    , slowDownTimer(0.0)
    , teamColorizeTimer(0.0)
    , speedMultiplier(1.0)
    , resetApplied(false)
    , slowApplied(false)
    , IsPeak(false)
    {}

  

void Cone::Update(ConeNumberSetup& coneSetup) {
    //setting speedX to change X
    x += static_cast<int>(speedX * speedMultiplier);

    Clamp(x, minX, maxX);
    //getting screen width and making it easier to type
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    //cone bounces from sides of the screen
    if (coneSetup.conesAmount / 7 > coneSetup.previousCone) {
        speedX += (speedX >= 0 ? 1 * 1 : -1);
        coneSetup.previousCone = coneSetup.conesAmount / 7;
    }

    if (coneSetup.conesAmount / 20 > coneSetup.coneLevelUpSpeed) {
        speedX += (speedX >= 0 ? 2 : -2);
        coneSetup.coneLevelUpSpeed = coneSetup.conesAmount / 20;
    }

    if (coneSetup.conesAmount < 1) {
        if (!resetApplied) {
            speedX = 4;
            coneSetup.previousCone = 0;
            resetApplied = true;
        }
    } else {
        resetApplied = false;
    }

    if ((x + width >= screenWidth - (minX + 5)) || (x <= (minX + 5))) {
        speedX *= -1;
    }

}
void Cone::Draw() const {
    DrawRectangle(x, y, width, height, WHITE);
}

void Cone::slowDownPUp() {
    if (!slowApplied) {
        slowDownTimer = 5.0;
        speedMultiplier = 0.5;
        slowApplied = true;
    }

    slowDownTimer -= GetFrameTime();
    if (slowDownTimer <= 0.0) {
        speedMultiplier = 1.0;
        slowApplied = false;
    }
}

void Cone::TeamColorizePUp() {
    if (!IsPeak) {
        teamColorizeTimer = 10.0;
        IsPeak = true;
    }

    teamColorizeTimer -= GetFrameTime();
    if (teamColorizeTimer <= 0.0) {
        IsPeak = false;
    }
}

int Cone::GetConeX() const {
    return x;
}

int Cone::GetConeY() const {
    return y;
}

double Cone::GetSlowTimer() const {
    if (slowApplied) {
        return slowDownTimer;
    }
    else {
        return 0.0;
    }
}

double Cone::GetTeamTimer() const {
    if (IsPeak) {
        return teamColorizeTimer;
    }
    else {
        return 0.0;
    }
}
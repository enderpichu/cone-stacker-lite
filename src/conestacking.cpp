#include "coneNumberSetup.h"
#include "cone.h"
#include "pedestal.h"

#include "raylib.h"
#include "raymath.h"

int ConeNumberSetup::prevClear = 0;

extern ConeStack conestack[MAX_CONES];

ConeNumberSetup::ConeNumberSetup() 
: conesAmount(0)
, previousCone(0)
, coneLevelUpSpeed(0)
{}

void ConeNumberSetup::Update(Cone& cone, Pedestal& pedestal, int screenWidth, Sound& stackSfx, Sound& firstSfx, Sound& loseSfx, Texture2D& coneTex, int& highScore, bool& gameOver, bool& mainMenu, bool& newHi, bool blockMouseStack) {
    const bool keyPressed = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W);
    const bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !blockMouseStack;
    if ((keyPressed || mousePressed) && !gameOver && !mainMenu) {
        if (cone.GetConeX() > (screenWidth/2 - coneTex.width - 10) && cone.GetConeX() < (screenWidth/2 + coneTex.width + 10)) {
        for (int i = 0; i < 1; i++) {
            if (conesAmount < MAX_CONES) {
            conestack[conesAmount].position.y = pedestal.GetPedestalPosY() - ((conesAmount % 20) * 8);
                    conesAmount ++;
                    if (conesAmount % 20 == 1) {
                        PlaySound(firstSfx);
                    }
                    else {
                        PlaySound(stackSfx);
                    }
                    if (conesAmount > highScore) {
                        highScore = conesAmount;
                        newHi = true;
                    }
                }
            }
        }
        else {
            PlaySound(loseSfx);
            conesAmount = 0;
            prevClear = 0;
            gameOver = true;
        }
    }
}
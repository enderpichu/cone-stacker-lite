#include "coneNumberSetup.h"
#include "cone.h"
#include "pedestal.h"

#include "raylib.h"
#include "raymath.h"

int ConeNumberSetup::prevClear = 0;

extern ConeStack conestack[MAX_CONES];

ConeNumberSetup::ConeNumberSetup() 
: coneNumbers(0)
, lastCone(0)
, coneLevelUpSpeed(0)
{}

void ConeNumberSetup::Update(Cone& cone, Pedestal& pedestal, int screenWidth, Sound& stackSfx, Sound& firstSfx, Sound& loseSfx, Texture2D& coneTex, int& highScore, bool& gameOver, bool& mainMenu, bool& newHi) {
     if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !gameOver && !mainMenu) {
        if (cone.GetConeX() > (screenWidth/2 - coneTex.width - 10) && cone.GetConeX() < (screenWidth/2 + coneTex.width + 10)) {
        for (int i = 0; i < 1; i++) {
            if (coneNumbers < MAX_CONES) {
            conestack[coneNumbers].position.y = pedestal.GetPedestalPosY() - ((coneNumbers % 20) * 8);
                    coneNumbers ++;
                    if (coneNumbers % 20 == 1) {
                        PlaySound(firstSfx);
                    }
                    else {
                        PlaySound(stackSfx);
                    }
                    if (coneNumbers > highScore) {
                        highScore = coneNumbers;
                        newHi = true;
                    }
                }
            }
        }
        else {
            PlaySound(loseSfx);
            coneNumbers = 0;
            prevClear = 0;
            gameOver = true;
        }
    }
}
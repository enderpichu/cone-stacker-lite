#pragma once

#include "raylib.h"

#define MAX_CONES 1500

class Cone;
class Pedestal;

struct ConeStack {
    Vector2 position;
};

class ConeNumberSetup {
        public:
            ConeNumberSetup();
            int lastCone;
            int coneNumbers;
            int coneLevelUpSpeed;
            static int prevClear;
            void Update(Cone& cone, Pedestal& pedestal, int screenWidth, Sound& stackSfx, Sound& firstSfx, Sound& loseSfx, Texture2D& coneTex, int& highScore, bool& gameOver, bool& mainMenu, bool& newHi, bool blockMouseStack);
            void DrawStack(Texture2D& coneTex, int screenWidth);
            void Reset();
};
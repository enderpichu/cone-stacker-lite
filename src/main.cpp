#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../libs/raygui/src/raygui.h"

#include "main.hpp"
#include <string>
#include <filesystem>

#include "cone.h"
#include "pedestal.h"
#include "coneNumberSetup.h"

#include "stdlib.h"

#define MAX_CONES 1500

ConeNumberSetup::ConeNumberSetup() 
: coneNumbers(0)
, lastCone(0)
, coneLevelUpSpeed(0)
{}

static int prevClear = 0;
// Window setup
int screenWidth = 720;
const int screenHeight = 480;
bool windowShouldClose = false;


// Loading resources
std::string assetPathPrefix = "../assets/";

//sum setup

//returns true when you lose
bool gameOver = false;

//returns true when game startsup
bool mainMenu = true;

Texture2D coneTexture;
Texture2D coneGameOver;
Texture2D coneMainMenu;

ConeNumberSetup conesetup;
Cone cone;
Pedestal pedestal;
typedef struct ConeStack {
    Vector2 position;
} ConeStack;

void NewConeInStack(Texture2D texture, int posX, int posY, Color color) {
    
}

// Draw text centered horizontally. Included because I use it all the time.
void DrawTextCentered(const char* text, int posX, int posY, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, posX-(textWidth/2), posY, fontSize, color);
}

void init_app() {
    if (std::filesystem::exists("../assets") == false) {
        assetPathPrefix = "assets/";
    }
    
    // Load textures here
    // nateTexture = LoadTexture((assetPathPrefix + "nate.png").c_str());
    coneTexture = LoadTexture((assetPathPrefix + "coneSprite.png").c_str());
    coneGameOver = LoadTexture((assetPathPrefix + "gameOverCone.png").c_str());
    coneMainMenu = LoadTexture((assetPathPrefix + "coneMainMenu.png").c_str());


    
    // InitAudioDevice();
    // Load sounds/music here
}
    ConeStack *conestack = (ConeStack *)malloc(MAX_CONES*sizeof(conestack));

bool app_loop() {
    float relDt = GetFrameTime() * 60.0f; // Calculate delta time in relation to 60 frames per second

    //updates

    cone.Update(conesetup);

    int newStack = (conesetup.coneNumbers / 20) * 20;

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (cone.GetConeX() > (screenWidth/2 - coneTexture.width - 100) && cone.GetConeX() < (screenWidth/2 + coneTexture.width + 100)) {
        for (int i = 0; i < 1; i++) {
            if (conesetup.coneNumbers < MAX_CONES) {
            conestack[conesetup.coneNumbers].position.y = pedestal.GetPedestalPosY() - ((conesetup.coneNumbers % 20) * 8);
                    conesetup.coneNumbers ++;
                }
            }
        }
        else {
            conesetup.coneNumbers = 0;
            prevClear = 0;
            gameOver = true;
        }
    }

    if (IsKeyPressed(KEY_ENTER) && gameOver) {
        gameOver = false;
    }

    if (IsKeyPressed(KEY_ENTER) && mainMenu) {
        mainMenu = false;
    }

    if(conesetup.coneNumbers % 20 == 0 && conesetup.coneNumbers > prevClear) {
    memset(conestack, 0, MAX_CONES*sizeof(conestack));
    prevClear = conesetup.coneNumbers;
    }
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        if (mainMenu)
        {
            DrawTexture(coneMainMenu, screenWidth/2 - coneMainMenu.width/2, screenHeight/2 - coneMainMenu.height/2, WHITE);
            DrawTextCentered("Welcome to Cone Stacker Lite! ENTER to start.", screenWidth/2, 20, 20, BLACK);
        }

        else if (!gameOver) {
            for (int i = newStack; i < conesetup.coneNumbers; i++) {
                if (conesetup.coneNumbers > 0) {
                    DrawTexture(coneTexture, screenWidth/2 - 16, (int)conestack[i].position.y, WHITE);
                }
            }
                    DrawTexture(coneTexture, cone.GetConeX(), cone.GetConeY(), WHITE);
                    pedestal.Draw();
                    DrawTextCentered(TextFormat("%i", conesetup.coneNumbers), screenWidth/2, 10, 20, BLACK);
                }
                else {
                    DrawTexture(coneGameOver, screenWidth/2 - coneGameOver.width/2, screenHeight/2 - coneGameOver.height/2, WHITE);
                    DrawTextCentered("Game Over! ENTER to restart.", screenWidth/2, 20, 20, BLACK);

                }
    EndDrawing();
    
    return !windowShouldClose;
}

void deinit_app() {
    // Unload assets here
    free (conestack);
    UnloadTexture(coneTexture);
    // CloseAudioDevice();
}
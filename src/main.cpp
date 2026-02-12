#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../libs/raygui/src/raygui.h"

#include "main.hpp"
#include <string>
#include <filesystem>

#include "cone.h"
#include "pedestal.h"

#include "stdlib.h"

#define MAX_CONES 1500

// Window setup
int screenWidth = 720;
const int screenHeight = 480;
bool windowShouldClose = false;


// Loading resources
std::string assetPathPrefix = "../assets/";

//sum setup

Texture2D coneTexture;
Texture2D coneGameOver;


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


    
    // InitAudioDevice();
    // Load sounds/music here
}
    ConeStack *conestack = (ConeStack *)malloc(MAX_CONES*sizeof(conestack));

    int coneNumbers = 0;

bool app_loop() {
    float relDt = GetFrameTime() * 60.0f; // Calculate delta time in relation to 60 frames per second

    //updates

    cone.Update();

    if (IsKeyPressed(KEY_SPACE)) {
        if (cone.GetConeX() > (screenWidth/2 - coneTexture.width) && cone.GetConeX() < (screenWidth/2 + coneTexture.width)) {
        for (int i = 0; i < 1; i++) {
            if (coneNumbers < MAX_CONES) {
            conestack[coneNumbers].position.y = pedestal.GetPedestalPosY();
                    coneNumbers ++;
                }
            }
        }
    }
    
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        for (int i = 0; i < coneNumbers; i++) {
                if (cone.GetConeX() > (screenWidth/2 - coneTexture.width) && cone.GetConeX() < (screenWidth/2 + coneTexture.width)) {
                    DrawTexture(coneTexture, screenWidth/2 - 16, (int)conestack[i].position.y, WHITE);
                }
                else {
                    DrawTexture(coneGameOver, screenWidth/2 - coneGameOver.width/2, screenHeight/2 - coneGameOver.height/2, WHITE);
                }
            }
        // DrawTextCentered("You've successfully set up your Raylib project!", screenWidth/2, screenHeight/2-100, 20, DARKGRAY);
        // DrawTexture(nateTexture, screenWidth/2 - nateTexture.width/2, screenHeight/2 - nateTexture.height/2, WHITE);
        DrawTexture(coneTexture, cone.GetConeX(), cone.GetConeY(), WHITE);
        pedestal.Draw();
        DrawTextCentered(TextFormat("%i", coneNumbers), screenWidth/2, 10, 20, BLACK);
                
    EndDrawing();
    
    return !windowShouldClose;
}

void deinit_app() {
    // Unload assets here
    free (conestack);
    UnloadTexture(coneTexture);
    // CloseAudioDevice();
}
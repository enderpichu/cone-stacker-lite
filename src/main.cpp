#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../libs/raygui/src/raygui.h"

#include "main.hpp"
#include <string>
#include <filesystem>

#include "cone.h"
#include "pedestal.h"

// Window setup
int screenWidth = 720;
const int screenHeight = 480;
bool windowShouldClose = false;


// Loading resources
std::string assetPathPrefix = "../assets/";

//sum setup

Texture2D coneTexture;


Cone cone;
Pedestal pedestal;



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
    
    // InitAudioDevice();
    // Load sounds/music here
}

bool app_loop() {
    float relDt = GetFrameTime() * 60.0f; // Calculate delta time in relation to 60 frames per second

    //updates

    cone.Update();
    
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        // DrawTextCentered("You've successfully set up your Raylib project!", screenWidth/2, screenHeight/2-100, 20, DARKGRAY);
        // DrawTexture(nateTexture, screenWidth/2 - nateTexture.width/2, screenHeight/2 - nateTexture.height/2, WHITE);
        DrawTexture(coneTexture, cone.GetConeX(), cone.GetConeY(), WHITE);
        pedestal.Draw();
                
    EndDrawing();
    
    return !windowShouldClose;
}

void deinit_app() {
    // Unload assets here
    // UnloadTexture(nateTexture);
    UnloadTexture(coneTexture);
    // CloseAudioDevice();
}
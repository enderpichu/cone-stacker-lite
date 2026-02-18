#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../libs/raygui/src/raygui.h"

#include "main.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "cone.h"
#include "pedestal.h"
#include "coneNumberSetup.h"
#include "powerUpLocator.h"

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

static int highScore = 0;
static const char* kSaveFileName = "save.json";
bool newHi = false;

Texture2D coneTexture;
Texture2D coneGameOver;
Texture2D coneMainMenu;

Sound lose;
Sound stack;
Sound firstStack;
Music background;

ConeNumberSetup conesetup;
Cone cone;
Pedestal pedestal;
PowerUpLocation powerUps;
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

static int LoadHighScore(const char* path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return 0;
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();
    std::size_t pos = content.find("highScore");
    if (pos == std::string::npos) {
        return 0;
    }

    pos = content.find(":", pos);
    if (pos == std::string::npos) {
        return 0;
    }

    pos += 1;
    while (pos < content.size() && (content[pos] == ' ' || content[pos] == '\t')) {
        pos++;
    }

    int value = 0;
    while (pos < content.size() && content[pos] >= '0' && content[pos] <= '9') {
        value = (value * 10) + (content[pos] - '0');
        pos++;
    }

    return value;
}

static void SaveHighScore(const char* path, int score) {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        return;
    }

    out << "{\n  \"highScore\": " << score << "\n}\n";
}

void init_app() {
    if (std::filesystem::exists("../assets") == false) {
        assetPathPrefix = "assets/";
    }

    highScore = LoadHighScore(kSaveFileName);
    
    // Load textures here
    // nateTexture = LoadTexture((assetPathPrefix + "nate.png").c_str());
    coneTexture = LoadTexture((assetPathPrefix + "coneSprite.png").c_str());
    coneGameOver = LoadTexture((assetPathPrefix + "gameOverCone.png").c_str());
    coneMainMenu = LoadTexture((assetPathPrefix + "coneMainMenu.png").c_str());


    
    InitAudioDevice();
        lose = LoadSound((assetPathPrefix + "coneLose.ogg").c_str());
        stack = LoadSound((assetPathPrefix + "coneStack.ogg").c_str());
        firstStack = LoadSound((assetPathPrefix + "firstConeStacked.ogg").c_str());
        background = LoadMusicStream((assetPathPrefix + "backgroundCone.ogg").c_str());
        PlayMusicStream(background);
}
    ConeStack *conestack = (ConeStack *)malloc(MAX_CONES*sizeof(conestack));

bool app_loop() {
    float relDt = GetFrameTime() * 60.0f; // Calculate delta time in relation to 60 frames per second

    //updates
    UpdateMusicStream(background);

    cone.Update(conesetup);
    powerUps.Update(conesetup);


    int newStack = (conesetup.coneNumbers / 20) * 20;

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !gameOver && !mainMenu) {
        if (cone.GetConeX() > (screenWidth/2 - coneTexture.width - 10) && cone.GetConeX() < (screenWidth/2 + coneTexture.width + 10)) {
        for (int i = 0; i < 1; i++) {
            if (conesetup.coneNumbers < MAX_CONES) {
            conestack[conesetup.coneNumbers].position.y = pedestal.GetPedestalPosY() - ((conesetup.coneNumbers % 20) * 8);
                    conesetup.coneNumbers ++;
                    if (conesetup.coneNumbers % 20 == 1) {
                        PlaySound(firstStack);
                    }
                    else {
                        PlaySound(stack);
                    }
                    if (conesetup.coneNumbers > highScore) {
                        highScore = conesetup.coneNumbers;
                        newHi = true;
                    }
                }
            }
        }
        else {
            PlaySound(lose);
            conesetup.coneNumbers = 0;
            prevClear = 0;
            SaveHighScore(kSaveFileName, highScore);
            gameOver = true;
        }
    }

    if (IsKeyPressed(KEY_ENTER) && gameOver) {
        StopSound(lose);
        newHi = false;
        gameOver = false;
    }

    if (IsKeyPressed(KEY_ENTER) && mainMenu) {
        mainMenu = false;
    }

    if(conesetup.coneNumbers % 20 == 0 && conesetup.coneNumbers > prevClear) {
    memset(conestack, 0, MAX_CONES*sizeof(conestack));
    prevClear = conesetup.coneNumbers;
    }

    int coneScores = conesetup.coneNumbers;
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        if (mainMenu)
        {
            DrawTexture(coneMainMenu, screenWidth/2 - coneMainMenu.width/2, screenHeight/2 - coneMainMenu.height/2, WHITE);
            DrawTextCentered("Welcome to Cone Stacker Lite! ENTER to start.", screenWidth/2, 20, 20, BLACK);
        }

        else if (!gameOver && !mainMenu) {
            for (int i = newStack; i < conesetup.coneNumbers; i++) {
                if (conesetup.coneNumbers > 0) {
                    DrawTexture(coneTexture, screenWidth/2 - 16, (int)conestack[i].position.y, WHITE);
                }
            }
                    DrawTexture(coneTexture, cone.GetConeX(), cone.GetConeY(), WHITE);
                    pedestal.Draw();
                    powerUps.Draw();
                    DrawTextCentered(TextFormat("%i", conesetup.coneNumbers), screenWidth/2, 10, 20, BLACK);
                }
                else {
                    DrawTexture(coneGameOver, screenWidth/2 - coneGameOver.width/2, screenHeight/2 - coneGameOver.height/2, WHITE);
                    DrawTextCentered("Game Over! ENTER to restart.", screenWidth/2, 20, 20, BLACK);
                    if (newHi) {
                        DrawTextCentered("NEW HIGH!", screenWidth/2, 425, 40, BLACK);
                    }
                }
        if (highScore != 0) {
        DrawText(TextFormat("HI: %i", highScore), screenWidth - 100, 30, 20, BLACK);
        }
    EndDrawing();
    
    return !windowShouldClose;
}

void deinit_app() {
    // Unload assets here
    free (conestack);
    SaveHighScore(kSaveFileName, highScore);
    UnloadTexture(coneTexture);
    UnloadTexture(coneGameOver);
    UnloadTexture(coneMainMenu);
    UnloadSound(lose);
    UnloadSound(stack);
    UnloadSound(firstStack);
    UnloadMusicStream(background);
    CloseAudioDevice();
}
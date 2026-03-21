#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../libs/raygui/src/raygui.h"

#include "main.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstring>

#include "cone.h"
#include "pedestal.h"
#include "coneNumberSetup.h"
#include "powerUpLocator.h"

#include "stdlib.h"

// Window setup
int screenWidth = 720;
const int screenHeight = 480;
bool windowShouldClose = false;


// Loading resources
std::string assetPathPrefix = "../assets/";

//sum setup

//returns true when you lose;
bool gameOver = false;

//returns true when game startsup
bool mainMenu = true;

bool inPowerUp();

static int highScore = 0;
static const char* kSaveFileName = "save.json";
bool newHi = false;

double timer = 2.5;
bool slowDown;
bool teamColorize;

Texture2D coneTexture;
Texture2D teamCone;
Texture2D coneGameOver;
Texture2D teamGameOver;
Texture2D coneMainMenu;

Texture2D teamColor;
Texture2D timeLord;
Texture2D gimmighoul;

Sound lose;
Sound stack;
Sound firstStack;
Music background;

ConeNumberSetup conesetup;
Cone cone;
Pedestal pedestal;
PowerUpLocation powerUps;
ConeStack conestack[MAX_CONES] = {};

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
    teamCone = LoadTexture((assetPathPrefix + "truvianCone.png").c_str());

    coneGameOver = LoadTexture((assetPathPrefix + "gameOverCone.png").c_str());
    teamGameOver = LoadTexture((assetPathPrefix + "truvianGameOver.png").c_str());
    coneMainMenu = LoadTexture((assetPathPrefix + "coneMainMenu.png").c_str());

    teamColor = LoadTexture((assetPathPrefix + "teamColorsPowerUp.png").c_str());
    timeLord = LoadTexture((assetPathPrefix + "timePowerUp.png").c_str());
    gimmighoul = LoadTexture((assetPathPrefix + "goldenConePowerUp.png").c_str());

    InitAudioDevice();
        lose = LoadSound((assetPathPrefix + "coneLose.ogg").c_str());
        stack = LoadSound((assetPathPrefix + "coneStack.ogg").c_str());
        firstStack = LoadSound((assetPathPrefix + "firstConeStacked.ogg").c_str());
        background = LoadMusicStream((assetPathPrefix + "backgroundCone.ogg").c_str());
        PlayMusicStream(background);
}

bool app_loop() {
    float relDt = GetFrameTime() * 60.0f; // Calculate delta time in relation to 60 frames per second

    // inPowerUp() = CheckCollisionPointRec(GetMousePosition(), );

    Texture2D& coneTex = teamColorize ? teamCone : coneTexture;

    //
    UpdateMusicStream(background);
    cone.Update(conesetup);
    bool blockMouseStack = powerUps.IsMouseInBounds(conesetup);
    conesetup.Update(cone, pedestal, screenWidth, stack, firstStack, lose, coneTex, highScore, gameOver, mainMenu, newHi, blockMouseStack);
    if (slowDown) {
        cone.slowDownPUp(); // tick timer & apply half speed
        if (!cone.slowApplied) slowDown = false; // timer expired
    }
    if (teamColorize) {
        cone.TeamColorizePUp();
        if (!cone.IsPeak) teamColorize = false; //same as above
    }
    powerUps.Update(conesetup);
    
    int pickedPower = powerUps.EatPowerUp();
        if (pickedPower != 0) {
            switch (pickedPower) {
                case 1:
                    for (int i = 0; i < 5; i++) {
                        if (conesetup.coneNumbers >= MAX_CONES) {
                            break;
                        }

                        conestack[conesetup.coneNumbers].position.y = pedestal.GetPedestalPosY() - ((conesetup.coneNumbers % 20) * 8);
                        conesetup.coneNumbers++;

                        if (conesetup.coneNumbers > highScore) {
                            highScore = conesetup.coneNumbers;
                            newHi = true;
                        }
                    }
                break;
                    
                case 2:
                    slowDown = true;
                break;

                case 3:
                    teamColorize = true;
                break;
            }
        }
    int newStack = (conesetup.coneNumbers / 20) * 20;

    if (IsKeyPressed(KEY_ENTER) && gameOver) {
        StopSound(lose);
        newHi = false;
        gameOver = false;
    }

    if (IsKeyPressed(KEY_M) && gameOver) {
        StopSound(lose);
        newHi = false;
        gameOver = false;
        mainMenu = true;
    }

    if (IsKeyPressed(KEY_ENTER) && mainMenu) {
        mainMenu = false;
    }

    if(conesetup.coneNumbers % 20 == 0 && conesetup.coneNumbers > ConeNumberSetup::prevClear) {
    memset(conestack, 0, sizeof(conestack));
    ConeNumberSetup::prevClear = conesetup.coneNumbers;
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
                    DrawTexture(coneTex, screenWidth/2 - 16, (int)conestack[i].position.y, WHITE);
                }
            }
                    DrawTexture(coneTex, cone.GetConeX(), cone.GetConeY(), WHITE);
                    powerUps.Draw(gimmighoul, timeLord, teamColor, gameOver, mainMenu);
                    pedestal.Draw();
                    DrawTextCentered(TextFormat("%i", conesetup.coneNumbers), screenWidth/2, 10, 20, BLACK);
                }
                else {
                    DrawTexture(coneGameOver, screenWidth/2 - coneGameOver.width/2, screenHeight/2 - coneGameOver.height/2, WHITE);
                    DrawTextCentered("Game Over! ENTER to restart.", screenWidth/2, 20, 20, BLACK);
                    DrawTextCentered("M to return to main menu.", screenWidth/2, 50, 20, BLACK);
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
    SaveHighScore(kSaveFileName, highScore);
    UnloadTexture(coneTexture);
    UnloadTexture(coneGameOver);
    UnloadTexture(teamGameOver);
    UnloadTexture(coneMainMenu);
    UnloadTexture(teamColor);
    UnloadTexture(timeLord);
    UnloadTexture(gimmighoul);
    UnloadTexture(teamCone);
    UnloadSound(lose);
    UnloadSound(stack);
    UnloadSound(firstStack);
    UnloadMusicStream(background);
    CloseAudioDevice();
}
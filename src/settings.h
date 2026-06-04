#pragma once

#include "raylib.h"

enum ConeColor {
    TRAFFIC_CONE,
    TEAM_CONE
};

class SettingsMenu {
    public: 
        SettingsMenu();
        void Update();  
        void Draw() const;
};

struct Setting {
    ConeColor coneColor;
    bool enablePowerUps = true;

};
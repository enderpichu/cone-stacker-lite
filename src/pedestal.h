#pragma once

#include "raylib.h"

class Pedestal {
        public:
            Pedestal();
            void Draw() const;

        private:
            int x;
            int y;
            int height;
            int width;

};
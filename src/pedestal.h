#pragma once

#include "raylib.h"

class Pedestal {
        public:
            Pedestal();
            void Draw(int screenWidth) const;
            int GetPedestalPosY() const;
        private:
            int x;
            int y;
            mutable Vector2 pedestalPos;
            int height;
            int width;

};
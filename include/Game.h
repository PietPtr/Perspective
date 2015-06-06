#include <SFML/Graphics.hpp>
#include <iostream>
#include "Building.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void update();

        void draw();
        void drawBackground();

        bool isWindowOpen();
    protected:
    private:
        RenderWindow* window = nullptr;
        View view;

        Vector2f viewPosition {0, 0};

        int windowWidth = 1280;
        int windowHeight = 720;

        Building testBuilding { 256, 256, 1.1f, Vector2f(128, 128), Color(70, 70, 70)};

};

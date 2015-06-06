#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;
int main()
{
    int windowWidth = 1280;
    int windowHeigth = 720;
    RenderWindow window(VideoMode(windowWidth, windowHeigth), "Float");
    window.setVerticalSyncEnabled(true);

    Game game(&window);

    while (window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}

int randint(int low, int high, int seed)
{
    srand(seed);
    int value = rand() % (high + 1 - low) + low;
    return value;
}

int randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(time(NULL) * value * rand());

    return value;
}

float getDistance(Vector2f point1, Vector2f point2)
{
    float xdistance = fabs(point1.x - point2.x);
    float ydistance = fabs(point1.y - point2.y);
    return (float)sqrt(xdistance * xdistance + ydistance * ydistance);
}

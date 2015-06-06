#ifndef BUILDING_H
#define BUILDING_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Building
{
    public:
        Building(int width, int length, float height, Vector2f position, Color color);
        void update();
        void draw(RenderWindow* window, Vector2f viewPosition);
        void setHeight(float value) { height = value; }
        float getHeight() { return height; }
        Vector2f calcTopRectPos(Vector2f viewPosition);
    protected:
    private:
        int width = 0;  // x on screen
        int length = 0; // y on screen
        float height = 0; // used to calculate size of the roof
        IntRect baseRect;
        Vector2f position;
        Color color;
};

#endif // BUILDING_H

#include <iostream>
#include "Building.h"
#include <SFML/Graphics.hpp>

using namespace sf;

float getDistance(Vector2f point1, Vector2f point2);

Building::Building(int _width, int _length, float _height, Vector2f _position, Color _color)
{
    width = _width;
    length = _length;
    height = _height;
    position = _position;
    color = _color;
    baseRect = IntRect(position.x, position.y, width, length);                  //Use the position to set the IntRect position
    //position = Vector2f(position.x + width / 2.0, position.y + length / 2.0);   //Change the position to the center of baseRect
}

void Building::draw(RenderWindow* window, Vector2f viewPosition)
{
    //bottom for debugging (won't be drawn since it is invisible
    RectangleShape baseSprite; //only for testing and debugging
    baseSprite.setPosition(Vector2f(baseRect.left, baseRect.top));
    baseSprite.setSize(Vector2f(baseRect.width, baseRect.height));
    baseSprite.setFillColor(color);
    //baseSprite.setOutlineColor(Color(0, 200, 0));
    //baseSprite.setOutlineThickness(1);
    baseSprite.setOrigin(Vector2f(width / 2.0, length / 2.0));

    //the roof of the building
    RectangleShape roofSprite;
    roofSprite.setPosition(calcTopRectPos(viewPosition));
    roofSprite.setSize(Vector2f(width * height, length * height));
    roofSprite.setFillColor(color);
    roofSprite.setOrigin(Vector2f((width * height) / 2, (width * height) / 2));

    IntRect roofRect(roofSprite.getPosition().x - roofSprite.getSize().x / 2.0,
                     roofSprite.getPosition().y - roofSprite.getSize().y / 2.0,
                     roofSprite.getSize().x,
                     roofSprite.getSize().y);

    //dirty solution
    roofSprite.setSize(roofSprite.getSize() + Vector2f(2, 2));
    roofSprite.setPosition(roofSprite.getPosition() - Vector2f(1, 1));

    Vector2f roofPos(roofRect.left, roofRect.top);
    Vector2f basePos(baseRect.left - baseRect.width / 2.0, baseRect.top - baseRect.height / 2.0);

    //the walls of the building
    VertexArray southWall(Quads, 4);
    southWall[0].position = roofPos + Vector2f(0, roofRect.height);
    southWall[1].position = roofPos + Vector2f(roofRect.width, roofRect.height);
    southWall[2].position = basePos + Vector2f(baseRect.width, baseRect.height);
    southWall[3].position = basePos + Vector2f(0, baseRect.height);

    for (int i = 0; i < 4; i++)
        southWall[i].color = Color(color.r + 10, color.g + 10, color.b + 10);

    VertexArray eastWall(Quads, 4);
    eastWall[0].position = basePos + Vector2f(baseRect.width, baseRect.height);
    eastWall[1].position = roofPos + Vector2f(roofRect.width, roofRect.height);
    eastWall[2].position = roofPos + Vector2f(roofRect.width, 0);
    eastWall[3].position = basePos + Vector2f(baseRect.width, 0);

    for (int i = 0; i < 4; i++)
        eastWall[i].color = Color(color.r - 20, color.g - 20, color.b - 20);

    VertexArray northWall(Quads, 4);
    northWall[0].position = basePos;
    northWall[1].position = basePos + Vector2f(baseRect.width, 0);
    northWall[2].position = roofPos + Vector2f(roofRect.width, 0);
    northWall[3].position = roofPos;

    for (int i = 0; i < 4; i++)
        northWall[i].color = Color(color.r - 10, color.g - 10, color.b - 10);

    VertexArray westWall(Quads, 4);
    westWall[0].position = basePos + Vector2f(0, baseRect.height);
    westWall[1].position = roofPos + Vector2f(0, roofRect.height);
    westWall[2].position = roofPos;
    westWall[3].position = basePos;

    for (int i = 0; i < 4; i++)
        westWall[i].color = Color(color.r + 20, color.g + 20, color.b + 20);

    window->draw(baseSprite);

    Vector2f baseCenter = basePos + Vector2f(baseRect.width / 2, baseRect.height / 2);
    Vector2f roofCenter = roofPos + Vector2f(roofRect.width / 2, roofRect.height / 2);

    //The difference in length and width of the roof and floor (used to calculate what walls to draw
    int dw = (roofRect.width - baseRect.width) / 2.0f;   //delta width
    int dl = (roofRect.height - baseRect.height) / 2.0f; //delta height

    if (roofCenter.x <= baseCenter.x - dw && roofCenter.y <= baseCenter.y - dl)
    {
        window->draw(eastWall);
        window->draw(southWall);
    }
    else if (roofCenter.x >= baseCenter.x + dw && roofCenter.y <= baseCenter.y - dl)
    {
        window->draw(westWall);
        window->draw(southWall);
    }
    else if (roofCenter.x >= baseCenter.x + dw && roofCenter.y >= baseCenter.y + dl)
    {
        window->draw(westWall);
        window->draw(northWall);
    }
    else if (roofCenter.x <= baseCenter.x - dw && roofCenter.y >= baseCenter.y + dl)
    {
        window->draw(eastWall);
        window->draw(northWall);
    }
    else if (roofCenter.x >= baseCenter.x - dw && roofCenter.x <= baseCenter.x + dw)
    {
        if (roofCenter.y > baseCenter.y)
        {
            window->draw(northWall);
        }
        else if (roofCenter.y <= baseCenter.y)
        {
            window->draw(southWall);
        }
    }
    else if (roofCenter.y >= baseCenter.y - dl && roofCenter.y <= baseCenter.y + dw)
    {
        if (roofCenter.x > baseCenter.x)
        {
            window->draw(westWall);
        }
        else if (roofCenter.x <= baseCenter.x)
        {
            window->draw(eastWall);
        }
    }

    CircleShape bot(3);
    bot.setPosition(basePos + Vector2f(baseRect.width / 2, baseRect.height / 2));

    CircleShape top(3);
    top.setPosition(roofPos + Vector2f(roofRect.width / 2, roofRect.height / 2));

    window->draw(roofSprite);

    //window->draw(bot);
    //window->draw(top);

    //std::cout << viewPosition.x << " " << viewPosition.y << "\n";
}

Vector2f Building::calcTopRectPos(Vector2f viewPosition)
{
    Vector2f topRectPos;

    //a = -fb
    Vector2f a = Vector2f(viewPosition.x - position.x, viewPosition.y - position.y); //a

    float f = 4.0f;

    Vector2f b = -(a / f) * height * height;

    topRectPos = position + b;

    return topRectPos;
}

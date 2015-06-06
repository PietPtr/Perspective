#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cmath>

using namespace sf;

int randint(int low, int high, int seed);

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
            if (event.key.code == Keyboard::Add)
            {
                testBuilding.setHeight(testBuilding.getHeight() + 0.1f);
            }
            if (event.key.code == Keyboard::Return)
            {
                testBuilding.setHeight(testBuilding.getHeight() - 0.1f);
            }
        }
        if (event.type == Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            windowWidth = event.size.width;
            windowHeight = event.size.height;
            window->setView(View(visibleArea));
        }
    }

    int deadzone = 30;
    if (std::abs(Joystick::getAxisPosition(0, Joystick::X)) > deadzone)
    {
        viewPosition.x += (Joystick::getAxisPosition(0, Joystick::X) / 20.0f);
    }
    if (std::abs(Joystick::getAxisPosition(0, Joystick::Y)) > deadzone)
    {
        viewPosition.y += (Joystick::getAxisPosition(0, Joystick::Y) / 20.0f);
    }
}

void Game::draw()
{
    window->clear();

    //set the view
    view.setCenter(viewPosition);
    view.setSize(windowWidth, windowHeight);
    window->setView(view);

    drawBackground();

    CircleShape player(5);
    player.setFillColor(Color(0, 200, 0));
    player.setPosition(viewPosition);
    window->draw(player);

    testBuilding.draw(window, viewPosition);

    window->display();
}

void Game::drawBackground()
{
    //Draw the background
    int tileSize = 16;

    RectangleShape background;
    background.setSize(Vector2f(tileSize, tileSize));
    background.setOutlineColor(Color(120, 120, 120));
    background.setOutlineThickness(1);
    Vector2f topLeftTile;

    topLeftTile.x = (int)(viewPosition.x - windowWidth / 2.0f);
    topLeftTile.x = topLeftTile.x - (int)topLeftTile.x % tileSize - tileSize;

    topLeftTile.y = (int)(viewPosition.y - windowHeight / 2.0f);
    topLeftTile.y = topLeftTile.y - (int)topLeftTile.y % tileSize - tileSize;

    for (int y = -3; y < (int)(windowHeight / tileSize) + 3; y++)
    {
        for (int x = -3; x < (int)(windowWidth / tileSize) + 3; x++)
        {
            //background.setTextureRect(IntRect(randint(0, 7, ((int)(y + topLeftTile.y / 16) % 4096 + 65536) * ((int)(x + topLeftTile.x / 16) % 4096 + 65536)) * 16, 64, 16, 16));
            int seed = ((int)(y + topLeftTile.y / 16) % 4096 + 65536) * ((int)(x + topLeftTile.x / 16) % 4096 + 65536);
            int randomGrey = randint(150, 190, seed);
            background.setFillColor(Color(randomGrey, randomGrey, randomGrey));
            background.setPosition(x * tileSize + topLeftTile.x, y * tileSize + topLeftTile.y);
            window->draw(background);
        }
    }
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}








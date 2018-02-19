#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <math.h>
#include <algorithm>

//My grid and snake libraries

#include "Snake.hpp"
#include "Grid.hpp"
#include "Button.hpp"
#include "StartScreen.hpp"
#include "Util.hpp"

// Do we want to showcase direct JNI/NDK interaction?
// Undefine this to get real cross-platform code.
// These headers are only needed for direct NDK/JDK interaction
#include <jni.h>
#include <android/native_activity.h>

// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>

//Maps one range to another
double Map(double n, double start1, double stop1, double start2, double stop2)
{
    return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

int getWidthOfGridBlock(unsigned int Width, unsigned int Height, unsigned int Rows, unsigned int Cols)
{
    unsigned int NewWidth = ((Width / Cols) + (Height / Rows)) / 2;
    return --NewWidth; //Subtract one to account of the 1 px border
}
// NDK/JNI sub example - call Java code from native code
// This is the actual Android example. You don't have to write any platform
// specific code, unless you want to use things not directly exposed.
// ('vibrate()' in this example; undefine 'USE_JNI' above to disable it)
int main(int argc, char *argv[])
{
    // Initialization of variables:
    srand(time(0)); //Fruit positioning

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");

    const int offset = 120; //Offset from top so that we can position the text

    window.setFramerateLimit(64); //Needs to be slow so that it can be a bit easier

    unsigned int Rows = 31;
    unsigned int Cols = 19;

    bool SwipeState = false; // If using d-pad, true, else false

    // Declare and load a font
    sf::Font font;
    font.loadFromFile("sansation.ttf"); //Default font with
    // Create a text
    sf::Text text("0", font);
    text.setCharacterSize(60);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    text.setPosition(window.getSize().x / 2 - (text.getString().getSize() * (text.getCharacterSize() / 5)) - 2, 2);

    // unsigned int BlockWidth = getWidthOfGridBlock(window.getSize().x, window.getSize().y, Rows, Cols);
    unsigned int BlockWidth = 54;

    Grid g(Rows, Cols, BlockWidth, BlockWidth, 2, 2);

    g.Pos = sf::Vector2f(0, 0);

    {
        sf::Vector2f WindowSize = sf::Vector2f(window.getSize().x, window.getSize().y - 60);
        sf::Vector2f gSize = g.GetSize();
        sf::Vector2f Centered = sf::Vector2f(WindowSize.x - gSize.x, WindowSize.y - gSize.y);
        sf::Vector2f Halved = sf::Vector2f(Centered.x / 2, 60 + (Centered.y / 2));
        g.Pos = Halved;
    }

    Snake s(sf::Vector2f(5, 5), sf::Vector2f(Rows, Cols));

    //s.Body.push_back(sf::Vector2f(25, 25));

    sf::Vector2<float> Fruit((rand() % (Rows - 2)) + 1, (rand() % (Cols - 2)) + 1);

    g.Tiles[Fruit.x][Fruit.y] = sf::Color::Red;

    sf::Vector2f start(-200, -200);

    sf::View view = window.getDefaultView();

    const int C_Radius = 120;
    const int SC_Radius = 52;

    sf::CircleShape circle;
    circle.setRadius(C_Radius);
    circle.setOrigin(C_Radius, C_Radius);
    circle.setFillColor(sf::Color(128, 128, 128, 120));
    circle.setPosition(-200, -200);

    sf::CircleShape scircle;
    scircle.setRadius(SC_Radius);
    scircle.setOrigin(SC_Radius, SC_Radius);
    scircle.setFillColor(sf::Color(128, 128, 128, 120));
    scircle.setPosition(-200, -200);

    Button SwipeToggle;
    SwipeToggle.setPosition(sf::Vector2f(5, 5));
    SwipeToggle.setSize(sf::Vector2f(window.getSize().x / 2 - (55), offset - 30));
    SwipeToggle.getInternalRectangle().setFillColor(sf::Color::Blue + sf::Color(60, 60, 60));
    SwipeToggle.optionalText.setString("Toggle D-Pad");
    SwipeToggle.optionalText.setCharacterSize(50);
    SwipeToggle.optionalText.setFillColor(sf::Color::Black);
    SwipeToggle.optionalText.setFont(font);
    SwipeToggle.optionalText.setOrigin(sf::Vector2f(SwipeToggle.optionalText.getGlobalBounds().width / 2, SwipeToggle.optionalText.getGlobalBounds().height / 2));
    // SwipeToggle.setTextPosition(sf::Vector2f(SwipeToggle.getSize().width / 2 - (SwipeToggle.optionalText.getString().getSize() * (SwipeToggle.optionalText.getCharacterSize() / 5)), 45));
    SwipeToggle.setTextPosition(sf::Vector2f(SwipeToggle.getSize().width / 2, (SwipeToggle.getSize().height / 2) - 5));
    // SwipeToggle.optionalText.setPosition(20, 20);

    bool hasMoved = false;
    int frame; //Used to reduce framerate
    while (window.isOpen())
    {
        {

            sf::Event event;

            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                {
                    view.setSize(event.size.width, event.size.height);
                    view.setCenter(event.size.width / 2, event.size.height / 2);
                    window.setView(view);
                    Rows = (window.getSize().x / BlockWidth) - 1;
                    Cols = ((window.getSize().y - offset) / BlockWidth) - 1;
                    int oldBodyCount = s.Body.size() - 3;
                    s = Snake(sf::Vector2f(5, 5), sf::Vector2f(Rows, Cols));
                    g = Grid(Rows, Cols, BlockWidth, BlockWidth, g.XSkew, g.YSkew);
                    {
                        sf::Vector2f WindowSize = sf::Vector2f(window.getSize().x, window.getSize().y - 60);
                        sf::Vector2f gSize = g.GetSize();
                        sf::Vector2f Centered = sf::Vector2f(WindowSize.x - gSize.x, WindowSize.y - gSize.y);
                        sf::Vector2f Halved = sf::Vector2f(Centered.x / 2, 60 + (Centered.y / 2));
                        g.Pos = Halved;
                    }
                    Fruit = sf::Vector2f(rand() % Rows, rand() % Cols);
                    text.setPosition(window.getSize().x / 2 - (text.getString().getSize() * (text.getCharacterSize() / 5)) - 2, 2);
                    SwipeToggle.setSize(sf::Vector2f(window.getSize().x / 2 - (55), offset - 30));
                    SwipeToggle.setTextPosition(sf::Vector2f(SwipeToggle.getSize().width / 2, (SwipeToggle.getSize().height / 2) - 5));
                }
                break;

                case sf::Event::GainedFocus:
                {
                    g.Tiles[0][0] = sf::Color::Yellow;
                    view.setSize(event.size.width, event.size.height);
                    view.setCenter(event.size.width / 2, event.size.height / 2);
                    window.setView(view);
                    Rows = (window.getSize().x / BlockWidth) - 1;
                    Cols = ((window.getSize().y - offset) / BlockWidth) - 1;
                    int oldBodyCount = s.Body.size() - 3;
                    s = Snake(sf::Vector2f(5, 5), sf::Vector2f(Rows, Cols));
                    g = Grid(Rows, Cols, BlockWidth, BlockWidth, g.XSkew, g.YSkew);
                    {
                        sf::Vector2f WindowSize = sf::Vector2f(window.getSize().x, window.getSize().y - 60);
                        sf::Vector2f gSize = g.GetSize();
                        sf::Vector2f Centered = sf::Vector2f(WindowSize.x - gSize.x, WindowSize.y - gSize.y);
                        sf::Vector2f Halved = sf::Vector2f(Centered.x / 2, 60 + (Centered.y / 2));
                        g.Pos = Halved;
                    }
                    text.setPosition(window.getSize().x / 2 - (text.getString().getSize() * (text.getCharacterSize() / 5)) - 2, 2);
                    Fruit = sf::Vector2f(rand() % Rows, rand() % Cols);
                    SwipeToggle.setSize(sf::Vector2f(window.getSize().x / 2 - (55), offset - 30));
                    SwipeToggle.setTextPosition(sf::Vector2f(SwipeToggle.getSize().width / 2, (SwipeToggle.getSize().height / 2) - 5));
                }
                break;

                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0)
                    {
                        if (event.touch.y > offset)
                        {
                            //g.Tiles[0][0] = sf::Color::Red;
                            start = sf::Vector2f(event.touch.x, event.touch.y);
                            circle.setPosition(start);
                            float Radius = (std::min(dist(circle.getPosition(), sf::Vector2f(event.touch.x, event.touch.y)), C_Radius - SC_Radius + 0.f)); //Calculates Radius
                            scircle.setPosition(sf::Vector2f(
                                                    (Radius * cosf(getAngle(start, sf::Vector2f(event.touch.x, event.touch.y)))),
                                                    (Radius * sinf(getAngle(start, sf::Vector2f(event.touch.x, event.touch.y)))) * -1) +
                                                circle.getPosition());
                        }
                        else
                        {
                            SwipeToggle.getInternalRectangle().setFillColor(sf::Color::Blue + sf::Color(100, 100, 100));
                        }
                    }
                    break;
                case sf::Event::TouchEnded:
                    if (event.touch.finger == 0)
                    {
                        if (event.touch.y > offset)
                        {
                            s.setVel(start, sf::Vector2f(event.touch.x, event.touch.y));
                        }
                        else if (SwipeToggle.isTouched(event.touch))
                        {
                            SwipeState = !SwipeState;
                            SwipeToggle.getInternalRectangle().setFillColor(sf::Color::Blue + sf::Color(60, 60, 60));
                        }
                    }
                    break;
                case sf::Event::TouchMoved:
                    if (event.touch.finger == 0)
                    {
                        if (event.touch.x > offset)
                        {
                            if (SwipeState)
                            {
                                //stop = sf::Vector2f( event.touch.x, event.touch.y);
                                //g.Tiles[0][0] = sf::Color::Blue;
                                if (!hasMoved)
                                {
                                    s.setVel(start, sf::Vector2f(event.touch.x, event.touch.y));
                                    hasMoved = true;
                                }
                                // scircle.setPosition(sf::Vector2f(
                                //text.setString(std::to_string(toGradians(getAngle(start, sf::Vector2f(event.touch.x, event.touch.y)))));
                                float Radius = (std::min(dist(circle.getPosition(), sf::Vector2f(event.touch.x, event.touch.y)), C_Radius - SC_Radius + 0.f)); //Calculates Radius
                                scircle.setPosition(sf::Vector2f(
                                                        (Radius * cosf(getAngle(start, sf::Vector2f(event.touch.x, event.touch.y)))),
                                                        (Radius * sinf(getAngle(start, sf::Vector2f(event.touch.x, event.touch.y)))) * -1) +
                                                    circle.getPosition());
                                // scircle.setPosition(circle.getPosition());
                                hasMoved = true;
                            }
                        }
                        else
                        {
                            if (SwipeToggle.isTouched(event.touch))
                            {
                                SwipeToggle.getInternalRectangle().setFillColor(sf::Color::Blue + sf::Color(100, 100, 100));
                            }
                            else
                            {
                                SwipeToggle.getInternalRectangle().setFillColor(sf::Color::Blue + sf::Color(60, 60, 60));
                            }
                        }
                    }
                    break;
                }
            }
        }

        if (Fruit == s.Head)
        {
            s.Body.push_back(sf::Vector2f(s.GhostTail));
            //window.setFramerateLimit(static_cast<int>(std::max(Map(s.Body.size() - 3, 0, 30, 15, 9), 9.0)));

            while (s.Contains(Fruit))
            {
                Fruit = sf::Vector2<float>((rand() % (Rows - 2)) + 1, (rand() % (Cols - 2)) + 1);
            }
            text.setPosition(window.getSize().x / 2 - (text.getString().getSize() * (text.getCharacterSize() / 5)) - 2, 2);
            text.setString(std::to_string(s.Body.size() - 3));
        }

        if (frame % 8 == 0)
        {
            s.Move();

            hasMoved = false;
        }
        // sf::Transform t;
        // t.translate(0, offset);

        for (sf::Vector2f r : s.Body)
        {
            g.Tiles[r.x][r.y] = sf::Color::White;
        }

        g.Tiles[s.GhostTail.x][s.GhostTail.y] = sf::Color::Black;

        g.Tiles[s.Head.x][s.Head.y] = sf::Color::Cyan;

        g.Tiles[Fruit.x][Fruit.y] = sf::Color::Red;

        window.clear(sf::Color(72, 70, 72));
        // window.draw(g, sf::RenderStates(t));
        window.draw(g);
        window.draw(text);
        window.draw(SwipeToggle);
        if (SwipeState)
        {
            window.draw(circle);
            window.draw(scircle);
        }
        window.display();

        if (s.CheckDead() && !s.IsStuffed())
        {
            s = Snake(sf::Vector2f(5, 5), sf::Vector2f(Rows, Cols));
            g = Grid(Rows, Cols, BlockWidth, BlockWidth, g.XSkew, g.YSkew);
            {
                sf::Vector2f WindowSize = sf::Vector2f(window.getSize().x, window.getSize().y - 60);
                sf::Vector2f gSize = g.GetSize();
                sf::Vector2f Centered = sf::Vector2f(WindowSize.x - gSize.x, WindowSize.y - gSize.y);
                sf::Vector2f Halved = sf::Vector2f(Centered.x / 2, 60 + (Centered.y / 2));
                g.Pos = Halved;
            }
            text.setString(std::to_string(s.Body.size() - 3));
            //window.setFramerateLimit(static_cast<int>(std::max(Map(s.Body.size() - 3, 0, 30, 15, 9), 9.0)));
            //g.Tiles[0][0] = sf::Color::Yellow;
            //move = 0;
        }
        frame++;
    }
}

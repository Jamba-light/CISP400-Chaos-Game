// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    sf::Texture texture;
    if (!texture.loadFromFile("ObiDog.jpg"))
        return(-1);
    sf::Sprite Obi;
    Obi.setTexture(texture);

	while (window.isOpen())
	{
        /*
		****************************************
		Prompt the player
		****************************************
		*/
        sf::Font font;
        if (!font.loadFromFile("coolvetica.ttf"))
            return(-1);
        
        sf::Text firstText;
        firstText.setFont(font);
        firstText.setString("Click any three points on the screen to create the vertices for the triangle.");
        firstText.setCharacterSize(60);
        firstText.setFillColor(sf::Color::White);
        firstText.setPosition(0, 900);

        sf::Text secondText;
        secondText.setFont(font);
        secondText.setString("Create a 4th point to start the algorithm.");
        secondText.setCharacterSize(60);
        secondText.setFillColor(sf::Color::White);  
        secondText.setPosition(0, 900);

       

        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

        /*
		****************************************
		Update
		****************************************
		*/
        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            
            for (int i = 0; i < 100; i++)
            {
                int randomVert = rand() % vertices.size();

                double x = (points.back().x + vertices.at(randomVert).x) / 2.0;
                double y = (points.back().y + vertices.at(randomVert).y) / 2.0;

                points.push_back(Vector2f(x, y));
            }
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        window.draw(Obi);

        if (vertices.size() < 3)
        {
            window.draw(firstText);
        }
        else if (points.size() == 0)
        {
            window.draw(secondText);
        }

        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
       
        for (unsigned int i = 0; i < points.size(); i++)
        {
            RectangleShape fill(Vector2f(3, 3));
            fill.setPosition(Vector2f(points[i].x, points[i].y));
            fill.setFillColor(Color::White);
            window.draw(fill);
        }
        
        window.display();
    }
}

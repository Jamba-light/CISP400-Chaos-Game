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

	while (window.isOpen())
	{
        /*
		****************************************
		Prompt the player
		****************************************
		*/
        sf::Font font;
        font.loadFromFile("coolvetica.ttf");
        if (!font.loadFromFile("coolvetica.ttf"))
        {
            exit(69);
        }
        
        sf::Text firstText;
        firstText.setFont(font);
        firstText.setString("Click any three points on the screen to create the vertices for the triangle.");
        firstText.setCharacterSize(50);
        firstText.setFillColor(sf::Color::White);
        firstText.setPosition(20, 20);

        sf::Text secondText;
        secondText.setFont(font);
        secondText.setString("Create a 4th point to start the algorithm.");
        secondText.setCharacterSize(75);
        secondText.setFillColor(sf::Color::White);  
        secondText.setPosition(300, 740);

       

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
            
            int randomVert = rand() % vertices.size();

            double x = (points.back().x + vertices.at(randomVert).x) / 2.0;
            double y = (points.back().y + vertices.at(randomVert).y) / 2.0;
            
            points.push_back(Vector2f(x, y));
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        if (vertices.size() < 3)
        {
            window.draw(firstText);
        }
        else if (points.size() == 0)
        {
            window.draw(secondText);
        }

      
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }
       
      

        for (int i = 0; i < points.size(); i++)
        {
            CircleShape circ(3, 3);
            circ.setPosition(Vector2f(points[i].x, points[i].y));
            circ.setFillColor(Color::White);
            window.draw(circ);
        }
        

        window.display();
    }
}

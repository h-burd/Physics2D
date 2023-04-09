#include <iostream>
#include <vector>
#include "physics.hpp"
#include "render.hpp"
#include "solver.hpp"
#include <SFML/Graphics.hpp>

using namespace std;



int main()
{
    // setup window
    const int32_t window_width  = 1000;
    const int32_t window_height = 1000;
    const uint32_t frame_rate = 60;

    
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Physics Simulation");
    window.setFramerateLimit(frame_rate);

    sf::Clock clock;

    // create vector of physics objects
    vector<Physics2D> objects;

    Render render;
    Solver solver;





    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (clock.getElapsedTime().asSeconds() >= 0.1))
            {
                clock.restart();
                Physics2D obj(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                objects.push_back(obj);
                // cout << objects.size() << endl;
            }
        }

        window.clear();
        render.renderObjects(objects, window);
        solver.varlet_solver(objects, 0.1);
        window.display();
    }


    return 0;
}

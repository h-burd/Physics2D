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
    vector<Sticks2D> sticks;

    Render render;
    Solver solver(0.2);

    // Physics2D obj(500 - 30,500 - 30, 0.0);
    // objects.push_back(obj);

    Physics2D obj(530, 0, 0.0);
    objects.push_back(obj);

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
                Physics2D obj(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 0.5);
                objects.push_back(obj);
                const double a = (sf::Mouse::getPosition(window).x - objects[0].x_pos);
                const double b = (sf::Mouse::getPosition(window).y - objects[0].y_pos);
                // distance from the object to the center of the screen
                const double R = sqrt((a * a) + (b * b));
                Sticks2D stk(50, objects.size() - 1, objects.size() - 2);
                sticks.push_back(stk);
                for (int i = 0; i < objects.size(); ++i)
                {
                    objects[i].fixed = false;
                }
                objects[0].fixed = true;
                objects[objects.size() - 1].fixed = true;
                // cout << "objects: " << objects.size() << "sticks: " << sticks.size() << endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                objects[0].x_pos = sf::Mouse::getPosition(window).x;
                objects[0].y_pos = sf::Mouse::getPosition(window).y;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                objects[objects.size() - 1].x_pos = sf::Mouse::getPosition(window).x;
                objects[objects.size() - 1].y_pos = sf::Mouse::getPosition(window).y;
            }
            
        }

        window.clear(sf::Color(46, 42, 46));
        render.render_objects(objects, sticks, window);
        solver.sticks_solver(sticks, objects);
        solver.verlet_solver(objects);
        // solver.circle_constraint_solver(objects);
        solver.screen_constraint_solver(objects);
        // solver.collision_solver(objects);
        window.display();
    }

    return 0;
}

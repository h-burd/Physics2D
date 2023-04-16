#include <iostream>
#include <vector>
#include "physics.hpp"
#include "render.hpp"
#include "solver.hpp"
#include "input.hpp"
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

    Render render(window, objects, sticks);
    Solver solver(0.2);
    Input input;

    // create inital physics object
    Physics2D obj(530, 0, 0.5);
    obj.fixed = true;
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
                // Physics2D obj(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, 0.5);
                Physics2D obj(objects[objects.size() - 1].x_pos + 50, objects[objects.size() - 1].y_pos + 50, 0.5);

                objects.push_back(obj);
                Sticks2D stk(50, objects.size() - 1, objects.size() - 2);
                sticks.push_back(stk);
            }
            
            // Move the positoin of the closest object to the mouse
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && (clock.getElapsedTime().asSeconds() >= 0.1)){
                objects[input.find_closest_object(objects, window)].x_pos = sf::Mouse::getPosition(window).x;
                objects[input.find_closest_object(objects, window)].y_pos = sf::Mouse::getPosition(window).y;
            }
            
            // Toggle if an object has a fixed position
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && (clock.getElapsedTime().asSeconds() >= 0.1)){
                if(objects[input.find_closest_object(objects, window)].fixed){
                    objects[input.find_closest_object(objects, window)].fixed = false;
                } else {
                    objects[input.find_closest_object(objects, window)].fixed = true;
                }
            }

            // Delete an object and remove stick connections using right arrow key
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (clock.getElapsedTime().asSeconds() >= 0.1)){
                const int closestObjectIndex = input.find_closest_object(objects, window);
                objects.erase(objects.begin() + closestObjectIndex);
                int stickBreakIndex;
                for (int i = 0; i < sticks.size(); i++){
                    if(sticks[i].obj1 == closestObjectIndex || sticks[i].obj2 == closestObjectIndex){
                        sticks.erase(sticks.begin() + i);
                        stickBreakIndex = i;
                    };
                }
                for (int i = stickBreakIndex; i < sticks.size(); i++){
                    sticks[i].obj1 -= 1;
                    sticks[i].obj2 -= 1;
                }
                // cout << "objs: " << objects.size() << "stks: " << sticks.size() << endl;
            }

        }

        window.clear(sf::Color(46, 42, 46));
        render.render_objects();
        solver.sticks_solver(sticks, objects);
        solver.verlet_solver(objects);
        // solver.circle_constraint_solver(objects);
        solver.screen_constraint_solver(objects);
        // solver.collision_solver(objects);
        window.display();
    }

    return 0;
}

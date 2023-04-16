#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>



using namespace std;

class Render
{


public:
	sf::RenderWindow renderWindow;

	Render(sf::RenderWindow& renderWindow, vector<Physics2D>& objects, vector<Sticks2D>& sticks) : window(renderWindow), objs(objects), stk(sticks) {}

	void render_objects() 
	{ 
		sf::CircleShape circle;

		for(int i = 0; i < stk.size(); i++){
			sf::Vertex line[] =
			{
			    sf::Vertex(sf::Vector2f(objs[stk[i].obj1].x_pos + objs[stk[i].obj1].radius,objs[stk[i].obj1].y_pos + objs[stk[i].obj1].radius),sf::Color(254,254,254)),
			    sf::Vertex(sf::Vector2f(objs[stk[i].obj2].x_pos + objs[stk[i].obj2].radius,objs[stk[i].obj2].y_pos + objs[stk[i].obj2].radius),sf::Color(254,254,254))
			};
			window.draw(line, 2, sf::Lines);
		}
		

    	for (int i = 0; i < objs.size(); i++){
    		// count += vect[i].x_vel;
			// circle.setOutlineThickness(10);
			
    		circle.setRadius(objs[i].radius);
    		if(objs[i].fixed){
    			circle.setFillColor(sf::Color(249,38,114));
    		} else {
    			circle.setFillColor(sf::Color(0,176,255));
    		}
			circle.setPosition(objs[i].x_pos, objs[i].y_pos);    		
        	window.draw(circle);
    	}
	}
    // Colors list: [(249,38,114), (61,209,119), (255,201,0),(174, 129, 255), (255,63,128), (0,176,255), (254,254,254)]

private:
	sf::RenderWindow& window;
	vector<Physics2D>& objs;
	vector<Sticks2D>& stk;

};
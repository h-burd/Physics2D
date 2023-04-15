#pragma once
#include <vector>
#include <SFML/Graphics.hpp>



using namespace std;

class Render
{
public:    
	void render_objects(const vector<Physics2D> &objs, const vector<Sticks2D> &stk, sf::RenderWindow& window) 
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


};
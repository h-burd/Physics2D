#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


using namespace std;

class Render
{
public:    

	void renderObjects(const vector<Physics2D> &vect, sf::RenderWindow& window) 
	{ 
		sf::CircleShape circle;
		// circle.setRadius(30);
		// circle.setOutlineColor(sf::Color::Red);
		// circle.setOutlineThickness(5);
    	for (int i = 0; i < vect.size(); i++){
    		// count += vect[i].x_vel;
    		circle.setRadius(30);
			circle.setPosition(vect[i].x_pos, vect[i].y_pos);    		
        	window.draw(circle);
    	}
	}

	
};
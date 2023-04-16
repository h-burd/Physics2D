#pragma once

#include <iostream>

class Input
{
public:
	Input(){
		mouseDown = false;
	};

	// function that returns the index of the object in the list that is closest to the mouse
	int find_closest_object(const vector<Physics2D> &objs, sf::RenderWindow &window){
		double dist = 400;
        int distIndex = 0;
        for (int i = 0; i < objs.size(); ++i)
        {
            const double a = (sf::Mouse::getPosition(window).x - objs[i].x_pos);
            const double b = (sf::Mouse::getPosition(window).y - objs[i].y_pos);
            const double R = sqrt((a * a) + (b * b));
            if(dist > R){
                dist = R;
                distIndex = i;
            }
        }
        return distIndex;
	}

	void update(){
		
	}
	

private:
	int closestObjectIndex;
	bool mouseDown;

};

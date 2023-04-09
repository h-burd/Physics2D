#pragma once

#include <cmath>
#include <iostream>

const int32_t window_width  = 1000;
const int32_t window_height = 1000;

class Solver
{
public:

	void varlet_solver(vector<Physics2D>& vect, float dt) {
		for (int i = 0; i < vect.size(); i++){
			const double y_velnew = (vect[i].y_vel) + (vect[i].y_acc * dt);
			vect[i].y_pos += y_velnew * dt;
			vect[i].y_vel = y_velnew;

    	}
	}

	// Constraint keeps objects on screen in a circle
	void constraint_solver(vector<Physics2D>& vect){
		for (int i = 0; i < vect.size(); i++){
			// constraint center = (screen width / 2, screen heigh / 2)
			// constraint radius = 400;
			const double a = (vect[i].x_pos - (window_width / 2));
			const double b = (vect[i].y_pos - (window_height / 2));
			// distance from the object to the center of the screen
			const double R = sqrt((a * a) + (b * b));
			// if object is too far adjust the position
			if (R > (400 - vect[i].radius)){
				vect[i].x_pos = ((400 / R) * a) + (window_width / 2);
				vect[i].y_pos = ((400 / R) * b) + (window_height / 2);
			}
    	}
	}

	void collision_solver(vector<Physics2D>& vect){
		for (int i = 0; i < vect.size(); i++){
			for (int j = 0; j < vect.size(); ++j)
			{
				if(i != j){
					const double a = vect[j].x_pos - vect[i].x_pos;
					const double b = vect[j].y_pos - vect[i].y_pos;

					const double R = sqrt((a * a) + (b * b));

					if(R/2 < vect[i].radius){
						vect[j].x_pos += (abs(a)/3);
						vect[i].x_pos -= (abs(a)/3);
						vect[j].y_pos += (abs(b)/3);
						vect[i].y_pos -= (abs(b)/3);

					}
				}
			}
			



    	}
	}

	
};

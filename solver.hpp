#pragma once

#include <cmath>
#include <iostream>

const int32_t window_width  = 1000;
const int32_t window_height = 1000;

class Solver
{
public:

	Solver(vector<Physics2D>& objects, vector<Sticks2D>& sticks) : objs(objects), stks(sticks) {}


	void verlet_solver(){
		for (int i = 0; i < objs.size(); i++){
			if(objs[i].fixed == false){
				double vel_x = (objs[i].x_pos - objs[i].x_pos_last) * 0.998; // drag
				double vel_y = (objs[i].y_pos - objs[i].y_pos_last) * 0.998;
				
				objs[i].x_pos_last = objs[i].x_pos;
				objs[i].y_pos_last = objs[i].y_pos;


				objs[i].x_pos += vel_x;
				objs[i].y_pos += vel_y;

				objs[i].y_pos += objs[i].gravity;
			} else {
				objs[i].x_pos_last = objs[i].x_pos;
				objs[i].y_pos_last = objs[i].y_pos;
			}
    	}
	}

	// Constraint keeps objects on screen in a circle centered on screen with given radius
	void circle_constraint_solver(){
		for (int i = 0; i < objs.size(); i++){
			// constraint center = (screen width / 2, screen height / 2)
			// constraint radius = 400;
			const double a = (objs[i].x_pos - (window_width / 2));
			const double b = (objs[i].y_pos - (window_height / 2));
			// distance from the object to the center of the screen
			const double R = sqrt((a * a) + (b * b));
			// if object is too far adjust the position
			if (R > (400 - objs[i].radius)){
				objs[i].x_pos = ((400 / R) * a) + (window_width / 2);
				objs[i].y_pos = ((400 / R) * b) + (window_height / 2);
			}
    	}
	}

	// Constraint keeps objects on the screen
	void screen_constraint_solver(){
		for (int i = 0; i < objs.size(); i++){
			double vel_x = (objs[i].x_pos - objs[i].x_pos_last);
			double vel_y = (objs[i].y_pos - objs[i].y_pos_last);
			
			if(objs[i].x_pos + (objs[i].radius * 2) > window_width){
				objs[i].x_pos = window_width - 2 * objs[i].radius;
				objs[i].x_pos_last = objs[i].x_pos + vel_x * 0.2;
			}
			else if(objs[i].x_pos < 0){
				objs[i].x_pos = 0;
				objs[i].x_pos_last = objs[i].x_pos + vel_x * 0.2;
			}
			else if (objs[i].y_pos + (objs[i].radius * 2) > window_height)
			{
				objs[i].y_pos = window_height - 2 * objs[i].radius;
				objs[i].y_pos_last = objs[i].y_pos + vel_y * 0.2;
			}
			else if (objs[i].y_pos < 0){
				objs[i].y_pos = 0;
				objs[i].y_pos_last = objs[i].y_pos + vel_y * 0.2;
			}
    	}
	}


	void collision_solver(){
		for (int i = 0; i < objs.size(); i++){
			for (int j = 0; j < objs.size(); ++j)
			{
				if(i != j){
					const double a = objs[j].x_pos - objs[i].x_pos;
					const double b = objs[j].y_pos - objs[i].y_pos;

					const double R = sqrt((a * a) + (b * b));

					if(R - (objs[i].radius * 2) < 0){
						// cout << "collisiosn" << endl;
						// objs[j].x_pos += (a / 2);
						// objs[i].x_pos += (a / 2);
						objs[j].x_pos_last = (objs[i].x_pos + a);
						objs[i].x_pos_last = objs[j].x_pos + a;

						// objs[j].y_pos += (b / 2);
						// objs[i].y_pos += (b / 2);
						objs[j].y_pos_last = objs[i].y_pos + b;
						objs[i].y_pos_last = objs[j].y_pos + b;

					}
				}
			}
    	}
	}

	void sticks_solver(){
		for (int i = 0; i < stks.size(); i++){
			const double a = objs[stks[i].obj1].x_pos - objs[stks[i].obj2].x_pos;
			const double b = objs[stks[i].obj1].y_pos - objs[stks[i].obj2].y_pos;

			const double R = sqrt((a * a) + (b * b));

			const double diff = stks[i].length - R;
			const double percent = diff / R / 2;

			if(objs[stks[i].obj2].fixed == false){
				objs[stks[i].obj2].x_pos -= a * percent;
				objs[stks[i].obj2].y_pos -= b * percent;
			}
			if(objs[stks[i].obj1].fixed == false){
				objs[stks[i].obj1].x_pos += a * percent;
				objs[stks[i].obj1].y_pos += b * percent;
			}
    	}
	}

private:
	vector<Physics2D>& objs;
	vector<Sticks2D>& stks;
};

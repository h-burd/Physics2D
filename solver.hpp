#pragma once

#include <cmath>
#include <iostream>

const int32_t window_width  = 1000;
const int32_t window_height = 1000;

class Solver
{
public:
	Solver(float bounce_value){
		bounce = bounce_value;
	};

	void verlet_solver(vector<Physics2D>& vect){
		for (int i = 0; i < vect.size(); i++){
			if(vect[i].fixed == false){
				double vel_x = (vect[i].x_pos - vect[i].x_pos_last) * 0.998; // drag
				double vel_y = (vect[i].y_pos - vect[i].y_pos_last) * 0.998;
				
				vect[i].x_pos_last = vect[i].x_pos;
				vect[i].y_pos_last = vect[i].y_pos;


				vect[i].x_pos += vel_x;
				vect[i].y_pos += vel_y;

				vect[i].y_pos += vect[i].gravity;
			}
			
    	}
		
		
	}

	// Constraint keeps objects on screen in a circle centered on screen with given radius
	void circle_constraint_solver(vector<Physics2D>& vect){
		for (int i = 0; i < vect.size(); i++){
			// constraint center = (screen width / 2, screen height / 2)
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

	// Constraint keeps objects on the screen
	void screen_constraint_solver(vector<Physics2D>& vect){
		for (int i = 0; i < vect.size(); i++){
			double vel_x = (vect[i].x_pos - vect[i].x_pos_last);
			double vel_y = (vect[i].y_pos - vect[i].y_pos_last);
			
			if(vect[i].x_pos + (vect[i].radius * 2) > window_width){
				vect[i].x_pos = window_width - 2 * vect[i].radius;
				vect[i].x_pos_last = vect[i].x_pos + vel_x * bounce;
			}
			else if(vect[i].x_pos < 0){
				vect[i].x_pos = 0;
				vect[i].x_pos_last = vect[i].x_pos + vel_x * bounce;
			}
			else if (vect[i].y_pos + (vect[i].radius * 2) > window_height)
			{
				vect[i].y_pos = window_height - 2 * vect[i].radius;
				vect[i].y_pos_last = vect[i].y_pos + vel_y * bounce;
			}
			else if (vect[i].y_pos < 0){
				vect[i].y_pos = 0;
				vect[i].y_pos_last = vect[i].y_pos + vel_y * bounce;
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

					if(R - (vect[i].radius * 2) < 0){
						// cout << "collisiosn" << endl;
						// vect[j].x_pos += (a / 2);
						// vect[i].x_pos += (a / 2);
						vect[j].x_pos_last = (vect[i].x_pos + a);
						vect[i].x_pos_last = vect[j].x_pos + a;

						// vect[j].y_pos += (b / 2);
						// vect[i].y_pos += (b / 2);
						vect[j].y_pos_last = vect[i].y_pos + b;
						vect[i].y_pos_last = vect[j].y_pos + b;

					}
				}
			}
    	}
	}

	void sticks_solver(vector<Sticks2D>& stk, vector<Physics2D>& objs){
		for (int i = 0; i < stk.size(); i++){
			const double a = objs[stk[i].obj1].x_pos - objs[stk[i].obj2].x_pos;
			const double b = objs[stk[i].obj1].y_pos - objs[stk[i].obj2].y_pos;

			const double R = sqrt((a * a) + (b * b));

			const double diff = stk[i].length - R;
			const double percent = diff / R / 2;

			if(objs[stk[i].obj2].fixed == false){
				objs[stk[i].obj2].x_pos -= a * percent;
				objs[stk[i].obj2].y_pos -= b * percent;
			}
			if(objs[stk[i].obj1].fixed == false){
				objs[stk[i].obj1].x_pos += a * percent;
				objs[stk[i].obj1].y_pos += b * percent;
			}
    	}
	}

private:
	float bounce;

};

#pragma once


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

	
};

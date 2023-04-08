#pragma once
#include <vector>


class SpringPhysics1D
{
// y'' + c/m y' + k/m y = F(external) = 0
// m = mass
// k = spring constant
// c = damping force
// c^2 > 4km --> underdamped
private:
    double x; // position of mass
    double v; // velocity of mass
    
    double m; // mass on spring
    double k; // spring constant
    double c; // damping force

    double t; // time
    double h; // time step

    double vn; // temp value for v
    double xn;

public:

    SpringPhysics1D(){
        x = -2.0; // position of mass
        v = 0.0; // velocity of mass
    
        m = 0.5; // mass on spring
        k = 3.0; // spring constant
        c = 0.1; // damping force
        
        t = 0.0; // time
        h = 0.025; // time step
    }

    SpringPhysics1D(double mass, double springConstant, double dampingForce){
        m = mass;
        k = springConstant;
        c = dampingForce;

        v = 0.0; // velocity of mass
        t = 0.0; // time
        h = 0.025; // time step
    }


    void eulers_method(){
        // cout << "t: " << t << " x: " << x << " v: " << v << endl;
        xn = x + (h * v);
        vn = v + (h * ((-k/m) * x) + ((-c/m) * v));
        v = vn;
        x = xn;
        t += h;
    }

    void update(){

    }

};
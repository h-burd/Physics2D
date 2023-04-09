#pragma once


class Physics2D
{
public:
    double x_pos;
    double y_pos;

    double x_vel;
    double y_vel;

    double x_acc;
    double y_acc;

    double radius;


    Physics2D(){
        x_pos = 20;
        y_pos = 100;
        x_vel = 2;
        y_vel = 0;
        x_acc = 0;
        y_acc = 30;
        radius = 30;
    }
    
    Physics2D(double xpos, double ypos){
        x_pos = xpos;
        y_pos = ypos;
        x_vel = 0;
        y_vel = 0;
        x_acc = 0;
        y_acc = 30;
        // y_acc = 1000;
        radius = 30;
    }
};



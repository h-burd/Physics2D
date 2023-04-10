#pragma once


class Physics2D
{
public:
    double x_pos;
    double y_pos;

    double x_pos_last;
    double y_pos_last;

    double radius;


    Physics2D(){
        x_pos = 20;
        y_pos = 100;
        x_pos_last = 20;
        y_pos_last = 100;
        radius = 30;
    }
    
    Physics2D(double xpos, double ypos){
        x_pos = xpos;
        y_pos = ypos;
        x_pos_last = xpos;
        y_pos_last = ypos;
        radius = 30;
    }
};



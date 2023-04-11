#pragma once

#include <iostream>
using namespace std;

class Physics2D
{
public:
    double x_pos;
    double y_pos;

    double x_pos_last;
    double y_pos_last;

    double radius;
    double gravity;
    bool fixed;


    Physics2D(){
        x_pos = 20;
        y_pos = 100;
        x_pos_last = 20;
        y_pos_last = 100;
        radius = 30;
    }
    
    Physics2D(double xpos, double ypos, double grav){
        x_pos = xpos;
        y_pos = ypos;
        x_pos_last = xpos;
        y_pos_last = ypos;
        radius = 15;
        gravity = grav;
        fixed = false;
    }

    void set_position(double x, double y){
        x_pos = x;
        y_pos = y;
        // cout << "here" << endl;
    }
};

class Sticks2D
{
public:
    double length;
    // Physics2D obj1;
    // Physics2D obj2;
    int obj1; //index of object 1
    int obj2; //index of object 1


    // Sticks2D(double len, Physics2D& o1, Physics2D& o2){
    //     length = len;
    //     obj1 = o1;
    //     obj2 = o2;
    //     // cout << obj1.x_pos << "  " << obj2.x_pos << "  " << length << endl;
    // }
    
    Sticks2D(double len, int o1, int o2){
        length = len;
        obj1 = o1;
        obj2 = o2;
        // cout << obj1.x_pos << "  " << obj2.x_pos << "  " << length << endl;
    }
};

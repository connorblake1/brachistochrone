//
//  Plotter.hpp
//  TrafficSimulator
//
//  Created by Connor Blake on 7/17/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#ifndef Plotter_hpp
#define Plotter_hpp
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
class Plotter {
private:
    float map(float in, float l1, float u1, float l2, float u2);
    float * plotter;
    std::string name, xaxis, yaxis;
    bool autoscale, datastream;
    int x,y,w,h, plots, vals;
    float * bounds;
public:
    Plotter(std::string name, std::string xaxis, std::string yaxis, bool scaling, bool datastream, int plots, int vals, int x, int y, int w, int h) {
        this->name = name;
        this->xaxis=xaxis;
        this->yaxis=yaxis;
        this->autoscale = scaling;
        this->datastream = datastream;
        plotter = new float[plots*vals];
        this->plots=plots;
        this->vals=vals;
        this->x=x;
        this->y=y;
        this->w=w;
        this->h=h;
        bounds = new float[2];
    }//done
    void importData(float * data);//done
    void updateFilled();//done
    void updateBounds(int p);//done
    void updateBounds();//done
    void setBounds(float l, float u);//done
    void showPlot(sf::RenderWindow * wind);//done
    void pushData(float * dataIn);//done
    void reset();
};
#endif /* Plotter_hpp */

//
//  Polynomial.cpp
//  RampCurves
//
//  Created by Connor Blake on 9/27/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//
#include <iostream>
#include <math.h>
#include "Polynomial.hpp"
void Polynomial::init(int deg, float x0in, float y0in, float * incoeffs, int w, int h, bool split) {
    this->degree = deg;
    if (split) {this->setCoeffsSplit(incoeffs);}
    else {
        this->setCoeffs(incoeffs);
        this->kscale=1;
    }
    this->x0 = x0in;
    this->y0 = y0in;
    this->w = w;
    this->h = h;
    //printout();
}
void Polynomial::graph(sf::RenderWindow * win, int y1, int y2, int nin, sf::Color col) {

    sf::Vertex line1[] = { sf::Vertex(sf::Vector2f(.05*w,0),sf::Color::White), sf::Vertex(sf::Vector2f(.05*w,h),sf::Color::White)};
    sf::Vertex line2[] = { sf::Vertex(sf::Vector2f(0,map(0,y1,y2,.95*h, .05*h)),sf::Color::White), sf::Vertex(sf::Vector2f(w,map(0,y1,y2,.95*h, .05*h)),sf::Color::White)};
    (*win).draw(line1, 2, sf::Lines);
    (*win).draw(line2, 2, sf::Lines);
    sf::VertexArray graph(sf::Points, nin);
    sf::CircleShape c1;
    c1.setRadius(10);
    
    c1.setFillColor(sf::Color::Green);
    c1.setPosition(.05*w,map(y0,y1,y2,.95*h, .05*h));
    win->draw(c1);
    sf::CircleShape c2;
    c2.setRadius(10);
    c2.setFillColor(sf::Color::Green);
    c2.setPosition(.95*w,map(0,y1,y2,.95*h, .05*h));
    win->draw(c2);
    for (int n = 0; n < nin; n++) {
        graph[n].color = col;
        float xmap = (float)(n)/nin*x0;
        graph[n].position = sf::Vector2f( map(xmap,0.0,x0,.05*w,.95*w), map(evaluate(xmap), y1, y2, .95*h, .05*h) );}
        (*win).draw(graph);}

sf::Vector2f * Polynomial::mapCoords(float fx, float y1, float y2) {
    sf::Vector2f * out = new sf::Vector2f(map(fx,0.0,x0,.05*w,.95*w), map(evaluate(fx), y1, y2, .95*h, .05*h));
    return out;
}
void Polynomial::init(int deg) {
    this->degree = deg;
    coeffs = new float[degree+1];
}
void Polynomial::setCoeffs(float * incoeffs) {
    //coeffs = new float[degree+1];
    this->coeffs = incoeffs;
}
void Polynomial::setCoeffsSplit(float * incoeffs) {
//    for (int i = 0; i < degree-1; i++) {
//        std::cout<<"incoeff " << i << "  " << incoeffs[i] << std::endl;
//    }
    coeffs = new float[degree+1];
    this->kscale = -1.0*y0/x0/incoeffs[0];
    //std::cout << kscale <<  " " << degree << std::endl;
    for (int i = degree; i >= 0; i--) {
        if (i == degree) {
            coeffs[degree] = kscale;}
        else if (i == 0) {
            coeffs[i] = y0;
        }
        else if (degree-1 == i) {
            coeffs[i] =kscale*(incoeffs[i-1]-x0);
        }
        else {
            coeffs[i] = kscale*(incoeffs[i-1]-x0*incoeffs[i]);}}
}
float Polynomial::evaluate(float x) {
    float r = 0;
    for (int i = 0; i <= degree; i++) {
        r += coeffs[i]*pow(x, i);}
    return r;
}
Polynomial * Polynomial::derivative() {
    Polynomial * p1 = new Polynomial();
    float * newcoeffs = new float[degree];
    for (int i = 0; i < degree; i++) {
        newcoeffs[i] = coeffs[i+1]*(i+1);
    }
    p1->init(degree-1, x0, y0, newcoeffs, w, h, false);
    return p1;
}

float Polynomial::map(float in, float l1, float u1, float l2, float u2) {
    float r = (in-l1)/(u1-l1)*(u2-l2)+l2;
    //map(plotter[vals*p+v]/(bounds[p*2+1]-bounds[p*2]), 0.0,1.0,y+.05*h,y+.95*h)
    return r;}

void Polynomial::printout() {
    for (int i = degree; i >= 0; i--) {
        std::cout << coeffs[i] << "x^" << i << " + " ;}
    std::cout << std::endl;
}

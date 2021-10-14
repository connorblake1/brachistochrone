//
//  Plotter.cpp
//  TrafficSimulator
//
//  Created by Connor Blake on 7/17/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#include "Plotter.hpp"

void Plotter::showPlot(sf::RenderWindow *wind) {
    //background
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(w,h));
    background.setFillColor(sf::Color::Black);
    background.setPosition(x,y);
    (*wind).draw(background);
    //axes
//    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(map(.05,0.0,1.0,x,x+w), map(0.0,0.0,1.0,y,y+h)),sf::Color::White), sf::Vertex(sf::Vector2f(map(.05,0.0,1.0,x,x+w), map(1.0,0.0,1.0,y,y+h)),sf::Color::White)};
//    (*wind).draw(line, 2, sf::Lines);
//    sf::Vertex line1[] = { sf::Vertex(sf::Vector2f(map(0.0,0.0,1.0,x,x+w), map(.95,0.0,1.0,y,y+h)),sf::Color::White), sf::Vertex(sf::Vector2f(map(1.0,0.0,1.0,x,x+w), map(.95,0.0,1.0,y,y+h)),sf::Color::White)};
//    (*wind).draw(line1, 2, sf::Lines);
    //labels
    sf::Font font;
    font.loadFromFile("/Users/connorblake/Documents/SORTOld/RampCurves/RampCurves/arial.ttf");
    sf::Text title(name, font, w/20);
    title.setFillColor(sf::Color::White);
    sf::FloatRect textRect1 = title.getLocalBounds();
    title.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
    title.setPosition(map(.5,0.0,1.0,x,x+w), map(.05,0.0,1.0,y,y+h));
    (*wind).draw(title);
    sf::Text xax(xaxis, font, w/20);
    xax.setFillColor(sf::Color::White);
    sf::FloatRect textRect2 = xax.getLocalBounds();
    xax.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
    xax.setPosition(map(.5,0.0,1.0,x,x+w), map(.95,0.0,1.0,y,y+h));
    (*wind).draw(xax);
//    sf::Text yax(xaxis, font, w/20);
//    yax.setFillColor(sf::Color::White);
//    sf::FloatRect textRect3 = yax.getLocalBounds();
//    yax.setOrigin(textRect3.left + textRect3.width/2.0f, textRect3.top  + textRect3.height/2.0f);
//    yax.setPosition(map(.5,0.0,1.0,x,x+w), map(.975,0.0,1.0,y,y+h));
//    (*wind).draw(yax);
    //data
    sf::Color colors[] = {sf::Color::Red,sf::Color::Blue,sf::Color::Green,sf::Color::Yellow,sf::Color::Magenta,sf::Color::Cyan,sf::Color::Red,sf::Color::Blue,sf::Color::Green,sf::Color::Yellow,sf::Color::Magenta,sf::Color::Cyan,sf::Color::Red,sf::Color::Blue,sf::Color::Green,sf::Color::Yellow,sf::Color::Magenta,sf::Color::Cyan};
    sf::VertexArray graph(sf::Points, vals);
    for (int v = 0; v < vals; v++) {
        graph[v].color = sf::Color::White;
        graph[v].position = sf::Vector2f(map(plotter[v],bounds[0],bounds[1],x,x+w),map(plotter[vals+v], bounds[0],bounds[1],y+h,y));
    }
    wind->draw(graph);
//    for (int p = 0; p < plots; p++) {
//        sf::VertexArray graph(sf::Points, vals);
//        for (int v = 0; v < vals; v++) {
//            graph[v].color = colors[p];
//            graph[v].position = sf::Vector2f(map((float)(v)/vals,0.0,1.0,x+w*.95,x+w*.05),map(plotter[vals*p+v]/(bounds[1]-bounds[0]), 0.0,1.0,y+.95*h,y+.05*h));}
//        (*wind).draw(graph);}
    //TODO: markings
}
float Plotter::map(float in, float l1, float u1, float l2, float u2) {
    float r = (in-l1)/(u1-l1)*(u2-l2)+l2;
    //map(plotter[vals*p+v]/(bounds[p*2+1]-bounds[p*2]), 0.0,1.0,y+.05*h,y+.95*h)
    return r;}
void Plotter::setBounds(float l, float u) {
    if (autoscale) {return;}
    bounds[0] = l;
    bounds[1] = u;}
void Plotter::updateBounds(int p) {
    if (autoscale) {return;}
    float l = 10000000;
    float u = -10000000;
    for (int v = 0; v < vals; v++) {
        float val =plotter[p*vals + v];
        if (val < l) {
            l = val;}
        if (v > u) {
            u = val;}}
    bounds[p*2+0] = l;
    bounds[p*2+1] = u;}
void Plotter::updateBounds() {
    if (autoscale) {return;}
    for (int p = 0; p < plots; p++) {
        float l = 10000000;
        float u = -10000000;
        for (int v = 0; v < vals; v++) {
            float val =plotter[p*vals + v];
            if (val < l) {
                l = val;}
            if (v > u) {
                u = val;}}
        bounds[p*2+0] = l;
        bounds[p*2+1] = u;}}
void Plotter::pushData(float * dataIn) {
    for (int p = 0; p < plots; p++) {
        for (int v = vals-1; v > 0; v--)  {
            plotter[p*vals+v] = plotter[p*vals+v-1];}
        plotter[p*vals] = dataIn[p];}
}
void Plotter::importData(float * data) {
    plotter = data;}
void Plotter::reset() {
    plotter = new float[plots*vals];}


//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Polynomial.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Plotter.hpp"
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
float getTimeForCurve(Polynomial * p, float sy, float ex) {
    int d = p->getDeg();
    float * c1 = new float[d+1];
    Polynomial * p1 = p->derivative();
    float fy = sy-.01;
    float fx = 0;
    float t = 0;
    float dt = .002;
    while (p->getDXDT(fx, fy, p1) > 0 && fy > -10) {
        fx += p->getDXDT(fx,fy, p1)*dt;
        fy = p->evaluate(fx);
        t+=dt;
        if (fx > ex) {
            return t;
        }}
    return 10000;}

float map(float in, float l1, float u1, float l2, float u2) {
    float r = (in-l1)/(u1-l1)*(u2-l2)+l2;
    //map(plotter[vals*p+v]/(bounds[p*2+1]-bounds[p*2]), 0.0,1.0,y+.05*h,y+.95*h)
    return r;}
float getTimeForCurve(Polynomial * p, float sy, float ex, sf::RenderWindow * win, sf::Text* texter1, sf::Text * texter2, sf::Text * texter3) {
    int d = p->getDeg();
    float * c1 = new float[d+1];
    Polynomial * p1 = p->derivative();
    float fy = sy-.01;
    float fx = 0;
    float t = 0;
    float dt = .002;
    win->clear();
    sf::RectangleShape blob(sf::Vector2f(10.0,10.0));
    while (p->getDXDT(fx, fy, p1) > 0 && fy > -10) {
        win->clear();
        sf::Vector2f * pos = p->mapCoords(fx,-5.0,5.0);
        blob.setPosition(*pos);
        win->draw(blob);
        win->draw(*texter1);
        win->draw(*texter2);
        win->draw(*texter3);
        p->graph(win, -5, 5, 500, sf::Color::Green);
        win->display();
        fx += p->getDXDT(fx,fy, p1)*dt;
        fy = p->evaluate(fx);
        t+=dt;
        if (fx > ex) {
            return t;
        }}
    return 10000;}

int main(int, char const**)
{
    float bounder = 500.0;
    
    bool breaker1 = false;
    bool breaker2 = false;
    
    srand(time(NULL));
    int dims = 4;
    int cycle = 0;

    float ex = 10;
    float sy = 5;
    
    float * c1 = new float[dims+1];
    Polynomial * p = new Polynomial();
    p->init(dims+1, ex, sy, c1, 1000, 1000, true);
    
    Polynomial * holder = new Polynomial();
    holder->init(dims+1, ex, sy, c1, 1000, 1000, true);
    float tmin = 1000;
    float told = 10000;
    float t = 1000;
    float lalign = 50;
    float ualign = 800;
    sf::Font fontMain;
    fontMain.loadFromFile("/Users/connorblake/Documents/SORTOld/RampCurves/RampCurves/arial.ttf");
    sf::Text title(" ",fontMain,50);
    title.setFillColor(sf::Color::White);
    title.setPosition(lalign, ualign-50);
    
    sf::Text time1(" ", fontMain, 50);
    time1.setFillColor(sf::Color::Yellow);
    time1.setPosition(lalign, ualign+70);
    
    sf::Text time2(" ",fontMain,50);
    time2.setFillColor(sf::Color::Red);
    time2.setPosition(lalign,ualign);
    
    sf::Text poly1(" ", fontMain,30);
    poly1.setFillColor(sf::Color::Yellow);
    poly1.setPosition(lalign,ualign+120);
    
    sf::Text poly2(" ", fontMain,30);
    poly2.setFillColor(sf::Color::Red);
    poly2.setPosition(lalign,ualign+50);
    
    Plotter grapher("","","", false,true,2,10000,300,150,200,200);
    grapher.setBounds(-bounder, bounder);
    
    
    float * coords = new float[dims];
    for (int i = 0; i < dims; i++){
        coords[i] = -1.0;}
    
    unsigned long tick1 = 0;
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();}
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();}
                else if (event.key.code == sf::Keyboard::R) {
                    breaker1 = true;
                }
                else if (event.key.code == sf::Keyboard::E) {
                    breaker2= true;
                }
            }}
        window.clear();
        

        float * holdcoords = new float[dims];
        float * holdtimes = new float[dims];
        //get times for each orthogonal direction
        for (int i = 0; i < dims; i++) {
            for (int j = 0; j < dims; j++) {
                holdcoords[j] = coords[j];}
            holdcoords[i] = coords[i] + .003;
//            std::cout << "i " << i << std::endl;
//            for (int j = 0; j < dims; j++) {
//                std::cout<< "    j " << holdcoords[j] << std::endl;
//            }
            p->setCoeffsSplit(holdcoords);
            holdtimes[i] = getTimeForCurve(p, sy, ex);}
//            p->printout();
//            std::cout << "baselines " << p->evaluate(0) << "   " << p->evaluate(ex) << std::endl;
//            Polynomial * p1 = p->derivative();
//            std::cout << "derivative " << std::endl;
//            p1->printout();


        //normalize times
        float d = 0;
        float * difftimes = new float[dims];
        for (int i = 0; i < dims; i++) {
            //std::cout << "h time " << holdtimes[i] << std::endl;
            difftimes[i] = holdtimes[i]-told;
            d += difftimes[i]*difftimes[i];}
        d = sqrt(d);
        //std::cout << "d " << d << std::endl;
        if (d < .01) {
            for (int i = 0; i < dims; i++){
                coords[i] = (float)(rand())/RAND_MAX*2*bounder-bounder;}
            continue;}
        for (int i = 0; i < dims; i++) {
            difftimes[i]/=d;}
        //step in new direction
        for (int i = 0; i < dims; i++) {
            coords[i] -= difftimes[i]*.005;}
        p->setCoeffsSplit(coords);
        t = getTimeForCurve(p, sy, ex);
        
//
//        std::stringstream stream1;
//        stream1 << "Current time: " << std::fixed << std::setprecision(4) << t;
//        time1.setString(stream1.str());
//        window.draw(time1);
        
        std::stringstream stream2;
        stream2 << "Best time: " << std::fixed << std::setprecision(4) << tmin;
        time2.setString(stream2.str());
        window.draw(time2);
        
//        std::stringstream stream3;
//        stream3 << "Current Polynomial: ";
//        for (int i = p->getDeg(); i >=0;i--) {
//            stream3 << std::fixed << std::setprecision(3) << p->getCoeffs()[i];
//            if (i == 1) {
//                stream3 << "x + ";}
//            if (i > 1) {
//                stream3 << "x^" << i << " + ";}}
//        poly1.setString(stream3.str());
//        window.draw(poly1);
        
        std::stringstream stream4;
        stream4 << "Best Polynomial: ";
        for (int i = holder->getDeg(); i >=0;i--) {
            stream4 << std::fixed << std::setprecision(3) << holder->getCoeffs()[i];
            if (i == 1) {
                stream4 << "x + ";}
            if (i > 1) {
                stream4 << "x^" << i << " + ";}}
        poly2.setString(stream4.str());
        window.draw(poly2);
        
        std::stringstream stream5;
        stream5 << "Degree: " << p->getDeg();
        title.setString(stream5.str());
        window.draw(title);
//        grapher.pushData(coords);
//        grapher.showPlot(&window);
//
        holder->graph(&window,-5,5,500,sf::Color::Red);
        //p->graph(&window, -5, 5, 500,sf::Color::Yellow);
        
        if (t < tmin) {
            tmin = t;
            for (int i = 0; i < dims+2; i++){
                holder->getCoeffs()[i] = p->getCoeffs()[i];};
            //std::cout << "New Low: " << t << std::endl;
            //holder->printout();
            //t = getTimeForCurve(holder, sy, ex,&window,&time2);
        }
        told = t;
        cycle++;

        
        
//        for (int i = 0; i < dims; i++){
//            if (i == 0) {
//                c1[0] = -5.0+(tick1%50)*.2;}
//            else {
//                c1[i] = -5.0+(tick1/pow(50,i))*.2;}}
//
//        p->setCoeffsSplit(c1);
        

        
//        else {
//            for (int i = 0; i < dims+1; i++){
//                std::cout << "coeff " << i << ": " << xlows[i] << std::endl;;}
//            for (int i = 0; i < dims; i++){
//                holdcoords[i] = (float)(rand())/RAND_MAX*10.0-5.0;}
//            p->setCoeffsSplit(holdcoords);
//        }
//        if (tick1 > pow(50,dims)) {
//            for (int i = 0; i < dims+1; i++){
//                std::cout << "coeff " << i << ": " << xlows[i] << std::endl;;}
//            exit(-1);}
        
        //tick1++;

        window.display();
        if (breaker1) {
            float a = getTimeForCurve(holder, sy, ex,&window, &time2, &poly2, &title);
            breaker1 = false;
        }
        else if (breaker2) {
            float a = getTimeForCurve(p, sy, ex,&window, &time1, &poly1, &title);
            breaker2 = false;
        }
            
            }

    return EXIT_SUCCESS;
}

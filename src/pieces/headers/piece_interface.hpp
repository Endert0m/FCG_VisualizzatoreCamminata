#include <SFML/Graphics.hpp>
#include <math.h>
#include "../../rigidbody/headers/rb.hpp"


#ifndef PIECE_INTERFACE_H
#define PIECE_INTERFACE_H


enum class ReferencePlane {
    XY,
    YZ,
    XZ
};

//classi
class PieceInterface{
    protected:
        
        //std::vector<JointInterface*> joints;

    public:
        sf::Shape* shape;
        sf::Vector2f size;
        rb::Vector3 globalPos;
        rb::rigidbody body;
        sf::Color color;

        virtual void update(sf::Clock cl) = 0;
        virtual sf::Shape* draw(ReferencePlane plane) = 0;
        virtual ~PieceInterface(){}
};


#endif
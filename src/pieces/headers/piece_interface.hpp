#include <SFML/Graphics.hpp>
#include <math.h>
#include "../../rigidbody/headers/rb.hpp"


#ifndef PIECE_INTERFACE_H
#define PIECE_INTERFACE_H


enum class ReferencePlane {
    XZ,
    YZ,
    XZN
};

enum class Direction {
    L,
    R
};

//classi
class PieceInterface{
    protected:
        
        void initialize_shapes(sf::Vector3f dim){
            shapeXZ = new sf::RectangleShape({dim.x, dim.y});
            shapeYZ = new sf::RectangleShape({dim.z, dim.y});
            shapeXZ->setOrigin({dim.x/2,dim.y/2});
            shapeYZ->setOrigin({dim.z/2,dim.y/2});
            shapeXZ->setFillColor(color);
            shapeYZ->setFillColor(color);
        }
        Direction direction = Direction::L;
    public:
        sf::Shape* shapeXZ, *shapeYZ;
        rb::Vector3 globalPos;
        rb::rigidbody body;
        sf::Color color;
        float transparency = 1.0; //canale alpha del pezzo

        virtual void update(sf::Clock cl) = 0;
        virtual sf::Shape* draw(ReferencePlane plane) = 0;
        virtual ~PieceInterface(){}
        virtual void setDirection(Direction dir){
            direction = dir;
        }
        virtual bool setTransparency(float alpha){
            if (alpha < 0 || alpha > 1) return false;
            transparency = alpha; 
        }
};


#endif
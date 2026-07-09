#include <SFML/Graphics.hpp>
#include <math.h>
#include "../../rigidbody/headers/rb.hpp"

#define TEXTUREPATH std::string("./../../textures/")

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

        sf::Texture TextureF ;
        sf::Texture TextureL ;

        void setTextures (std::string F, std::string L){
            try{
                TextureF = sf::Texture(TEXTUREPATH + F);
                TextureL = sf::Texture(TEXTUREPATH + L);

                shapeXZ->setTexture(&TextureL);
                shapeYZ->setTexture(&TextureF);
            }catch(...){
                throw "Errore nel caricamento texture.";
            }
        }

    public:
        sf::Shape* shapeXZ, *shapeYZ;
        rb::Vector3 globalPos;
        rb::rigidbody body;
        sf::Color color;
        float multColor[3] = {1,1,1};
        float transparency = 1.0; //canale alpha del pezzo

        virtual void update(sf::Clock cl, float multiplier) = 0;
        virtual sf::Shape* draw(ReferencePlane plane) = 0;
        virtual ~PieceInterface(){}
        virtual void setDirection(Direction dir){
            direction = dir;
        }
        virtual bool setTransparency(float alpha){
            if (alpha < 0 || alpha > 1) return false;
            transparency = alpha; 
            return true;
        }
        virtual void setColor(float* col) {
            multColor[0] = col[0];
            multColor[1] = col[1];
            multColor[2] = col[2];
        }
};


#endif
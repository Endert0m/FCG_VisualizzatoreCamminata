#include "piece_interface.hpp"

#ifndef COSCIA_H
#define COSCIA_H



class Coscia : public PieceInterface{
    private:
        const sf::Vector3f coscia_Dim = {80, 200, 80};
        const sf::Color coscia_Col = sf::Color::Yellow;
        const sf::Texture TextureF = sf::Texture(TEXTUREPATH + "cosciaF.png");
        const sf::Texture TextureL = sf::Texture(TEXTUREPATH + "cosciaL.png");

    public: 

        Coscia(rb::Vector3 coords, _Float16 mass);
        ~Coscia();

        void update(sf::Clock cl, float multiplier) override;
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
#include "piece_interface.hpp"

#ifndef CAVIGLIA_H
#define CAVIGLIA_H


class Caviglia : public PieceInterface{
    private:
        const sf::Vector3f caviglia_Dim = {60, 200, 60};
        const sf::Color caviglia_Col = sf::Color(230,160,11,255);
        const sf::Texture TextureF = sf::Texture(TEXTUREPATH + "cavigliaF.png");
        const sf::Texture TextureL = sf::Texture(TEXTUREPATH + "cavigliaL.png");

    public: 

        Caviglia(rb::Vector3 coords, _Float16 mass);
        ~Caviglia();

        void update(sf::Clock cl, float multiplier) override;
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
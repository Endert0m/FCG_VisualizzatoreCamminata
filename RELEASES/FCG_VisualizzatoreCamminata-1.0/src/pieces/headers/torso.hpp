#include "piece_interface.hpp"

#ifndef TORSO_H
#define TORSO_H


class Torso : public PieceInterface{
    private:
        const sf::Vector3f torso_Dim = {100, 100, 150};
        const sf::Color torso_Col = sf::Color::Red;
        
        const std::string TEXTURE_F = std::string("bacinoF.png");
        const std::string TEXTURE_L = std::string("bacinoL.png");

    public:
        Torso(rb::Vector3 coords, _Float16 mass);
        ~Torso();

        void update(sf::Clock cl, float multiplier) override;
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
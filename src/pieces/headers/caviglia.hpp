#include "piece_interface.hpp"

#ifndef CAVIGLIA_H
#define CAVIGLIA_H

const sf::Vector2f caviglia_Dim = {60, 200};
const sf::Color caviglia_Col = sf::Color(230,160,11,255);


class Caviglia : public PieceInterface{
    public: 

        Caviglia(rb::Vector3 coords, _Float16 mass);
        ~Caviglia();

        void update(sf::Clock cl) override;
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
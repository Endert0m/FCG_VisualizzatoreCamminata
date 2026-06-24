#include "piece_interface.hpp"

#ifndef COSCIA_H
#define COSCIA_H

const sf::Vector2f coscia_Dim = {80, 200};
const sf::Color coscia_Col = sf::Color::Yellow;


class Coscia : public PieceInterface{
    public: 

        Coscia(rb::Vector3 coords, _Float16 mass);
        ~Coscia();

        void update(sf::Clock cl) override;
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
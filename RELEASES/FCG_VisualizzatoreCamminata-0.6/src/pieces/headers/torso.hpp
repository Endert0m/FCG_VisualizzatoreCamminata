#include "piece_interface.hpp"

#ifndef TORSO_H
#define TORSO_H




class Torso : public PieceInterface{
    private:
        const sf::Vector3f torso_Dim = {100, 100, 250};
        const sf::Color torso_Col = sf::Color::Red;
    public:
        Torso(rb::Vector3 coords, _Float16 mass);
        ~Torso();

        void update(sf::Clock cl) override;
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
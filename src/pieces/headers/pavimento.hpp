#include "piece_interface.hpp"


#ifndef PAVIMENTO_H
#define PAVIMENTO_H

class Pavimento : public PieceInterface{
    private:
        const sf::Vector3f pavimento_Dim = {600, 20, 600};
        const sf::Color pavimento_Col = sf::Color(255,255,255,255);
        
        const std::string TEXTURE_F = std::string("pavimentoF.png");
        const std::string TEXTURE_L = std::string("pavimentoL.png");


    public: 

        Pavimento(rb::Vector3 coords, _Float16 mass);
        ~Pavimento();

        void update(sf::Clock cl, float multiplier) override {};
        sf::Shape* draw(ReferencePlane plane) override;
};

#endif
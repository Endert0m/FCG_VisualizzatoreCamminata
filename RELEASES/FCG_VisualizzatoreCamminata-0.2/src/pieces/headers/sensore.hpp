#include "piece_interface.hpp"

#ifndef SENSORE_H
#define SENSORE_H

const sf::Vector2f sensore_Dim = {30, 60};
const sf::Color sensore_Col = sf::Color::Red;

class Sensore : public PieceInterface{
    private:
        std::vector<std::vector<float>> accData;
        std::vector<std::vector<float>> gData;
        std::vector<std::vector<float>> rotData;
        std::vector<float> timeData;
        rb::Vector3 stPos;

        //in che punto sto controllando il segnale 
        unsigned int dataPos;
        unsigned int dataIntvl; 
        

        //funzioni ausiliarie
        void calcRotWithG(unsigned int index);

    public: 
        Sensore(rb::Vector3 coords, _Float16 mass);
        Sensore(rb::Vector3 coords, _Float16 mass, unsigned int st, unsigned int dataIntvl, std::vector<std::vector<float>> data);
        ~Sensore();

        void update(sf::Clock cl) override;
        sf::Shape* draw(ReferencePlane plane) override;

        //funzioni specifiche
        void initCSV(std::vector<std::vector<float>> data);

};

#endif
#include "piece_interface.hpp"

#ifndef SENSORE_H
#define SENSORE_H



class Sensore : public PieceInterface{
    private:
        const sf::Vector3f sensore_Dim = {30, 60, 30};
        const sf::Color sensore_Col = sf::Color::Red;
        
        std::vector<std::vector<float>> accData;
        std::vector<std::vector<float>> gData;
        std::vector<std::vector<float>> rotData;
        std::vector<float> timeData;
        rb::Vector3 stPos;

        //in che punto sto controllando il segnale 
        unsigned int dataPos;
        std::vector<int> dataIntvl; 
        unsigned int curTime;

        //funzioni ausiliarie
        void calcRotWithG(unsigned int index);
        

    public: 
        Sensore(rb::Vector3 coords, _Float16 mass);
        Sensore(rb::Vector3 coords, _Float16 mass, unsigned int st, int min, int max, std::vector<std::vector<float>> data);
        ~Sensore();

        void update(unsigned int pos) override;
        sf::Shape* draw(ReferencePlane plane) override;

        //funzioni specifiche
        void initCSV(std::vector<std::vector<float>> data);
        void setIntervall(int min, int max);
        void setPos(int &pos);

};

#endif
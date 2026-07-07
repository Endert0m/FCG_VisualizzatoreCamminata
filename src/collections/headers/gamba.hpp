#include "collection_interface.hpp"
#include "include_pieces.hpp"

#ifndef GAMBA_H
#define GAMBA_H

class Gamba : public CollectionInterface {
    protected:
        std::vector<Sensore*> sensori;
        std::vector<PieceInterface*> pezzi;
        std::vector<JointInterface*> joints;

        std::vector<rb::Vector3> calibrazione;

        rb::Vector3 rebound = {0,0,0};

    public:
        Gamba(rb::Vector3 pos, unsigned int* dataPos, std::string cosciaData, std::string cavigliaData);
        Gamba(rb::Vector3 pos, unsigned int* dataPos, std::string cosciaData, std::string cavigliaData, Direction dir);
        collection create(ReferencePlane plane) override;
        PieceInterface* getJointPiece();
        void setDirection(Direction dir);
        void update(sf::Clock cl, float multiplier)override;
        float getZ_Acc();
};

#endif 

#include "collection_interface.hpp"
#include "include_pieces.hpp"

#ifndef GAMBA_H
#define GAMBA_H

class Gamba : public CollectionInterface {
    protected:
        std::vector<PieceInterface*> sensori;
        std::vector<PieceInterface*> pezzi;
        std::vector<JointInterface*> joints;
    public:
        Gamba(rb::Vector3 pos, unsigned int* dataPos, std::string cosciaData, std::string cavigliaData);
        collection create(ReferencePlane plane) override;
        PieceInterface* getJointPiece();
        void setDirection(Direction dir);
        bool setTransparency(float alpha) override;
};

#endif
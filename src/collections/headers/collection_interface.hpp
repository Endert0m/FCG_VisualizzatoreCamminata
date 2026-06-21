#include "../../pieces/headers/piece_interface.hpp"
#include "../../joints/headers/joint_interface.hpp"

#ifndef COLL_INTERFACE_H
#define COLL_INTERFACE_H

struct collection{
    std::vector<PieceInterface*> pieces;
    std::vector<JointInterface*> joints;
};


class CollectionInterface{
    public:
        virtual collection create(ReferencePlane plane) = 0;
        virtual void update(sf::Clock cl) = 0;
        virtual bool setTransparency(float alpha) = 0; 
        virtual ~CollectionInterface(){};
};




inline collection operator+(collection c1, collection c2){
    collection res;
    for (PieceInterface* i : c1.pieces){
        res.pieces.push_back(i);
    }
    for (PieceInterface* i : c2.pieces){
        res.pieces.push_back(i);
    }
    for (JointInterface* i : c1.joints){
        res.joints.push_back(i);
    }
    for (JointInterface* i : c2.joints){
        res.joints.push_back(i);
    }
    
    return res;
}

#endif
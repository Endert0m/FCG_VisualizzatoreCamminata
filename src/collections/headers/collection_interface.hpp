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
        virtual ~CollectionInterface(){};
};


#endif
#include "../../pieces/headers/piece_interface.hpp"

#ifndef JOINT_INTERFACE_H
#define JOINT_INTERFACE_H

/*
1) il joint può essere tra più pezzi
2) esistono 3 tipi di joint:
   - completi / rigidi
   - a pivot / 1 grado di libertà di rotazione
   - spillo / completa libertà di rotazione 
*/



class JointInterface{
    protected: 
        virtual void rotate(unsigned int id) = 0;
        virtual void traslate(unsigned int id) = 0;

    public:
        std::vector<rb::Vector3> offset;
        std::vector<rb::Vector3_s> rotOffset;
        PieceInterface* father;
        std::vector<PieceInterface*> childs;

        virtual ~JointInterface(){};
        virtual void movechild() = 0;

        
};

#endif
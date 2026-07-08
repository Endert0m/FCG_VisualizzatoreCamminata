#include "../../pieces/headers/piece_interface.hpp"
#include "../../joints/headers/joint_interface.hpp"

#ifndef COLL_INTERFACE_H
#define COLL_INTERFACE_H

struct collection{
    std::vector<PieceInterface*> pieces;
    std::vector<JointInterface*> joints;
};


class CollectionInterface{
    protected:
        float transparency = 1.0;
        bool isVisible = true;
    public:
        virtual collection create(ReferencePlane plane) = 0;
        virtual void update(sf::Clock cl, float multiplier) = 0;
        virtual void resetTime() = 0;
        virtual bool setTransparency(float alpha) {
            if (alpha < 0 || alpha > 1) return false;
            transparency = alpha;
            return true;
        }; 
        virtual bool getVisibility(){
            return isVisible;
        }
        virtual float getTransparency() {
            return transparency;
        }

        virtual void setVisibility(bool c) {
            isVisible = c;
        }
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
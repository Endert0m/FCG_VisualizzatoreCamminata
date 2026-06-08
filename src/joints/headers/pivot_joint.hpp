#include "joint_interface.hpp"

#ifndef PIVOTJ_H
#define PIVOTJ_H

class PivotJoint : public JointInterface {
    protected:
        void rotate(unsigned int id) override;
        void traslate(unsigned int id) override;
        void updatePivot();

        rb::Vector3 oldRot;
        std::vector<rb::Vector3> oldCRot;
        rb::Vector3 pivot;
        rb::Vector3 stPivot;
        
        //angolo attuale pivot e offset
        rb::Vector3 pivotAngle;
        std::vector<rb::Vector3> offsetAngle;

        //possono servire per calcolare l'offset rispetto alla posizione precedente
        rb::Vector3 oldPos;
        std::vector<rb::Vector3> oldCPos;
        
    public:
        
        void movechild() override;

        PivotJoint(PieceInterface* father,std::vector<PieceInterface*> childs, rb::Vector3 pivotPoint);
        ~PivotJoint();
};

#endif
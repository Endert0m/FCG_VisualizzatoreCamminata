#include "joint_interface.hpp"

class PivotJoint : public JointInterface {
    protected:
        void rotate(unsigned int id) override;
        void traslate(unsigned int id) override;

        rb::Vector3_s oldRot;
        rb::Vector3 pivot;
        std::vector<rb::Vector3_s> oldCRot;

        //possono servire per calcolare l'offset rispetto alla posizione precedente
        rb::Vector3 oldPos;
        std::vector<rb::Vector3> oldCPos;
        
    public:
        
        void movechild() override;

        PivotJoint(PieceInterface* father,std::vector<PieceInterface*> childs, rb::Vector3 pivotPoint);
        ~PivotJoint();
};
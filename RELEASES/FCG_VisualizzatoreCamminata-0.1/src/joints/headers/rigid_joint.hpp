#include "joint_interface.hpp"


class RigidJoint : public JointInterface {
    protected:
        void rotate(unsigned int id) override;
        void traslate(unsigned int id) override;

        //possono servire per calcolare l'offset rispetto alla posizione precedente
        rb::Vector3 oldPos;
        std::vector<rb::Vector3> oldCPos;
        
    public:
        
        void movechild() override;

        RigidJoint(PieceInterface* father,std::vector<PieceInterface*> childs);
        ~RigidJoint();
};
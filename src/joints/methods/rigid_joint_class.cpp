#include "../headers/rigid_joint.hpp"

#define ZERO_INT 0.00001

//using namespace glm;

void RigidJoint::rotate(unsigned int id){
    rb::Vector3_s fRot = father->body.getRot();
    rb::Vector3_s fRotOld = childs[id]->body.getRot() - rotOffset[id];
    rb::Vector3 fPos = father->body.getPos();
    rb::Vector3 cPos = childs[id]->body.getPos();

    childs[id]->body.setRot(fRot + rotOffset[id]);

    //passo a coordinate 3D per calcolare rotazione sul piano YZ oltre che al piano XZ
    // calcolo alpha angolo 

    float alpha = float (fRot[0] - fRotOld[0]);
    float beta = float (fRot[1] - fRotOld[1]);

    float cosA = glm::cos(alpha);
    float sinA = glm::sin(alpha);
    
    float cosB = glm::cos(beta);
    float sinB = glm::sin(beta);


    glm::mat4 Rx = glm::mat4{
        1 , 0, 0, 0,
        0, cosA, sinA, 0,
        0, -sinA, cosA, 0,
        0, 0, 0, 1
    };

    glm::mat4 Ry = glm::mat4{
        cosB , 0, sinB, 0,
        0, 1, 0, 0,
        -sinB, 0, cosB, 0,
        0, 0, 0, 1
    };

    glm::mat4 T = glm::mat4{
        1, 0, 0, 0, 
        0, 1, 0, 0,
        0 ,0, 1, 0,
        fPos[0], fPos[1], fPos[2], 1
    };

    glm::vec4 resRot = Rx * Ry * glm::vec4(offset[id][0],offset[id][1],offset[id][2],1);
    offset[id] = rb::Vector3{resRot[0], resRot[1], resRot[2]};

    glm::vec4 resTransf = T * resRot;

    childs[id]->body.setPos({resTransf[0],resTransf[1],resTransf[2]});
    

}   

void RigidJoint::traslate(unsigned int id){
    

}

RigidJoint::RigidJoint(PieceInterface* father,std::vector<PieceInterface*> childs){
    this->childs = childs;
    this->father = father;
    rb::Vector3 fCoords = father->globalPos + father->body.getPos();
    rb::Vector3_s fRot = father->body.getRot();




    //mi calcolo l'offset per ogni child rispetto al padre
    for(PieceInterface* c : childs){
        rb::Vector3 tmpCoords;
        rb::Vector3_s tmpRot;

        rb::Vector3 cCoords = c->globalPos + c->body.getPos();

        tmpCoords = cCoords - fCoords;
        tmpRot = c->body.getRot() - fRot;

        
        offset.push_back(tmpCoords);
        rotOffset.push_back(tmpRot);
        
    }


}

RigidJoint::~RigidJoint(){

}

void RigidJoint::movechild(){
   
    for ( unsigned int i = 0; i < childs.size(); i++){
        traslate(i);
        rotate(i);
    }
}
#include "../headers/rigid_joint.hpp"

#define ZERO_INT 0.00001

//using namespace glm;

void RigidJoint::rotate(unsigned int id){
    rb::Vector3_s fRot = father->body.getRot();
    rb::Vector3_s fRotOld = childs[id]->body.getRot() - rotOffset[id];
    rb::Vector3 fPos = father->body.getPos();
    rb::Vector3 cPos = childs[id]->body.getPos();

    childs[id]->body.setRot(fRot + rotOffset[id]);


    // sposto il alla distanza offset rispetto all'origine R*pos
    // calcolo alpha angolo 

    float alpha = float (fRot[2] - fRotOld[2]);
    float cosA = glm::cos(alpha);
    float sinA = glm::sin(alpha);

    glm::mat3 R = glm::mat3(
        /*cos*/ cosA, /*sin*/ sinA, 0,
        /*-sin*/ -sinA , /*cos*/  cosA, 0,
        0,      0,           1
    );

    //sposto il child all'origine rispetto al padre

    glm::vec3 XZ_cPos = {offset[id][0],offset[id][2],1};
    glm::vec3 resRot = R * XZ_cPos;

    offset[id][0] = resRot[0] ;
    offset[id][2] = resRot[1] ; 

    childs[id]->body.setPos({fPos[0]-offset[id][0],offset[id][1],fPos[2] -offset[id][2]});
   
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
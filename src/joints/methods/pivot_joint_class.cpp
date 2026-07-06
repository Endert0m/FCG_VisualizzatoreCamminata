#include "../headers/pivot_joint.hpp"

#define ZERO_INT 0.00001

void PivotJoint::updatePivot(){
    rb::Vector3 fRot = father->body.getRot();

    pivotAngle = pivotAngle + (fRot - oldRot); // trovo angolo totale da angolo di partenza 
    
    float cosA = glm::cos(pivotAngle[0]);
    float sinA = glm::sin(pivotAngle[0]);
    float cosA1 = glm::cos(pivotAngle[1]);
    float sinA1 = glm::sin(pivotAngle[1]);

    glm::mat4 Rpx = glm::mat4{
        1 , 0, 0, 0,
        0, cosA, sinA, 0,
        0, -sinA, cosA, 0,
        0, 0, 0, 1
    };

    glm::mat4 Rpy = glm::mat4{
        cosA1 , 0, sinA1, 0,
        0, 1, 0, 0,
        -sinA1, 0, cosA1, 0,
        0, 0, 0, 1
    };

    glm::vec4 pivotN =  Rpy * Rpx * glm::vec4(stPivot[0], stPivot[1], stPivot[2],1);
    pivot = rb::Vector3{pivotN[0],pivotN[1],pivotN[2]};

    oldRot = fRot;
}

void PivotJoint::rotate(unsigned int id){
    
    rb::Vector3 fPos = father->body.getPos();
    rb::Vector3 cRot = childs[id]->body.getRot();
    
    ////  sposto l'origine passivamente su tutti gli assi ////

    rotOffset[id] = rotOffset[id] + (cRot - oldCRot[id]);

    
    float cosB = glm::cos(rotOffset[id][0]);
    float sinB = glm::sin(rotOffset[id][0]);
    
    float cosB1 = glm::cos(rotOffset[id][1]);
    float sinB1 = glm::sin(rotOffset[id][1]);
    
    glm::mat4 Rcx = glm::mat4{
        1 , 0, 0, 0,
        0, cosB, sinB, 0,
        0, -sinB, cosB, 0,
        0, 0, 0, 1
    };

    glm::mat4 Rcy = glm::mat4{
        cosB1 , 0, sinB1, 0,
        0, 1, 0, 0,
        -sinB1, 0, cosB1, 0,
        0, 0, 0, 1
    };


    glm::vec4 offN = Rcy * Rcx * glm::vec4(offset[id][0],offset[id][1],offset[id][2],1);
    // offset[id] = rb::Vector3{offN[0],offN[1],offN[2]};

    childs[id]->body.setPos(rb::Vector3{fPos[0]+offN[0]+pivot[0],fPos[1]+offN[1]+pivot[1],fPos[2]+offN[2]+pivot[2]});

    //printf("Offset = %f %f %f \n" , offN[0], offN[1], offN[2]);

    oldCRot[id] = cRot;

}   

void PivotJoint::traslate(unsigned int id){

}


PivotJoint::PivotJoint(PieceInterface* father,std::vector<PieceInterface*> childs, rb::Vector3 pivotPoint){
    this->childs = childs;
    this->father = father;
    rb::Vector3 fCoords = father->globalPos + father->body.getPos();
    rb::Vector3 fRot = father->body.getRot();

    pivot = pivotPoint;
    stPivot = pivotPoint;
    rb::Vector3 pivotCenter = father->body.getPos() + stPivot;

    pivotAngle = rb::Vector3{0,0,0};

    oldRot = father->body.getRot();

    //mi calcolo l'offset per ogni child rispetto al pivot
    for(PieceInterface* c : childs){
        rb::Vector3 tmpCoords;
        rb::Vector3 cCoords = c->body.getPos();
        tmpCoords = cCoords - pivotCenter;
        oldCRot.push_back(c->body.getRot());
        offset.push_back(tmpCoords);
        rotOffset.push_back(rb::Vector3{0,0,0});
    }


}

PivotJoint::~PivotJoint(){

}


void PivotJoint::movechild(){
    updatePivot();
    for ( unsigned int i = 0; i < childs.size(); i++){
        traslate(i);
        rotate(i);
    }
}
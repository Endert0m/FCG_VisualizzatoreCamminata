#include "../headers/pivot_joint.hpp"

#define ZERO_INT 0.00001

void PivotJoint::rotate(unsigned int id){
    rb::Vector3_s fRot = father->body.getRot();
    rb::Vector3 fPos = father->body.getPos();
    rb::Vector3_s cRot = childs[id]->body.getRot();
    
    ////  sposto l'origine passivamente su tutti gli assi ////

    float alpha = float (fRot[0] - oldRot[0]);
    float cosA = glm::cos(alpha);
    float sinA = glm::sin(alpha);
    float alpha1 = float (fRot[1] - oldRot[1]);
    float cosA1 = glm::cos(alpha1);
    float sinA1 = glm::sin(alpha1);

    float beta = float (cRot[0] - oldCRot[id][0]);
    float cosB = glm::cos(beta);
    float sinB = glm::sin(beta);
    float beta1 = float (cRot[1] - oldCRot[id][1]);
    float cosB1 = glm::cos(beta1);
    float sinB1 = glm::sin(beta1);
   
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

    
    glm::vec4 pivotN =  Rpy * Rpx * glm::vec4(pivot[0], pivot[1], pivot[2],1);
    pivot = rb::Vector3{pivotN[0],pivotN[1],pivotN[2]};
    glm::vec4 offN = Rcy * Rcx * glm::vec4(offset[id][0],offset[id][1],offset[id][2],1);
    offset[id] = rb::Vector3{offN[0],offN[1],offN[2]};

    childs[id]->body.setPos(rb::Vector3{fPos[0]+offset[id][0]+pivot[0],fPos[1]+offset[id][1]+pivot[1],fPos[2]+offset[id][2]+pivot[2]});

    printf("Offset = %f %f %f \n" , offN[0], offN[1], offN[2]);

    oldRot = fRot; //aggiorno la rotazione per il ciclo successivo
    oldCRot[id] = cRot;

}   

void PivotJoint::traslate(unsigned int id){

}


PivotJoint::PivotJoint(PieceInterface* father,std::vector<PieceInterface*> childs, rb::Vector3 pivotPoint){
    this->childs = childs;
    this->father = father;
    rb::Vector3 fCoords = father->globalPos + father->body.getPos();
    rb::Vector3_s fRot = father->body.getRot();

    pivot = pivotPoint;
    rb::Vector3 pivotCenter = father->body.getPos() + pivot;

    /*
    float sign = pivot[2] >= 0 ? 1 : -1;
    float r = sqrt(pow(pivot[0],2)+pow(pivot[2],2));
    rotOffset.push_back(  rb::Vector3_s{0,0,_Float16( acos(sign * pivot[0]/r) )} );
    */


    oldRot = father->body.getRot();

    //mi calcolo l'offset per ogni child rispetto al pivot
    for(PieceInterface* c : childs){
        rb::Vector3 tmpCoords;
        rb::Vector3 cCoords = c->body.getPos();
        tmpCoords = cCoords - pivotCenter;

        /*
        float r = sqrt(pow(tmpCoords[0],2)+pow(tmpCoords[2],2));
        oldCRot.push_back( rb::Vector3_s{0,0,_Float16( acos(tmpCoords[0]/r) )} );
        */
        oldCRot.push_back(c->body.getRot());

        offset.push_back(tmpCoords);
        
    }


}

PivotJoint::~PivotJoint(){

}


void PivotJoint::movechild(){
   
    for ( unsigned int i = 0; i < childs.size(); i++){
        traslate(i);
        rotate(i);
    }
}